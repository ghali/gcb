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

typedef enum { BA1, BA2, BA3 } My_Boundary_attributes;
typedef enum { IA1, IA2, IA3 } My_Interior_attributes;


#include "geometry/E1/geometry_e1.h"

typedef Geometry_E1<MyDouble>::Point                      Point_E1d;
typedef Geometry_E1<MyDouble>::Hyperplane            Hyperplane_E1d;
typedef Geometry_E1<MyDouble>::Convex_polytope  Convex_polytope_E1d;

//typedef Point_E1<MyDouble>     Point_E1d;
//typedef Segment_E1<MyDouble> Segment_E1d;
//typedef BSP_geometry::BSP_convex_polytope            BSP_E1_segment_d;



#include "geometry/E1/topo_segment_e1.h"
#include "bsp_e1.h"
#include "solid/bsp/bsp_node.h"

typedef BSP_E1< MyDouble, My_Boundary_attributes, My_Interior_attributes >       BSP_geometry;
typedef BSP_geometry::Sub_hyperplane                 Sub_hyperplane_d;

typedef BSP_node< BSP_geometry, My_Boundary_attributes, My_Interior_attributes >  BSP_node_E1;
