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
#include "geometry/E2/geometry_e2.h"
typedef Geometry_E2<MyDouble>    Geometry_E2d;
typedef Geometry_E2d::Point      Point_E2d;
typedef Geometry_E2d::Segment    Segment_E2d;
typedef Geometry_E2d::Polygon    Polygon_E2d;

// Geometry in E3
#include "geometry/E3/geometry_e3.h"
typedef Geometry_E3<MyDouble>    Geometry_E3d;
typedef Geometry_E3d::Point      Point_E3d;
typedef Geometry_E3d::Segment    Segment_E3d;
typedef Geometry_E3d::Polygon    Polygon_E3d;
#include "geometry/E3/interpolation_e3.h"
#include "geometry/E3/projection_e3.h"
#include "geometry/E3/vector_e3.h"
typedef Vector_E3<MyDouble>      Vector_E3d;
typedef Project_on_xy<MyDouble>           Project_on_xy_d;

// Geometry in T3
#include "geometry/T3/geometry_t3.h"
typedef Geometry_T3<MyDouble>    Geometry_T3d;
typedef Geometry_T3d::Point      Point_T3d;
typedef Geometry_T3d::Hyperplane Plane_T3d;
typedef Geometry_T3d::Segment    Segment_T3d;
typedef Geometry_T3d::Polygon    Polygon_T3d;
#include "geometry/T3/transformation_t3.h"
#include "geometry/T3/perspective_divide_t3.h"
typedef Transformation_T3<MyDouble>    Transformation_T3d;
typedef Perspective_divide<MyDouble> Perspective_divide_d;

// Geometry in S2
#include "geometry/S2/geometry_s2.h"
typedef Geometry_S2<MyDouble>    Geometry_S2d;
typedef Geometry_S2d::Point      Point_S2d;
typedef Geometry_S2d::Segment    Segment_S2d;
typedef Geometry_S2d::Polygon    Polygon_S2d;
#include "geometry/S2/circle_s2.h"
typedef Circle_S2<MyDouble>      Circle_S2d;
#include "geometry/S2/interpolation_s2.h"

// Indexed Face Set
#include "solid/ifs/indexed_face_set.h"
#include "solid/ifs/ifs_reader.h"
typedef Indexed_face_set<MyDouble> Indexed_face_set_d;
typedef IFS_reader<MyDouble>             IFS_reader_d;


