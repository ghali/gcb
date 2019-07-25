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

#include "boost/shared_ptr.hpp"

template<typename HEDS_traits>
struct Halfedge;

template<typename HEDS_traits>
struct Face;

template<typename HEDS_traits>
struct Node
{
    typedef typename HEDS_traits::Node_type  Attribute_node_type;
    typedef typename HEDS_traits::Edge_type  Attribute_edge_type;
    typedef typename HEDS_traits::Face_type  Attribute_face_type;

    typedef Node<HEDS_traits>      My_node;
    typedef Halfedge<HEDS_traits>  My_edge;
    typedef Face<HEDS_traits>      My_face;

    // Shared Pointers
    typedef boost::shared_ptr<My_node> My_node_ptr;
    typedef boost::shared_ptr<My_edge> My_edge_ptr;
    typedef boost::shared_ptr<My_face> My_face_ptr;
    // 
    // Replace with the following to switch to concrete pointers.
    // typedef My_node *  My_node_ptr;
    // typedef My_edge *  My_edge_ptr;
    // typedef My_face *  My_face_ptr;


    My_edge_ptr outgoing_edge;
    Attribute_node_type nt;

    Node(const Attribute_node_type & _nt = Attribute_node_type())
        : nt(_nt) {}

    const Attribute_node_type info() const { return nt; }
    Attribute_node_type & info() { return nt; }

    unsigned int valence() const
    {
        My_edge_ptr e = outgoing_edge;
        if(!e)
            return 0;

        int valence = 0;
        do {
            // e = e->pred->twin;
            e = e->twin->succ;
            ++valence;
        } while(e != outgoing_edge);

        return valence;
    }

    // Precondition: Node has at least one outgoing edge.
    My_edge_ptr get_ccw_nth_outgoing_edge(int n) // first edge is #0
    {
        My_edge_ptr e = outgoing_edge;

        while(n) {
            e = e->pred->twin;
            --n;
        } 

        return e;
    }
};

#endif // NODE_H
