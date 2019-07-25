/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/free/splitting/2D/splitting_2.h"
#include "geometry_types.h"

// template<typename NT>
// void
// split( const Convex_polygon_E2<NT> & a_polygon,
//        const Segment_E2<NT> splitting_line, // Hyperplane
//        Convex_polygon_E2<NT> & positive_side,
//        Convex_polygon_E2<NT> & negative_side )
// {
//     split<Geometry_E2<NT> >(a_polygon, splitting_line, positive_side, negative_side);
// }

#include <cassert>
#include <iostream>
using namespace std;
#include <iterator>
#include <map>

const Point_E2d A(4,4);        //   B--C
const Point_E2d B(4,6);        //   | /|
const Point_E2d C(6,6);        //   |/ |
const Point_E2d D(6,4);        //   A--D

const Triangle_E2d ABCtriangle( A, B, C );
const Triangle_E2d DEFtriangle( A, C, D );

const Convex_polygon_E2d ABC( ABCtriangle );
const Convex_polygon_E2d ACD( DEFtriangle );

void test_boolean_union()
{
    BSP_node_E2 N;
    N.boolean_union( ABC, BA1, IA1 );
    // ABC is represented using the following subtree.
    //                                                                       !  
    //                   AB (splittingLine = LP[0])               node 1     !  
    //                 + / \ -                                               !  
    //                  /   \                                                !  
    //                 F    BC (splittingLine = LP[1])            nodes 2, 3 !  
    //                    + / \ -                                            !  
    //                     /   \                                             !  
    //                    F    CA (splittingLine = LP[2])         nodes 4, 5 !  
    //                       + / \ -                                         !  
    //                        /   \                                          !  
    //                       F     T                              nodes 6, 7 !  
    //      

    assert( N.size() == 7 );
    assert( N.hyperplane == Segment_E2d(A,B) );
    assert( N.boundary_attributes == BA1 );

    assert( ! N.positive_child->cell_is_occupied );
    assert( N.negative_child->hyperplane == Segment_E2d(B,C) );
    assert( N.negative_child->boundary_attributes == BA1 );

    assert( ! N.negative_child->positive_child->cell_is_occupied );
    assert( N.negative_child->negative_child->hyperplane == Segment_E2d(C,A) );
    assert( N.negative_child->negative_child->boundary_attributes == BA1 );

    assert( ! N.negative_child->negative_child->positive_child->cell_is_occupied );
    assert( N.negative_child->negative_child->negative_child->cell_is_occupied );
    assert( N.negative_child->negative_child->negative_child->interior_attributes == IA1 );

    // Test point classification and interior attributes for ABC
    assert( N.classify( Point_E2d (4.5, 5.5) ) == std::make_pair(INSIDE_SET, IA1) );

    N.boolean_union( ACD, BA2, IA2 );

    // Union is now:
    // 
    //                N= AB (splittingLine = LP[0])        !  
    //                 + / \ -                             !  
    //                  /   \                              !  
    //                 F    BC (splittingLine = LP[1])     !  
    //                    + / \ -                          !  
    //                     /   \                           !  
    //                    F    CA (splittingLine = LP[2])  !  
    //                       + / \ -                       !  
    //                        /   \                        !  
    //                   M= CD     T                       !  
    //                    + / \ -                          !  
    //                     /   \                           !  
    //                    F    DA                          !  
    //                       + / \ -                       !  
    //                        /   \                        !  
    //                       F     T                       !

    assert( N.size() == 11 ); // confirm AC/CA was not duplicated

    BSP_node_E2 * M = N.negative_child->negative_child->positive_child;
    assert( M->hyperplane == Segment_E2d(C,D) );
    assert( M->boundary_attributes == BA2 );

    assert( ! M->positive_child->cell_is_occupied );
    assert( M->negative_child->hyperplane == Segment_E2d(D,A) );
    assert( M->negative_child->boundary_attributes == BA2 );

    assert( ! M->negative_child->positive_child->cell_is_occupied );
    assert( M->negative_child->negative_child->cell_is_occupied );
    assert( M->negative_child->negative_child->interior_attributes == IA2 );

    // Test point classification and interior attributes for ACD
    assert( N.classify( Point_E2d (5.5, 4.5) ) == std::make_pair(INSIDE_SET, IA2) );
}

void test_intersection_and_difference()
{
    // ...
}
#if 0
void test_depth_order_1()
{

    const Point_E2d A(2,2);        //       B--C  
    const Point_E2d B(2,4);        //  o    | /        E
    const Point_E2d C(4,4);        //       |/               /|
    const Point_E2d D(6,1);        //       A               / |
    const Point_E2d E(8,3);        //               D--F
    const Point_E2d F(8,1);

    const Point_E2d observer(1,3);

    const Triangle_E2d ABCtriangle( A, B, C );
    const Triangle_E2d DEFtriangle( D, E, F );

    const Convex_polygon_E2d ABC( ABCtriangle );
    const Convex_polygon_E2d DEF( DEFtriangle );

    BSP_node_E2 N;
    N.boolean_union( ABC, BA1, IA1 );
    N.boolean_union( DEF, BA2, IA2 );

    typedef BSP_node_E2::Boundary_list Boundary_list;

    const Bbox_E2d bbox( Point_E2d(0,0), Point_E2d(10,5) );
    const Convex_polygon_E2d convex_polytope(bbox);

    Boundary_list mylist = N.get_boundary( convex_polytope, observer );

    assert( mylist.size() == 2 );
    Boundary_list::const_iterator i = mylist.begin();
    assert( i->first.carrying_line() == Segment_E2d(A, B) );
    assert( i->second                == BA1 );

    ++i;
    assert( i->first.carrying_line() == Segment_E2d(D, E) );
    assert( i->second                == BA2 );
}

void test_depth_order_2()
{
    const Point_E2d A(4, 2), B( 0, 2), C( 2, 3);
    const Point_E2d D(1, 4), E(-5, 4), F(-2, 5);
    const Triangle_E2d T1( A, B, C ), T2( D, E, F );
    const Color red(1,0,0), green(0,1,0);

    BSP_node_E2d depth_order_tree;
    depth_order_tree.boolean_union( T1, red, 0 );
    depth_order_tree.boolean_union( T2, green, 0 );

    typedef BSP_node_E2d::Boundary_list Boundary_list;

    const Point_E2d observer(0, 0);
    const Bbox_E2d bbox( Point_E2d(-6,-1), Point_E2d(5,6) );
    const Convex_polygon_E2d initial_convex_polytope(bbox);
    Boundary_list mylist = depth_order_tree.get_boundary( initial_convex_polytope, observer );

    assert( mylist.size() == 2 );
    Boundary_list::const_iterator i = mylist.begin();
    assert( i->first.carrying_line() == Segment_E2d(A, B) );
    assert( i->second                == red );

    std::vector<Segment_E2d> lines = i->first.bounding_cell().get_lines();
    assert( lines.size() == 4 );
    assert( i->first.source() == A );
    assert( i->first.target() == B );

    ++i;
    assert( i->first.carrying_line() == Segment_E2d(D, E) );
    assert( i->second                == green );

    assert( i->first.source() == D );
    assert( i->first.target() == E );
}

void test_polygon_collection()
{
    const Point_E2d A(4, 2), B( 0, 2), C( 2, 3);
    const Point_E2d D(1, 4), E(-5, 4), F(-2, 5);
    const Triangle_E2d T1( A, B, C ), T2( D, E, F );
    const Color red(1,0,0), green(0,1,0);

    BSP_node_E2d tree;
    tree.boolean_union( T1, red, 3 );
    tree.boolean_union( T2, green, 5 );

    const Bbox_E2d bbox( Point_E2d(-6,-1), Point_E2d(5,6) );
    const Convex_polygon_E2d initial_convex_polytope(bbox);

    typedef BSP_node_E2d::Interior_list Interior_list;
    
    Interior_list polygons = tree.get_convex_polytopes(initial_convex_polytope);

    Interior_list::const_iterator p = polygons.begin();

    std::vector<Segment_E2d> l = p->first.get_lines();
    std::vector<Segment_E2d>::const_iterator lit = l.begin();
    assert( *lit++ == Segment_E2d(A,B) );
    assert( *lit++ == Segment_E2d(B,C) );
    assert( *lit++ == Segment_E2d(C,A) );
    assert( lit == l.end() );
    assert( p++->second == 3 );

    /*std::vector<Segment_E2d>*/ l = p->first.get_lines();
    /*std::vector<Segment_E2d>::const_iterator*/ lit = l.begin();
    assert( *lit++ == Segment_E2d(D,E) );
    assert( *lit++ == Segment_E2d(E,F) );
    assert( *lit++ == Segment_E2d(F,D) );
    assert( lit == l.end() );
    assert( p++->second == 5 );

    assert( p == polygons.end() );
}
#endif
int main()
{
    test_boolean_union();
    test_intersection_and_difference();
#if 0
    test_depth_order_1();
    test_depth_order_2();
    test_polygon_collection();
#endif
}
