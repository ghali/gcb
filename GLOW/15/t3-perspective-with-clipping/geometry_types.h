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

// Geometry in E2
#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/bbox_e2.h"
typedef Point_E2<MyDouble>      Point_E2d;
typedef Segment_E2<MyDouble>  Segment_E2d;
typedef Bbox_E2<MyDouble>        Bbox_E2d;

// Geometry in E3
#include "geometry/E3/point_e3.h"
#include "geometry/E3/segment_e3.h"
#include "geometry/E3/interpolation_e3.h"
#include "geometry/E3/projection_e3.h"
typedef Point_E3<MyDouble>      Point_E3d;
typedef Segment_E3<MyDouble>  Segment_E3d;

// Geometry in T3
#include "geometry/T3/transformation_t3.h"
#include "geometry/T3/perspective_divide_t3.h"
typedef Point_T3<MyDouble>                      Point_T3d;
typedef Plane_T3<MyDouble>                      Plane_T3d;
typedef Segment_T3<MyDouble>                  Segment_T3d;
typedef Transformation_T3<MyDouble>    Transformation_T3d;
typedef Perspective_divide<MyDouble> Perspective_divide_d;
typedef Project_on_xy<MyDouble>           Project_on_xy_d;

// Indexed Face Set
#include "solid/ifs/indexed_face_set.h"
#include "solid/ifs/ifs_reader.h"
typedef Indexed_face_set<MyDouble> Indexed_face_set_d;
typedef IFS_reader<MyDouble>             IFS_reader_d;

// PostScript
#include "postscript/postscript.h"
typedef Postscript<MyDouble> Postscript_d;
