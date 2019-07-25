#ifndef INTERSECTION_S2_H
#define INTERSECTION_S2_H

#include "misc/determinant.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/circle_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/predicates_s2.h"
//#include "geometry/S2/projection_s2.h"

template<typename NT>
class Point_S2;

template<typename NT>
class Segment_S2;

template<typename NT>
class Circle_S2;

//----------------------------------------------------------------
template<typename NT>
Point_S2<NT>
intersection(const Circle_S2<NT>& l1, const Circle_S2<NT>& l2)
// precondition: circles are not parallel
{
    NT detx = + determinant(l1.y(), l1.z(), l2.y(), l2.z());
    NT dety = - determinant(l1.x(), l1.z(), l2.x(), l2.z());
    NT detw = + determinant(l1.x(), l1.y(), l2.x(), l2.y());

    return Point_S2<NT>(detx, dety, detw);

    // NT denom = determinant(l1.x(), l1.y(), l2.x(), l2.y());
    // assert(denom != 0);
    // 
    // NT detx = + determinant(l1.y(), l1.z(), l2.y(), l2.z());
    // NT dety = - determinant(l1.x(), l1.z(), l2.x(), l2.z());
    // 
    // return Point_S2<NT>(detx/denom, dety/denom);
}
//----------------------------------------------------------------

template<typename NT>
Point_S2<NT>
intersection_of_lines(const Segment_S2<NT>& seg1, const Segment_S2<NT>& seg2)
{
    Circle_S2<NT> l1(seg1.source(), seg1.target());
    Circle_S2<NT> l2(seg2.source(), seg2.target());

    return intersection(l1, l2);
}

#endif // INTERSECTION_S2_H
