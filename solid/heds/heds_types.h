/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef HEDS_TYPES_H
#define HEDS_TYPES_H

#include "geometry_types.h"
#include "solid/heds/heds.h"

//----------------------------------------------------------------
struct Vertex
{
    Point_E3f    coords;
    Vertex(const Point_E3f & c = Point_E3f())
        : coords(c) {}
};

struct Arc {};                  // Unused in this example

struct Polygon
{
    Direction_E3f normal;
    Color_3f color;

    Polygon() {}                // Direction_E3 has a default.
    Polygon(const Direction_E3f & n)
        : normal(n) {}
    Polygon(const Color_3f & c)
        : color(c) {}
};

//----------------------------------------------------------------
std::ostream &
operator<< (std::ostream & os, const Vertex & J);

std::ostream &
operator<< (std::ostream & os, const Arc);

std::ostream &
operator<< (std::ostream & os, const Polygon & P);


//----------------------------------------------------------------
struct My_heds_traits
{
    typedef Vertex  Node_type;
    typedef Arc     Edge_type;
    typedef Polygon Face_type;
};


typedef HEDS<My_heds_traits>     HEDS_ff;

// Topology
typedef Node<My_heds_traits>     My_node;
typedef Halfedge<My_heds_traits> My_edge;
typedef Face<My_heds_traits>     My_face;

typedef HEDS_ff::My_node_ptr  My_node_ptr;
typedef HEDS_ff::My_edge_ptr  My_edge_ptr;
typedef HEDS_ff::My_face_ptr  My_face_ptr;

// Geometry (and other attributes)
typedef HEDS_ff::Attribute_node_type Attribute_node_type;
typedef HEDS_ff::Attribute_edge_type Attribute_edge_type;
typedef HEDS_ff::Attribute_face_type Attribute_face_type;

//----------------------------------------------------------------
//----------------------------------------------------------------
struct HEDS_misc_fn
{
    static
    Bbox_E3f
    get_Bbox(const HEDS_ff & H)
    // precondition: H has at least two vertices
    {
        typedef HEDS_ff::My_node_container::const_iterator NodeIt;

        NodeIt vi = H.V.begin();
        Bbox_E3f B = (*vi)->nt.coords;
        do {
            ++vi;
            B += (*vi)->nt.coords;
        } while( vi != H.V.end() );
        return B;
    }
};
//----------------------------------------------------------------

#endif // HEDS_TYPES_H
