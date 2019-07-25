/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "graph_draw.h"

//----------------barycentric_iteration_Begin----------------
bool barycentric_iteration(My_graph& G, double threshold)
{
    const Point_E2d ORIGIN(0,0);
    std::map<My_node*, Point_E2d> M;
    typedef std::list<My_node*>::const_iterator NIT;
    typedef std::list<My_edge*>::const_iterator EIT;
    for(NIT nit = G.nodes.begin(); nit != G.nodes.end(); ++nit)
    {
        if( (*nit)->info().is_free ) {
            Vector_E2d sum(0,0);
            int degree = 0;

            std::list<My_edge*> &Ls = (*nit)->sourceOf;
            for(EIT eit = Ls.begin(); eit != Ls.end(); ++eit, ++degree)
                sum = sum + ((*eit)->target()->info().coords - ORIGIN);

            std::list<My_edge*> &Lt = (*nit)->targetOf;
            for(EIT eit = Lt.begin(); eit != Lt.end(); ++eit, ++degree)
                sum = sum + ((*eit)->source()->info().coords - ORIGIN);

            M[*nit] = Point_E2d(ORIGIN + (sum/double(degree)));
        }
    }

    bool still_moving = false;
    for(NIT nit = G.nodes.begin(); nit != G.nodes.end(); ++nit)
    {
        if((*nit)->info().is_free) {
            if( squared_distance((*nit)->info().coords, M[*nit]) > threshold )
                still_moving = true;

            (*nit)->info().set_coords( M[*nit] );
        }
    }
    return still_moving;
}
//----------------barycentric_iteration_End----------------

