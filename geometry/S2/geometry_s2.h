// geometry_s2.h

#ifndef GEOMETRY_S2_H
#define GEOMETRY_S2_H

#include "geometry/S2/point_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/polygon_s2.h"
#include "geometry/S2/convex_polygon_s2.h"

template<typename NT>
struct Geometry_S2
{
    typedef NT NumberType;

    typedef Point_S2<NT>           Point;
    typedef Segment_S2<NT>         Hyperplane;
    typedef Segment_S2<NT>         Segment;
    typedef Polygon_S2<NT>         Polygon;
    typedef Convex_polygon_S2<NT>  Convex_polytope;
};

#endif // GEOMETRY_S2_H
