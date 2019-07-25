// geometry_e2.h

#ifndef GEOMETRY_E2_H
#define GEOMETRY_E2_H

#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/polygon_e2.h"
#include "geometry/E2/convex_polygon_e2.h"
#include "geometry/E2/sub_hyperplane_e2.h"

template<typename NT>
struct Geometry_E2
{
    typedef NT NumberType;

    typedef Point_E2<NT>           Point;
    typedef Segment_E2<NT>         Segment;
    typedef Segment_E2<NT>         Hyperplane; // Using Segment is more precise than line.
    // typedef Line_E2<NT>         Hyperplane; // Using Segment is more precise than line.
    typedef Polygon_E2<NT>         Polygon;
    typedef Convex_polygon_E2<NT>  Convex_polytope;
    typedef Sub_hyperplane_E2<NT>  Sub_hyperplane;
};

#endif // GEOMETRY_E2_H
