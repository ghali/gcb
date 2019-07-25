/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_E2D_H
#define SEGMENT_E2D_H

#include "point_e2d.h"

//----------------Segment_E2d_Begin----------------
class Segment_E2d {
private:
    Point_E2d _source, _target;
public:
    Segment_E2d() : _source(), _target() {}
    Segment_E2d( const Point_E2d& source, const Point_E2d& target )
        : _source(source), _target(target) {}
    Segment_E2d( const Segment_E2d& seg )
        : _source(seg._source), _target(seg._target) {}
//----------------Segment_E2d_End----------------
    Point_E2d source() const { return _source; }
    Point_E2d target() const { return _target; }
};

#endif // SEGMENT_E2D_H
