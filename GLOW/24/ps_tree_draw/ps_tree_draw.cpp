/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <sys/time.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "tree_draw/node.h"
#include "tree_draw/embed_tree_by_rank_e2.h"
// #include "embed_tree_tidier_e2.h"

#include "geometry/E2/point_e2.h"
#include "postscript/ps_binary_tree_renderer.h"

typedef double PS_number_type;
typedef double NT;

const NT diameter = 0.2;

typedef Point_E2<PS_number_type> Point_E2ps;
typedef Node<NT> Node_type;

typedef std::map<const Node_type*, Point_E2ps > My_map;

Node_type *
generate_random_tree( int number_of_nodes )
{
    std::vector<int> V;
    for(int i=0; i<number_of_nodes; ++i)
        V.push_back(i);

    timeval mytime;
    gettimeofday(&mytime, NULL);
    srand(mytime.tv_usec);
    random_shuffle(V.begin(), V.end());

    std::vector<int>::const_iterator it= V.begin();
    Node_type * mytree = new Node_type( *it++ );
    while( it != V.end() )
        mytree->insert( *it++ );

    return mytree;
}

// Uncomment "tidier" lines after implementing the corresponding algorithm
int main(int argc, char **argv)
{
    int number_of_nodes = (argc>=2) ? atoi(argv[1]) : 50;
    int number_of_iterations = (argc==3) ? atoi(argv[2]) : 3;
    int i = 0;

    while(i++!=number_of_iterations)
    {
        std::ostringstream number_str, rank_fname;
//        std::ostringstream tidier_fname;
        number_str << "psout/" << std::setfill('0') << std::setw(2) << i;
        rank_fname << number_str.str() << "_rank_drawing" << ".eps";
//        tidier_fname << number_str.str() << "_tidier_drawing" << ".eps";

        Node_type * mytree = generate_random_tree( number_of_nodes );

        My_map M1 = embed_tree_by_rank_E2<Node_type, PS_number_type >(mytree);
        PS_Binary_Tree_Renderer<Node_type, PS_number_type> r( rank_fname.str(), mytree, M1, diameter );
        r.draw();

//        My_map M2 = embed_tree_tidier_E2<Node_type, PS_number_type >(mytree);
//        r = PS_Binary_Tree_Renderer<Node_type, PS_number_type>( tidier_fname.str(), mytree, M2, diameter );
//        r.draw();
    }
}
