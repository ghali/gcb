/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GRAPH_TYPES_H
#define GRAPH_TYPES_H

//----------------------------------------------------------------
#include "geometry_types.h"
#include "graph/graph.h"

struct Node_parameter
{
    Point_E2d coords;
    bool is_free;               // is node fixed or free?
    Node_parameter(const Point_E2d& p, bool _is_free = true)
        : coords(p), is_free(_is_free) {}
    void set_coords(const Point_E2d& p)
    {
        coords = p;
    }
    void flip_status()
    {
        is_free = !is_free;
    }
};
std::ostream&
operator<<(std::ostream& out , const Node_parameter& np);

struct My_graph_traits
{
    typedef Node_parameter  Node_type;
    typedef char  Edge_type;
};

typedef Graph<My_graph_traits>  My_graph;
typedef My_graph::My_node  My_node;
typedef My_graph::My_edge  My_edge;
//----------------------------------------------------------------

#endif // GRAPH_TYPES_H
