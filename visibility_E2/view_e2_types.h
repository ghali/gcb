/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <list>
#include <vector>

#include "geometry/E2/geometry_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/free/clip_2.h"

typedef Geometry_E2<double> Geometry_E2d;

typedef Geometry_E2d::Point            Point_E2d;
typedef Geometry_E2d::Hyperplane       Segment_E2d;
typedef Geometry_E2d::Convex_polytope  Convex_polytope_E2d;

typedef Geometry_E2d::Polygon           Polygon_E2d;

// ? typedef Geometry_E2d::Convex_polytope Convex_polygon_E2d;
// ? typedef Geometry_E2d::Sub_hyperplane  Sub_hyperplane_E2d;

// #include "geometry/E2/segment_e2.h"

//---------------------
// BSP tree (E2 and S1)
//---------------------

#include "geometry/free/splitting/2D/splitting_2.h"

#include "solid/bsp/bsp_node.h"

//----------------------------------------------------
// Types for BSP tree on E2 (to determine depth order)
//----------------------------------------------------

#include "geometry/E2/convex_polygon_e2.h"

#include "solid/bsp/e2/bsp_e2.h"

//-------------------------------------------------
// Types for BSP tree on S1 (to determine the view)
//-------------------------------------------------

#include "geometry/S1/geometry_s1.h"

typedef Geometry_S1<double>                          Geometry_S1d;

typedef Geometry_S1<double>::Point                      Point_S1d;
typedef Geometry_S1<double>::Hyperplane            Hyperplane_S1d;
typedef Geometry_S1<double>::Convex_polytope  Convex_polytope_S1d;


#include "geometry/S1/topo_segment_s1.h"

#include "solid/bsp/s1/bsp_s1.h"

#include "geometry/free/splitting/1d/splitting_s1.h"

