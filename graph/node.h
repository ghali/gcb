/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef NODE_H
#define NODE_H

#include <list>

//----------------Edge_forward_decl_Begin----------------
template<typename Graph_traits> struct Edge;
//----------------Edge_forward_decl_End----------------

//----------------Node_1_Begin----------------
template<typename Graph_traits> struct Node
{
    typedef typename Graph_traits::Node_type  Parameter_node_type;
    typedef typename Graph_traits::Edge_type  Parameter_edge_type;

    typedef Edge<Graph_traits>  My_edge;

    std::list<My_edge*> sourceOf; // node is source of these edges
    std::list<My_edge*> targetOf; // node is target of these edges

    Parameter_node_type nt;

    Node(const Parameter_node_type& _nt)
        : sourceOf(), targetOf(), nt(_nt) {}

    virtual ~Node() { }
//----------------Node_1_End----------------

    const Parameter_node_type info() const { return nt; }
    Parameter_node_type& info() { return nt; }

//----------------Node_2_Begin----------------
    My_edge*
    is_adjacent(Node *n2) const
    {
        typedef typename std::list<My_edge*>::const_iterator Edge_iterator;
        for( Edge_iterator eit=sourceOf.begin(); eit!=sourceOf.end(); ++eit )
            if( (*eit)->target() == n2 ) // directed graph
                return *eit;
        return NULL;
    }
};
//----------------Node_2_End----------------

#endif // NODE_H
