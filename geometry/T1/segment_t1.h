/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_T1_H
#define SEGMENT_T1_H

#include "geometry/T1/point_t1.h"

template<typename NT>
class Segment_T1
{
    Point_T1<NT> _source, _target;
public:
    Segment_T1(const Point_T1<NT>& source, const Point_T1<NT>& target)
        : _source(source), _target(target)
    {}

    Point_T1<NT> source() { return _source; }
    Point_T1<NT> target() { return _target; }
};

#endif // SEGMENT_T1_H
