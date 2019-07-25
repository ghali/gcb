/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef EMBED_TREE_BY_RANK_E2_H
#define EMBED_TREE_BY_RANK_E2_H

#include <vector>
#include <map>

#include "geometry/E2/point_e2.h"

template<typename Node, typename T>
void
assign_rank_and_depth(
                      const Node* mynode,
                      int& rank, int depth,
                      std::map<const Node*, Point_E2<T> > & M )
{
    Node * N = mynode->get_negative_child();
    Node * P = mynode->get_positive_child();

    if( N )  assign_rank_and_depth( N, rank, depth-2, M );
    M[mynode] = Point_E2<T>(rank, depth);
    rank += 1;
    if( P )  assign_rank_and_depth( P, rank, depth-2, M );
}

// Requirement: Node_type must provide the two functions
//     get_negative_child() and get_positive_child()

template<typename Node_type, typename T>
std::map<const Node_type*, Point_E2<T> >
embed_tree_by_rank_E2( const Node_type* mytree )
{
    std::map<const Node_type*, Point_E2<T> > M;
    if( mytree )
    {
        int current_rank = 0;
        assign_rank_and_depth( mytree, current_rank, 0, M );
    }
    return M;
}

#endif // EMBED_TREE_BY_RANK_E2_H
