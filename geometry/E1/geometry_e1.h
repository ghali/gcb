// geometry_e1.h

#ifndef GEOMETRY_E1_H
#define GEOMETRY_E1_H

#include "geometry/E1/point_e1.h"
#include "geometry/E1/topo_segment_e1.h"

template<typename NT>
struct Geometry_E1
{
    typedef NT NumberType;

    typedef Point_E1<NT>         Point;
    typedef Point_E1<NT>         Hyperplane;
    typedef Topo_segment_E1<NT>  Convex_polytope;
};

#endif // GEOMETRY_E1_H
