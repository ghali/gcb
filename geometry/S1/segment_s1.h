/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_S1_H
#define SEGMENT_S1_H

#include <cmath>
#include <iostream>

#include "misc/orientation.h"
#include "geometry/S1/point_s1.h"

// Reasons to restrict a segment_S1 to remain smaller than a semi-circle:
// 1- Splitting is simplified; at most 2 parts can result.
// 2- Interpolation is simplified.

//----------------Segment_S1_Begin----------------
template<typename NT>
class Segment_S1
{
    Point_S1<NT> _source, _target;
public:
    Segment_S1(
               const Point_S1<NT>& source = Point_S1<NT>(1,0),
               const Point_S1<NT>& target = Point_S1<NT>(0,1))
        : _source(source), _target(target)
    {}

    Point_S1<NT> source() const { return _source; }
    Point_S1<NT> target() const { return _target; }
};
//----------------Segment_S1_End----------------

template<typename T>
std::ostream&
operator<<(std::ostream& os, const Segment_S1<T>& seg) {
    return os << seg.source() << " -- " << seg.target();
}

#endif // SEGMENT_S1_H
