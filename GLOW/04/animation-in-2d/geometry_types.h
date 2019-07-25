/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H

#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"
#include "geometry/E2/polygon_e2.h"
#include "geometry/E2/transformation_e2.h"

typedef Point_E2< double >                     Point2d;
typedef Vector_E2< double >                   Vector2d;
typedef Polygon_E2< double >                 Polygon2d;
typedef Transformation_E2< double > Transformation_E2d;

#endif // GEOMETRY_TYPES_H
