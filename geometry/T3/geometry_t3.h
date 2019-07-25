// geometry_t3.h

#ifndef GEOMETRY_T3_H
#define GEOMETRY_T3_H

#include "geometry/T3/point_t3.h"
#include "geometry/T3/plane_t3.h"
#include "geometry/T3/segment_t3.h"
#include "geometry/T3/polygon_t3.h"
// #include "geometry/T3/convex_polygon_t3.h"
// #include "geometry/T3/sub_hyperplane_t3.h"

template<typename NT>
struct Geometry_T3
{
    typedef NT NumberType;

    typedef Point_T3<NT>           Point;
    typedef Segment_T3<NT>         Segment;
    typedef Plane_T3<NT>           Hyperplane;
    typedef Polygon_T3<NT>         Polygon;
//    typedef Convex_polygon_T3<NT>  Convex_polytope;
//    typedef Sub_hyperplane_T3<NT>  Sub_hyperplane;
};

#endif // GEOMETRY_T3_H
