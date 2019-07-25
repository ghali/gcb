/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_E2D_H
#define LINE_E2D_H

#include "point_e2d.h"
#include "segment_e2d.h"

//----------------Line_E2d_Begin----------------
class Line_E2d {
private:
    Point_E2d source, target;
public:
    Line_E2d() : source(), target() {}
    Line_E2d( const Point_E2d& _source, const Point_E2d _target )
        : source(_source), target(_target) {}
    Line_E2d( const Line_E2d& line )
        : source(line.source), target(line.target) {}
    Line_E2d( const Segment_E2d& seg )
        : source(seg.source()), target(seg.target()) {}
//----------------Line_E2d_End----------------
};

#endif // LINE_E2D_H
