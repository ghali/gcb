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

//----------------------------------------------------------------
// E2
//----------------------------------------------------------------

#include "geometry/E2/geometry_e2.h"

#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/convex_polygon_e2.h"

#include "geometry/E2/triangle_e2.h"
#include "geometry/E2/bbox_e2.h"


typedef Geometry_E2<MyDouble>                          Geometry_E2d;

typedef Geometry_E2<MyDouble>::Point                      Point_E2d;
typedef Geometry_E2<MyDouble>::Hyperplane            Hyperplane_E2d;
typedef Geometry_E2<MyDouble>::Convex_polytope  Convex_polytope_E2d;

typedef Triangle_E2<MyDouble>              Triangle_E2d;
typedef Bbox_E2<MyDouble>                      Bbox_E2d;

//----------------------------------------------------------------
