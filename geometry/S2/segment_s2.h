/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_S2_H
#define SEGMENT_S2_H

#include <cassert>

#include "geometry/S2/point_s2.h"
#include "geometry/S2/circle_s2.h"

//----------------Segment_S2_Begin----------------
template<typename NT>
class Segment_S2
{
    Point_S2<NT> _source, _target;
    Circle_S2<NT> _circle;
public:
    Segment_S2() : _source(), _target() {}
    Segment_S2(
               const Point_S2<NT>& source,
               const Point_S2<NT>& target)
        : _source(source), _target(target)
    {
        assert(_source!=_target && _source!=-_target);
        Direction_E3<NT> D = cross_product(
                                           _source.get_Direction_E3(),
                                           _target.get_Direction_E3());
        _circle = Circle_S2<NT>(D);
    }
    Segment_S2(
               const Point_S2<NT>& source,
               const Point_S2<NT>& target,
               const Circle_S2<NT>& circle)
        : _source(source), _target(target), _circle(circle)
    {
        assert(_circle.contains(_source) && _circle.contains(_target));
    }
//----------------Segment_S2_End----------------

    Point_S2<NT> source() const { return _source; }
    Point_S2<NT> target() const { return _target; }

    Circle_S2<NT> get_Circle_S2() const { return _circle; }

    bool operator==(const Segment_S2<NT>& s) const {
        return (this == &s) ||
            (_source == s._source && _target == s._target && _circle == s._circle);
    }

    NT getAngle() const {
        // Precondition: segment is no larger than half a circle
        // Calculate angle between the two spherical points P1 and P2.
        double angle =  acos(dot_product(_source.get_Direction_E3(),
                                         _target.get_Direction_E3()));
        return angle;
    }

    Point_S2<NT>
    get_midpoint() const {
        // Precondition: segment is shorter than half a circle
        return (_source.get_Direction_E3() + _target.get_Direction_E3());
    }
public:
    typedef NT              eNT;
    typedef Point_S2<NT> ePoint;
};

#endif // SEGMENT_S2_H
