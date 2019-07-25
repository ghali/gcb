/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef EDGE_H
#define EDGE_H

//----------------------------------------------------------------
template<typename Graph_traits> struct Node;

//----------------Edge_Begin----------------
template<typename Graph_traits> struct Edge
{
    typedef typename Graph_traits::Node_type  Parameter_node_type;
    typedef typename Graph_traits::Edge_type  Parameter_edge_type;

    typedef Node<Graph_traits>  My_node;

    My_node * _source;
    My_node * _target;

    Parameter_edge_type et;

    Edge() {}
    Edge(My_node* s, My_node* t, const Parameter_edge_type& et)
        : _source(s), _target(t), et(et) {}

    virtual ~Edge() { }

    const Parameter_edge_type info() const { return et; }
    Parameter_edge_type& info() { return et; }

    My_node * source() const { return _source; }
    My_node * target() const { return _target; }
};
//----------------Edge_End----------------

#endif // EDGE_H
