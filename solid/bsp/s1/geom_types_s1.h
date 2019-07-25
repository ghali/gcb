/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

typedef double MyDouble;

typedef enum { BA1, BA2, BA3, BA4 } My_Boundary_attributes;
typedef enum { IA1, IA2, IA3, IA4 } My_Interior_attributes;


#include "geometry/S1/geometry_s1.h"

typedef Geometry_S1<MyDouble>::Point                      Point_S1d;
typedef Geometry_S1<MyDouble>::Hyperplane            Hyperplane_S1d;
typedef Geometry_S1<MyDouble>::Convex_polytope  Convex_polytope_S1d;

//typedef Point_S1<MyDouble>     Point_S1d;
//typedef Segment_S1<MyDouble> Segment_S1d;


#include "geometry/S1/topo_segment_s1.h"
#include "bsp_s1.h"
#include "solid/bsp/bsp_node.h"

typedef BSP_S1< MyDouble, My_Boundary_attributes, My_Interior_attributes >       BSP_geometry;
typedef BSP_geometry::Sub_hyperplane                 Sub_hyperplane_d;

typedef BSP_node< BSP_geometry, My_Boundary_attributes, My_Interior_attributes >  BSP_node_S1;
