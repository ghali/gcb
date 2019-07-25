#ifndef CLIP_2_H
#define CLIP_2_H

#include <iostream>
using std::cout; using std::endl;

// Geometry can be:
// Confirmed:
//     Geometry_E2<NT>
//     Geometry_E3<NT>
//     Geometry_T3<NT>
// Unconfirmed:
//     Geometry_S2<NT>

// Consider making:
//     geometry_T3/intersection_t3.h::
//     positive_half_space_clip(const Plane_T3<T>& plane, Segment_T3<T>& mySegment)
// geometry free.

// The following is the non-geometry-free version of template<typename Geometry> void split_2.
template<typename Geometry>
bool
positive_half_space_clip(const typename Geometry::Hyperplane & hyperplane,
                         typename Geometry::Polygon & a_polygon)
{
    typedef typename Geometry::Point                    Point;
    typedef typename Geometry::Segment                Segment;
    typedef typename Geometry::Hyperplane          Hyperplane;
    typedef typename Geometry::Polygon                Polygon;

    Polygon ret_polygon;

    {
        // quick exit
        if (a_polygon.is_empty())
            return false;
    }

    // std::vector<Point> points = polygon_vertices<Geometry>(a_polygon);

    typedef typename Polygon::Point_const_iterator PCI;
    const PCI points_begin = a_polygon.begin();
    const PCI points_end   = a_polygon.end();


    bool all_on_positive_side = true;
    bool all_on_oriented_boundary = true;
    bool all_on_negative_side = true;

    for(PCI vi = points_begin;
        vi != points_end; ++vi)
    {
        int s = oriented_side( hyperplane, *vi );

        switch(s) {
        case ON_POSITIVE_SIDE:
            all_on_negative_side = false;
            all_on_oriented_boundary = false;
            break;
        case ON_ORIENTED_BOUNDARY:
            break;
        case ON_NEGATIVE_SIDE:
            all_on_positive_side = false;
            all_on_oriented_boundary = false;
            break;
        }
    }

    if(all_on_positive_side || all_on_negative_side)
    {
        if(all_on_positive_side) // case (1)
        {
            // cout << a_polygon << endl;
            return true;
        }
        if(all_on_negative_side) // case (2)
        {
            a_polygon = Polygon();
            return false;
        }
    }

    if(all_on_oriented_boundary) // case (3)
    {
        a_polygon = Polygon();
        return false;
    }

    PCI pi = points_end - 1;
    PCI pj = points_begin;

    // typedef typename std::vector<Hyperplane>::const_iterator ESit;
    for( ; pj != points_end; ++pj)
    {
        int vertexI = oriented_side(hyperplane, *pi);
        int vertexJ = oriented_side(hyperplane, *pj);

        //----------------------------------------------------------------
        // Segment is on one side of the hyperplane only (possibly touching).
        // The following correctly handles the case when both points are ON_ORIENTED_BOUNDARY
        //----------------------------------------------------------------
        if( vertexI != ON_NEGATIVE_SIDE &&
            vertexJ != ON_NEGATIVE_SIDE )
        {
            if( vertexI == ON_ORIENTED_BOUNDARY ) { // distinct from splitting_2
                ret_polygon.push_back( *pi );
            }
            ret_polygon.push_back( *pj ); // case (4)
        }
        else if( vertexI != ON_POSITIVE_SIDE &&
                 vertexJ != ON_POSITIVE_SIDE )
        {
            // case (6)
            if( vertexJ == ON_ORIENTED_BOUNDARY ) {
            }
        }
        else
        {
            //----------------------------------------------------------------
            // Segment straddles the hyperplane
            //----------------------------------------------------------------

            // Point ipoint = intersection_of_lines( hyperplane, Segment(*pi, *pj) );
            Point ipoint = intersection_of_hyperplane_and_segment( hyperplane, Segment(*pi, *pj) );

            // going from +ve to -ve
            if(vertexI == ON_POSITIVE_SIDE && vertexJ == ON_NEGATIVE_SIDE) // case (8)
            {
                ret_polygon.push_back( ipoint );
            }

            // going from -ve to +ve
            if(vertexI == ON_NEGATIVE_SIDE && vertexJ == ON_POSITIVE_SIDE) // case (9)
            {
                ret_polygon.push_back( ipoint );
                ret_polygon.push_back( *pj );
            }
        }

        pi = pj;
    }

    a_polygon = ret_polygon;

    // cout << a_polygon << endl;

    return true;
}

#endif // CLIP_2_H
