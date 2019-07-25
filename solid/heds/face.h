/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef FACE_H
#define FACE_H

#include "boost/shared_ptr.hpp"

template<typename HEDS_traits>
struct HEDS;

template<typename HEDS_traits>
struct Halfedge;

template<typename HEDS_traits>
struct Face
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

    My_edge_ptr edge;
    Attribute_face_type ft;

    // Face() : edge(NULL), ft() {}
    // 
    // Face(const Attribute_face_type & _ft)
    //     : edge(new My_edge(NULL)), ft(_ft) {}
    // 
    // Face(const Attribute_face_type & _ft,
    //      My_edge_ptr myedge
    //      )
    //     : edge(myedge), ft(_ft) {}

    Face(My_edge_ptr myedge,
         const Attribute_face_type & _ft = Attribute_face_type()
         )
        : edge(myedge), ft(_ft) {}

    const Attribute_face_type info() const { return ft; }
    Attribute_face_type & info() { return ft; }

    unsigned int valence() const
    {
        My_edge_ptr e = edge;
        if(!e)
            return 0;

        int valence = 0;
        do {
            e = e->succ;
            ++valence;
        } while(e != edge);

        return valence;
    }
};

#endif // FACE_H
