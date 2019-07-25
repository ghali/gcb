/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "boost/shared_ptr.hpp"

template<typename HEDS_traits>
struct Face;

template<typename HEDS_traits>
struct Halfedge
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

    My_node_ptr   source, target;
    My_face_ptr          adjFace;
    My_edge_ptr       pred, succ;
    My_edge_ptr             twin;

    Attribute_edge_type et;

    Halfedge(My_node_ptr source,
             My_node_ptr target,
             const Attribute_edge_type & _et = Attribute_edge_type())
        : source(source), target(target), adjFace(My_face_ptr()), et(_et)
    {}

    Halfedge(My_node_ptr source,
             My_node_ptr target,
             My_face_ptr adjFace,
             const Attribute_edge_type & _et = Attribute_edge_type())
        : source(source), target(target), adjFace(adjFace), et(_et)
    {}

    const Attribute_edge_type info() const { return et; }
    Attribute_edge_type & info() { return et; }
};

#endif // HALFEDGE_H
