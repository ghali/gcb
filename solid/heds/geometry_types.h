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

#include "geometry/E3/point_e3.h"
#include "geometry/E3/direction_e3.h"
#include "geometry/E3/bbox_e3.h"
#include "misc/color_3.h"

typedef Color_3<float>           Color_3f;
typedef float                  NumberType;

typedef Point_E3<float>         Point_E3f;
typedef Vector_E3<float>       Vector_E3f;
typedef Direction_E3<float> Direction_E3f;
typedef Bbox_E3<float>           Bbox_E3f;

#endif // GEOMETRY_TYPES_H
