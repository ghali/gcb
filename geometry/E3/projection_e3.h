/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PROJECTION_E3_H
#define PROJECTION_E3_H

#include "geometry/E3/point_e3.h"
#include "geometry/E2/point_e2.h"
#include "geometry/E3/segment_e3.h"
#include "geometry/E2/segment_e2.h"

//----------------E3_Project_on_xy_Begin----------------
template<typename NT>
struct Project_on_xy
{
    Point_E2<NT> operator() (const Point_E3<NT>& p) const
    {
        return Point_E2<NT>(p.x(), p.y());
    }
//----------------E3_Project_on_xy_End----------------

    Segment_E2<NT> operator() (const Segment_E3<NT>& s) const
    {
        return Segment_E2<NT>(operator() (s.source()),
                              operator() (s.target()));
    }
};

#endif // PROJECTION_E3_H
