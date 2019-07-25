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
// E1
//----------------------------------------------------------------

#include "geometry/E1/geometry_e1.h"

typedef Geometry_E1<MyDouble>                          Geometry_E1d;

typedef Geometry_E1<MyDouble>::Point                      Point_E1d;
typedef Geometry_E1<MyDouble>::Hyperplane            Hyperplane_E1d;
typedef Geometry_E1<MyDouble>::Convex_polytope  Convex_polytope_E1d;

//----------------------------------------------------------------
// S1
//----------------------------------------------------------------

#include "geometry/S1/geometry_s1.h"

typedef Geometry_S1<MyDouble>                          Geometry_S1d;

typedef Geometry_S1<MyDouble>::Point                      Point_S1d;
typedef Geometry_S1<MyDouble>::Hyperplane            Hyperplane_S1d;
typedef Geometry_S1<MyDouble>::Convex_polytope  Convex_polytope_S1d;

//----------------------------------------------------------------
