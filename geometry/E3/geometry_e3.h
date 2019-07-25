// geometry_e3.h

#ifndef GEOMETRY_E3_H
#define GEOMETRY_E3_H

#include "geometry/E3/point_e3.h"
#include "geometry/E3/plane_e3.h"
#include "geometry/E3/segment_e3.h"
#include "geometry/E3/polygon_e3.h"
// #include "geometry/E3/convex_polygon_e3.h"
// #include "geometry/E3/sub_hyperplane_e3.h"

template<typename NT>
struct Geometry_E3
{
    typedef NT NumberType;

    typedef Point_E3<NT>           Point;
    typedef Segment_E3<NT>         Segment;
    typedef Plane_E3<NT>           Hyperplane; // Using Segment is more precise than line.
    typedef Polygon_E3<NT>         Polygon;
    // typedef Convex_polygon_E3<NT>  Convex_polytope;
    // typedef Sub_hyperplane_E3<NT>  Sub_hyperplane;
};

#endif // GEOMETRY_E3_H
