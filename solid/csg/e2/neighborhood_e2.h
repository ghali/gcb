/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef NEIGHBORHOOD_E2_H
#define NEIGHBORHOOD_E2_H

#include "../csg_boolean_operation.h"

typedef double MyDouble;

#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"

typedef Point_S1<MyDouble>     Point_S1d;
typedef Segment_S1<MyDouble> Segment_S1d;


// #include "solid/bsp/s1/bsp_s1_segment.h"
#include "solid/bsp/s1/bsp_s1.h"
#include "solid/bsp/bsp_node.h"

typedef BSP_S1< MyDouble, char, char >        BSP_geometry;
typedef BSP_geometry::BSP_convex_polytope BSP_S1_segment_d;
typedef BSP_geometry::Sub_hyperplane      Sub_hyperplane_d;

typedef BSP_node< BSP_geometry, char, char >   BSP_node_S1;


class Neighborhood_E2
{
    BSP_node_S1 N;
public:
    Neighborhood_E2( ) : N() {}
    Neighborhood_E2( const BSP_node_S1& N ) : N(N) {}

    bool is_empty() const { return N.is_empty(); }
    bool is_full()  const { return N.is_full(); }

    Set_membership contains( const Point_S1d& P ) const
    {
        return N.classify(P).first;
    }

    Neighborhood_E2 eval(const CSG_Boolean_operation& op,
                         const Neighborhood_E2& n2)
    {
        switch(op) {
        case UNION:
            return Neighborhood_E2( N.boolean_union(n2.N) );
            break;
        case INTERSECTION:
            return Neighborhood_E2( N.boolean_intersection(n2.N) );
            break;
        default: // case DIFFERENCE:
            return Neighborhood_E2( N.boolean_difference(n2.N) );
            break;
        }
    }
};

#endif // NEIGHBORHOOD_E2_H
