
#ifndef INTERSECTION_E3
#define INTERSECTION_E3

#include <cassert>

#include "point_e3.h"
#include "plane_e3.h"
#include "segment_e3.h"
#include "triangle_e3.h"
#include "predicates_e3.h"

template<typename NT>
Point_E3<NT>
intersection(const Plane_E3<NT> & K,
             const Line_E3<NT> & L)
// Precondition: plane and line are not parallel.
{
    // A point P is on K if it satisfies:
    //     dot(P, K.V()) + K.d() = 0
    // A point P is on L if it satisfies:
    //     P = L.source() + alpha (L.target() - L.source())
    // Substituting:
    //     dot(L.source() + alpha (L.target() - L.source()), K.V()) + K.d() = 0
    //     dot(L.source() + alpha (L.target() - L.source()), K.V()) =  - K.d()
    //     dot(L.source(), K.V()) + dot(alpha (L.target() - L.source()), K.V()) =  - K.d()
    //     alpha dot((L.target() - L.source()), K.V()) =  - K.d() - dot(L.source(), K.V())
    //     alpha  =  ( - K.d() - dot(L.source(), K.V()) ) / dot((L.target() - L.source()), K.V())
    const Point_E3<NT> O(0,0,0);
    NT num = - K.get_d() - dot_product((L.source() - O), K.get_vector_e3());
    NT denom = dot_product((L.target() - L.source()), K.get_vector_e3());
    assert( denom != 0 );
    NT alpha = num / denom;
    Point_E3<NT> P = L.source() + (L.target() - L.source()) * alpha;
    return P;
}

enum Intersection_type_E3
{
    NO_INTERSECTION,
    IS_POINT_E3,
    IS_SEGMENT_E3,
    IS_TRIANGLE_E3
};

// The following function is not yet optimized.
template<typename NT>
Intersection_type_E3
intersection(const Plane_E3<NT> & P,
             const Triangle_E3<NT> & T,
             Point_E3<NT> & Pint,
             Segment_E3<NT> & Pseg)
{
    const Oriented_side o0 = oriented_side(P, T.P0());
    const Oriented_side o1 = oriented_side(P, T.P1());
    const Oriented_side o2 = oriented_side(P, T.P2());
    // std::cout << "o0:" << o0 << " o1:" << o1 << " o2:" << o2 << std::endl;

    // No intersection
    if(o0 == ON_POSITIVE_SIDE
       && o1 == ON_POSITIVE_SIDE
       && o2 == ON_POSITIVE_SIDE)
        return NO_INTERSECTION;
    else if(o0 == ON_NEGATIVE_SIDE
            && o1 == ON_NEGATIVE_SIDE
            && o2 == ON_NEGATIVE_SIDE)
        return NO_INTERSECTION;
    // Intersects in a boundary segment
    else if(o0 == ON_ORIENTED_BOUNDARY && o1 == ON_ORIENTED_BOUNDARY) {
        Pseg = Segment_E3<NT>(T.P0(), T.P1());
        return IS_SEGMENT_E3;
    }
    else if(o0 == ON_ORIENTED_BOUNDARY && o2 == ON_ORIENTED_BOUNDARY) {
        Pseg = Segment_E3<NT>(T.P0(), T.P2());
        return IS_SEGMENT_E3;
    }
    else if(o1 == ON_ORIENTED_BOUNDARY && o2 == ON_ORIENTED_BOUNDARY) {
        Pseg = Segment_E3<NT>(T.P1(), T.P2());
        return IS_SEGMENT_E3;
    }
    // Intersects in a boundary point
    else if(o0 == ON_ORIENTED_BOUNDARY) {
        Pint = T.P0();
        return IS_POINT_E3;
    }
    else if(o1 == ON_ORIENTED_BOUNDARY) {
        Pint = T.P1();
        return IS_POINT_E3;
    }
    else if(o2 == ON_ORIENTED_BOUNDARY) {
        Pint = T.P2();
        return IS_POINT_E3;
    }
    // Intersects in an interior segment
    else if(( o0 == ON_NEGATIVE_SIDE
              && o1 == ON_POSITIVE_SIDE
              && o2 == ON_POSITIVE_SIDE)
            ||
            ( o0 == ON_POSITIVE_SIDE
              && o1 == ON_NEGATIVE_SIDE
              && o2 == ON_NEGATIVE_SIDE))
    {
        Point_E3<NT> P01 = intersection(P, Line_E3<NT>(T.P0(), T.P1()));
        Point_E3<NT> P02 = intersection(P, Line_E3<NT>(T.P0(), T.P2()));
        Pseg = Segment_E3<NT>(P01, P02);
        return IS_SEGMENT_E3;
    }
    else if(( o1 == ON_NEGATIVE_SIDE
              && o0 == ON_POSITIVE_SIDE
              && o2 == ON_POSITIVE_SIDE)
            ||
            ( o1 == ON_POSITIVE_SIDE
              && o0 == ON_NEGATIVE_SIDE
              && o2 == ON_NEGATIVE_SIDE))
    {
        Point_E3<NT> P10 = intersection(P, Line_E3<NT>(T.P1(), T.P0()));
        Point_E3<NT> P12 = intersection(P, Line_E3<NT>(T.P1(), T.P2()));
        Pseg = Segment_E3<NT>(P10, P12);
        return IS_SEGMENT_E3;
    }
    else if(( o2 == ON_NEGATIVE_SIDE
              && o0 == ON_POSITIVE_SIDE
              && o1 == ON_POSITIVE_SIDE)
            ||
            ( o2 == ON_POSITIVE_SIDE
              && o0 == ON_NEGATIVE_SIDE
              && o1 == ON_NEGATIVE_SIDE))
    {
        Point_E3<NT> P20 = intersection(P, Line_E3<NT>(T.P2(), T.P0()));
        Point_E3<NT> P21 = intersection(P, Line_E3<NT>(T.P2(), T.P1()));
        Pseg = Segment_E3<NT>(P20, P21);
        return IS_SEGMENT_E3;
    }
    // Coincident
    assert(o0 == ON_ORIENTED_BOUNDARY
           && o1 == ON_ORIENTED_BOUNDARY
           && o2 == ON_ORIENTED_BOUNDARY);
    return IS_TRIANGLE_E3;
}

#endif // INTERSECTION_E3
