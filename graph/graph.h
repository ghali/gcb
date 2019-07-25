/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>

#include "node.h"
#include "edge.h"

template<typename Graph_traits> struct Graph;

template<typename Graph_traits> 
std::ostream&
operator<<(std::ostream& out, const Graph<Graph_traits>& G);

//----------------Graph_1_Begin----------------
template<typename Graph_traits> struct Graph
{
    typedef typename Graph_traits::Node_type  Parameter_node_type;
    typedef typename Graph_traits::Edge_type  Parameter_edge_type;

    typedef Node<Graph_traits>  My_node;
    typedef Edge<Graph_traits>  My_edge;

    std::list<My_node*> nodes;
    std::list<My_edge*> edges;

    Graph() {}
    virtual ~Graph() { clear(); }
//----------------Graph_1_End----------------

//----------------insert_node_Begin----------------
    virtual My_node* insert_node(
                                 const Parameter_node_type& nt =
                                 Parameter_node_type())
    {
        My_node* mynode = new My_node( nt );
        nodes.push_back(mynode);
        return mynode;
    }
//----------------insert_node_End----------------

//----------------insert_edge_Begin----------------
    virtual My_edge* insert_edge(
                                 My_node* source, My_node* target,
                                 const Parameter_edge_type& et =
                                 Parameter_edge_type() )
    {
        My_edge* newedge = new My_edge(source, target, et);

        source->sourceOf.push_back(newedge);
        target->targetOf.push_back(newedge);

        edges.push_back(newedge);
        return newedge;
    }
//----------------insert_edge_End----------------

    virtual My_edge* are_adjacent(My_node* source, My_node* target)
    {
        return source->is_adjacent( target );
    }

    void clear()
    {
        typedef typename std::list<My_node*>::iterator Nit;
        for(Nit n = nodes.begin(); n != nodes.end(); ++n)
            delete *n;
        typedef typename std::list<My_edge*>::iterator Eit;
        for(Eit e = edges.begin(); e != edges.end(); ++e)
            delete *e;

        nodes.clear();
        edges.clear();
    }

    int number_of_nodes() const { return nodes.size(); }
    int number_of_edges() const { return edges.size(); }

    friend
    std::ostream&
    operator<< <>(std::ostream& out, const Graph<Graph_traits>& G);
};


template<typename Graph_traits>
std::ostream&
operator<<(std::ostream& out, const Graph<Graph_traits>& G)
{
    typedef typename Graph<Graph_traits>::My_node  My_node;
    typedef typename Graph<Graph_traits>::My_edge  My_edge;

    out << "GRAPH\n" << G.nodes.size() << " " << G.edges.size() << std::endl;
    std::map<My_node*, int> M;
    int counter = 0;
    typedef typename std::list<My_node*>::const_iterator NIT;
    for(NIT My_node_It = G.nodes.begin();
        My_node_It != G.nodes.end(); ++My_node_It) {
        out << (*My_node_It)->info() << std::endl;
        M[*My_node_It] = counter++;
    }

    typedef typename std::list<My_edge*>::const_iterator EIT;
    for(EIT My_edge_It = G.edges.begin();
        My_edge_It != G.edges.end(); ++My_edge_It) {
        out << M[(*My_edge_It)->source()] << " " << M[(*My_edge_It)->target()] << std::endl;
    }
    for(NIT My_node_It = G.nodes.begin();
        My_node_It != G.nodes.end(); ++My_node_It) {
        if( (*My_node_It)->sourceOf.size() ) {
            out << "My_node " << M[*My_node_It] << " is the source of an edge adjacent to ";
            for(EIT My_edge_It = (*My_node_It)->sourceOf.begin();
                My_edge_It != (*My_node_It)->sourceOf.end(); ++My_edge_It) {
                out << M[(*My_edge_It)->target()] << " ";
            }
            out << std::endl;
        }
        if( (*My_node_It)->targetOf.size() ) {
            out << "My_node " << M[*My_node_It] << " is the target of an edge adjacent to ";
            for(EIT My_edge_It = (*My_node_It)->targetOf.begin();
                My_edge_It != (*My_node_It)->targetOf.end(); ++My_edge_It) {
                out << M[(*My_edge_It)->source()] << " ";
            }
            out << std::endl;
        }
    }
    return out;
}

#endif // GRAPH_H
