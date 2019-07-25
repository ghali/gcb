/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/E3/direction_e3.h"

#include "geometry/S3/quaternion.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/circle_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/transformation_s2.h"

typedef Direction_E3<double> Direction_E3d;

typedef Quaternion<double>     Quaterniond;

typedef Point_S2<double>          PointS2d;
typedef Circle_S2<double>        CircleS2d;
typedef Segment_S2<double>      SegmentS2d;
typedef Rotation_S2<double>    RotationS2d;
