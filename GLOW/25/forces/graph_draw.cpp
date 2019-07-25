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

bool force_iteration(My_graph& G, double threshold)
{
    const double spring_stiffness = 2e-3;
    const double rest_length = 10;
    //const double electrical_repulsion = 25;           // suitable constant for 1/r
    const double electrical_repulsion = 5000;           // suitable constant for 1/r^2
    //const double electrical_repulsion = 20000;        // suitable constant for 1/r^3
    const double DAMPING = 15.0;
    const Point_E2d ORIGIN(0,0);

    std::map<My_node*, Point_E2d> M;
    typedef std::list<My_node*>::const_iterator NIT;
    for(NIT nit = G.nodes.begin(); nit != G.nodes.end(); ++nit) {

        if((*nit)->info().is_free) {
            Vector_E2d force(0,0);

            std::list<My_edge*> &Ls = (*nit)->sourceOf;
            std::list<My_edge*> &Lt = (*nit)->targetOf;

            // Spring force results from adjacent nodes only
            typedef std::list<My_edge*>::const_iterator EIT;
            for(EIT eit = Ls.begin(); eit != Ls.end(); ++eit)
            {
                Vector_E2d Vuv = (*eit)->target()->info().coords - (*nit)->info().coords;
                double dVuv = std::sqrt(squared_distance(ORIGIN, ORIGIN + Vuv));
                Vector_E2d springForce = spring_stiffness * (dVuv - rest_length) * Vuv;
                force = force + springForce;
            }
            for(EIT eit = Lt.begin(); eit != Lt.end(); ++eit)
            {
                Vector_E2d Vuv = (*eit)->source()->info().coords - (*nit)->info().coords;
                double dVuv = std::sqrt(squared_distance(ORIGIN, ORIGIN + Vuv));
                Vector_E2d springForce = spring_stiffness * (dVuv - rest_length) * Vuv;
                force = force + springForce;
            }

            // Electrical repulsion force results from all nodes
            for(NIT nit2 = G.nodes.begin(); nit2 != G.nodes.end(); ++nit2)
            {
                if(nit2 != nit) {
                    Vector_E2d Vuv = (*nit2)->info().coords - (*nit)->info().coords;
                    double dVuv = std::sqrt(squared_distance(ORIGIN, ORIGIN + Vuv));

                    //Vector_E2d electrForce = electrical_repulsion/dVuv * Vuv;
                    Vector_E2d electrForce = electrical_repulsion/dVuv/dVuv * Vuv;
                    //Vector_E2d electrForce = electrical_repulsion/dVuv/dVuv/dVuv * Vuv;
                    force = force - electrForce;
                }
            }
            M[*nit] = (*nit)->info().coords + force/DAMPING;
        }
    }

    bool still_moving = false;
    for(NIT nit = G.nodes.begin(); nit != G.nodes.end(); ++nit)
    {
        if((*nit)->info().is_free) {
            if( squared_distance((*nit)->info().coords, M[*nit]) > threshold )
                still_moving = true;
            (*nit)->info().coords = M[*nit];
        }
    }
    return still_moving;
}
