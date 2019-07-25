/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "heds_types.h"

#include "solid/heds/heds_reader.h"

#include <cassert>
#include <iostream>
#include <map>

typedef HEDS_reader<My_heds_traits>   HEDS_reader_ff;

void test_file_reading()
{
    HEDS_ff myHEDS;

    // assert( !HEDS_reader_ff::read(myHEDS, "/Users/me/ghali/gcb/chaps/code/objects/cube.off") );
    assert( !HEDS_reader_ff::read(myHEDS, "../../objects/cube.off") );

    assert( myHEDS.number_of_nodes() == 8 );
    assert( myHEDS.number_of_faces() == 6 );

    // assert( myHEDS.check_twins() );

    typedef HEDS_ff::My_face_container::const_iterator FIT;
    for(FIT fit = myHEDS.F.begin(); fit != myHEDS.F.end(); ++fit)
    {
        assert( (*fit)->edge->succ->succ->succ->succ == (*fit)->edge );
        assert( (*fit)->edge->pred->pred->pred->pred == (*fit)->edge );
    }
}

void test_stitch_twins_for_a_node_pair()
{
    HEDS_ff myHEDS;

    My_node_ptr V0 = My_node_ptr( new My_node(Point_E3f()) );
    My_node_ptr V1 = My_node_ptr( new My_node(Point_E3f()) );
    myHEDS.V.push_back(V0);
    myHEDS.V.push_back(V1);

    My_edge_ptr e0 = My_edge_ptr( new My_edge(V0, V1) );
    My_edge_ptr e1 = My_edge_ptr( new My_edge(V1, V0) );
    myHEDS.E.push_back(e0);
    myHEDS.E.push_back(e1);

    myHEDS.stitch_twins();
    
    assert( e0->twin == e1 );
    assert( e1->twin == e0 );

    My_face_ptr P0 = My_face_ptr( new My_face(e0, Attribute_face_type()) );
    e0->adjFace = P0;
    e1->adjFace = P0;

    std::cout << myHEDS << std::endl;
}

void test_set_halfedge_succ_pred_links()
{
    My_node_ptr V0( new My_node(Point_E3f()) );
    My_node_ptr V1( new My_node(Point_E3f()) );
    My_node_ptr V2( new My_node(Point_E3f()) );

    My_edge_ptr e0( new My_edge(V0, V1) );
    My_edge_ptr e1( new My_edge(V1, V0) );

    My_edge_ptr e2( new My_edge(V1, V2) );
    My_edge_ptr e3( new My_edge(V2, V1) );

    My_edge_ptr e4( new My_edge(V2, V0) );
    My_edge_ptr e5( new My_edge(V0, V2) );

    HEDS_ff myHEDS;
    myHEDS.V.push_back(V0);
    myHEDS.V.push_back(V1);
    myHEDS.V.push_back(V2);

    myHEDS.E.push_back(e0);
    myHEDS.E.push_back(e1);
    myHEDS.E.push_back(e2);
    myHEDS.E.push_back(e3);
    myHEDS.E.push_back(e4);
    myHEDS.E.push_back(e5);

    myHEDS.stitch_twins();

    myHEDS.set_halfedge_succ_pred_links();

    // assert();

}

void test_triangular_lamina_from_lower_primitives()
{
    //         N0----------- e3
    //       /  \ \           |
    //      /    |  \         |
    //  e5 /    /    \         | 
    //    |    e0 F0  \e2------
    //    |   /                  N2
    //     \ /  -----e1--------
    //     N1 /                /
    //        \               /      
    //          --------------
    //                 e4
    // 

    HEDS_ff myHEDS;

    My_node_ptr N0( new My_node(Point_E3f()) );
    My_node_ptr N1( new My_node(Point_E3f()) );
    My_node_ptr N2( new My_node(Point_E3f()) );

    myHEDS.V.push_back(N0); myHEDS.V.push_back(N1); myHEDS.V.push_back(N2);

    My_edge_ptr e0( new My_edge(N0, N1) );
    My_edge_ptr e1( new My_edge(N1, N2) );
    My_edge_ptr e2( new My_edge(N2, N0) );

    My_edge_ptr e3( new My_edge(N0, N2) );
    My_edge_ptr e4( new My_edge(N2, N1) );
    My_edge_ptr e5( new My_edge(N1, N0) );

    e0->succ = e1; e1->succ = e2; e2->succ = e0;
    e3->succ = e4; e4->succ = e5; e5->succ = e3;

    e0->pred = e2; e1->pred = e0; e2->pred = e1;
    e3->pred = e5; e4->pred = e3; e5->pred = e4;

    myHEDS.E.push_back(e0); myHEDS.E.push_back(e1); myHEDS.E.push_back(e2);
    myHEDS.E.push_back(e3); myHEDS.E.push_back(e4); myHEDS.E.push_back(e5);

    myHEDS.stitch_twins();

    // Test twins are propertly stitched
    {
        assert( e0->twin == e5  && e5->twin == e0 );
        assert( e1->twin == e4  && e4->twin == e1 );
        assert( e2->twin == e3  && e3->twin == e2 );
    
        myHEDS.set_node_outgoing_edge();

        assert( N0->outgoing_edge == e0 || N0->outgoing_edge == e3 );
        assert( N1->outgoing_edge == e1 || N1->outgoing_edge == e5 );
        assert( N2->outgoing_edge == e2 || N2->outgoing_edge == e4 );
    }

    // Test node functions: valence and nth_outgoing
    {
        assert( N0->valence() == 2 );

        assert( N0->get_ccw_nth_outgoing_edge(0) == e0);
        assert( N0->get_ccw_nth_outgoing_edge(1) == e3);
    }

    My_face_ptr F0( new My_face(e0, Attribute_face_type()) );
    My_face_ptr F1( new My_face(e5, Attribute_face_type()) );
    myHEDS.F.push_back(F0); myHEDS.F.push_back(F1);

    e0->adjFace = F0;
    e1->adjFace = F0;
    e2->adjFace = F0;
    e3->adjFace = F1;
    e4->adjFace = F1;
    e5->adjFace = F1;

    // Test face function: valence
    {
        assert( F0->valence() == 3 );
        assert( F1->valence() == 3 );
    }

    std::cout << myHEDS << std::endl;
}

#if 0
void test_triangular_lamina_using_Euler_operators()
{
    //         N0----------- e3
    //       /  \ \           |
    //      /    |  \         |
    //  e5 /    /    \         | 
    //    |    e0 F0  \e2------
    //    |   /                  N2
    //     \ /  -----e1--------1
    //     N1 /                /
    //        \               /      
    //          --------------
    //                 e4
    // 

    HEDS_ff myheds;

    Attribute_node_type vertex;
    Attribute_face_type polygon;

    My_node_ptr N0, N1, N2;
    My_face_ptr F0, F1;
    My_edge_ptr e0, e1, e2, e3, e4, e5;

    myheds.mvfs(/*in*/vertex, /*in*/polygon, /*out*/N0, /*out*/F0);
    // myheds.mev(/*in*/vertex, /*in*/edge);
    // myheds.mev();
    // myheds.mef();
}
#endif

int main()
{
    test_file_reading();
    // Uncomment the following tests after implementing
    // the stitch-twins exercise.
//    test_stitch_twins_for_a_node_pair();
//    test_set_halfedge_succ_pred_links();
//    test_triangular_lamina_from_lower_primitives();
    // test_triangular_lamina_using_Euler_operators();
}
