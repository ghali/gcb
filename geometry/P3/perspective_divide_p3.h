/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PERSPECTIVE_DIVIDE_P3_H
#define PERSPECTIVE_DIVIDE_P3_H

#include "geometry/P3/point_p3.h"
#include "geometry/E3/point_e3.h"

//----------------P3_perspective_divide_Begin----------------
template<typename NT>
struct Perspective_divide
{
    Point_E3<NT> operator() (const Point_P3<NT>& p) const
    {
        return Point_E3<NT>(
                            p.hx()/p.hw(),
                            p.hy()/p.hw(),
                            p.hz()/p.hw());
    }
};
//----------------P3_perspective_divide_End----------------

#endif // PERSPECTIVE_DIVIDE_P3_H
