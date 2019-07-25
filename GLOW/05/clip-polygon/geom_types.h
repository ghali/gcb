/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GEOM_TYPES_H
#define GEOM_TYPES_H

typedef double MyDouble;

#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/polygon_e2.h"

typedef Point_E2<   int >        Point_E2i;

typedef Point_E2<   MyDouble >   Point_E2d;
typedef Segment_E2< MyDouble > Segment_E2d;
typedef Line_E2< MyDouble >       Line_E2d;
typedef Polygon_E2< MyDouble > Polygon_E2d;

#endif // GEOM_TYPES_H
