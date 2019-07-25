#ifndef POLYGON_VERTICES_H
#define POLYGON_VERTICES_H

#include <vector>

// The client should include whichever intersection routines are necessary.

template<typename Geometry>
std::vector<typename Geometry::Point>
polygon_vertices(const typename Geometry::Convex_polytope & a_polygon)
{
    typedef typename Geometry::Point                    Point;
    typedef typename Geometry::Hyperplane          Hyperplane;

    std::vector<Point> points;
    const std::vector<Hyperplane> a_polygon_lines = a_polygon.get_lines();
    const std::vector<Hyperplane> & lines = a_polygon_lines;
    Point  ipoint = intersection_of_lines(*(lines.end() - 1), *(lines.begin()));

// hack
//    if(ipoint.z() < 0)
//        ipoint = - ipoint;

    points.push_back(ipoint);

    typedef typename std::vector<Hyperplane>::const_iterator ESit;
    for(ESit I = lines.begin();
        I != lines.end()-1; ++I)
    {
        Point  ipoint = intersection_of_lines(*I, *(I+1));

// hack
//    if(ipoint.z() < 0)
//        ipoint = - ipoint;


        points.push_back(ipoint);
    }

    return points;
}

#endif // POLYGON_VERTICES_H
