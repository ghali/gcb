/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "graph_types.h"

#include <string>
#include <cassert>

//----------------graph_setup_Begin----------------
void graph_setup()
{
    My_graph G;
    My_node *n1 = G.insert_node( City( "Cairo", 15e6 ) );
    My_node *n2 = G.insert_node( City( "Alexandria", 2e6) );

    My_edge *e1 = G.insert_edge( n1, n2, Flight( 225, 'f' ) );

    assert( G.are_adjacent(n1, n2) == e1 );
    assert( !G.are_adjacent(n2, n1) );
}
//----------------graph_setup_End----------------

int main()
{
    graph_setup();
}
