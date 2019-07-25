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


#include "geometry/E2/geometry_e2.h"

#include "geometry/E2/triangle_e2.h"
#include "geometry/E2/bbox_e2.h"

typedef Geometry_E2<MyDouble>              Geometry_E2d;

typedef Geometry_E2d::Point           Point_E2d;
typedef Geometry_E2d::Hyperplane      Segment_E2d;
typedef Geometry_E2d::Convex_polytope Convex_polygon_E2d;
typedef Geometry_E2d::Sub_hyperplane  Sub_hyperplane_E2d;

typedef Triangle_E2<MyDouble>              Triangle_E2d;
typedef Bbox_E2<MyDouble>                      Bbox_E2d;

#include "bsp_e2.h"
#include "solid/bsp/bsp_node.h"
//typedef BSP_E2_convex_polygon< MyDouble, My_Boundary_attributes > BSP_E2_convex_polygon_d;
//typedef BSP_E2_segment       < MyDouble, My_Boundary_attributes >        Sub_hyperplane_d;

typedef BSP_E2< MyDouble, My_Boundary_attributes, My_Interior_attributes >       BSP_geometry;
typedef BSP_node< BSP_geometry, My_Boundary_attributes, My_Interior_attributes >  BSP_node_E2;

//----------------------------------------------------------------
#include "misc/color_3.h"
typedef Color_3<unsigned char> Color;

typedef BSP_E2< MyDouble, Color, int >                BSP_geometry_E2;
typedef BSP_node< BSP_geometry_E2, Color, int >          BSP_node_E2d;
