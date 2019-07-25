/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PERSPECTIVE_DIVIDE_T3_H
#define PERSPECTIVE_DIVIDE_T3_H

#include "geometry/T3/point_t3.h"
#include "geometry/E3/point_e3.h"

template<typename NT>
struct Perspective_divide
{
    Point_E3<NT> operator() (const Point_T3<NT>& p) const
    {
        return Point_E3<NT>(p.hx()/p.hw(),
                            p.hy()/p.hw(),
                            p.hz()/p.hw());
    }
};

#endif // PERSPECTIVE_DIVIDE_T3_H
