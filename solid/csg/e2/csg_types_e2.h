/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

typedef double mydouble;

#include "geometry/E2/point_e2.h"
#include "geometry/E2/triangle_e2.h"
#include "geometry/E2/transformation_e2.h"
typedef Point_E2<mydouble> Point_E2d;
typedef Triangle_E2<mydouble> Triangle_E2d;
typedef Transformation_E2<mydouble> Transformation_E2d;


#include "csg_e2_triangle.h"
#include "neighborhood_e2.h"

#include "../csg_boolean.h"
#include "../csg_transformation.h"

typedef CSG_node<Point_E2d, Neighborhood_E2, Transformation_E2d> CSG_node_E2d;
typedef CSG_Boolean<Point_E2d, Neighborhood_E2, Transformation_E2d> CSG_Boolean_E2d;
typedef CSG_transformation<Point_E2d, Neighborhood_E2, Transformation_E2d> CSG_transformation_E2d;

