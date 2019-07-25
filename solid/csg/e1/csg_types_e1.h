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

#include "geometry/E1/point_e1.h"
#include "geometry/E1/segment_e1.h"
#include "geometry/E1/transformation_e1.h"
typedef Point_E1<mydouble> Point_E1d;
typedef Segment_E1<mydouble> Segment_E1d;
typedef Transformation_E1<mydouble> Transformation_E1d;

#include "csg_e1_segment.h"
#include "neighborhood_e1.h"

#include "../csg_boolean.h"
#include "../csg_transformation.h"

typedef CSG_node<Point_E1d, Neighborhood_E1, Transformation_E1d> CSG_node_E1d;
typedef CSG_Boolean<Point_E1d, Neighborhood_E1, Transformation_E1d> CSG_Boolean_E1d;
typedef CSG_transformation<Point_E1d, Neighborhood_E1, Transformation_E1d> CSG_transformation_E1d;
