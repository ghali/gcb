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
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/bbox_e2.h"

typedef Point_E2< int >        Point_E2i;

typedef Point_E2< double >     Point_E2d;
typedef Vector_E2< double >   Vector_E2d;
typedef Segment_E2< double > Segment_E2d;
typedef Bbox_E2< double >       Bbox_E2d;

// PostScript
#include "postscript/postscript.h"
typedef Postscript<double>  Postscript_d;

#endif // GEOMETRY_TYPES_H
