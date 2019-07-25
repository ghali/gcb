// geometry_s1.h

#ifndef GEOMETRY_S1_H
#define GEOMETRY_S1_H

#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"
#include "geometry/S1/topo_segment_s1.h"

template<typename NT>
struct Geometry_S1
{
    typedef NT NumberType;

    typedef Point_S1<NT>         Point;
    typedef Point_S1<NT>         Hyperplane;
    typedef Topo_segment_S1<NT>  Convex_polytope;
    typedef Point_S1<NT>         Sub_hyperplane;
};

#endif // GEOMETRY_S1_H
