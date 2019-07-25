/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "graph.h"

//----------------City_Begin----------------
struct City
{
    std::string city_name;
    int population;
//----------------City_End----------------

    City( std::string city_name, int population )
        : city_name(city_name), population(population) {}
};
std::ostream&
operator<<(std::ostream& out , const City& c) {
    return out << c.city_name << " " << c.population;
}

//----------------Flight_Begin----------------
struct Flight
{
    float distance;
    char type; 
//----------------Flight_End----------------

    Flight( float distance, char type )
        : distance(distance), type(type) {}
};
std::ostream&
operator<<(std::ostream& out , const Flight& f) {
    return out << f.distance << " " << f.type;
}


//----------------My_graph_traits_Begin----------------
struct My_graph_traits
{
    typedef City Node_type;
    typedef Flight Edge_type;
};

typedef Graph<My_graph_traits> My_graph;
typedef My_graph::My_node  My_node;
typedef My_graph::My_edge  My_edge;
//----------------My_graph_traits_End----------------
