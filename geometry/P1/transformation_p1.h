/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_P1_H
#define TRANSFORMATION_P1_H

#include "geometry/P1/point_p1.h"

template<typename NT>
class Transformation_P1
{
    NT m00, m01;
    NT m10, m11;
public:
    Transformation_P1(const NT& m00 = 1, const NT& m01 = 0,
                      const NT& m10 = 0, const NT& m11 = 1)
        : m00(m00), m01(m01), m10(m10), m11(m11)
    {}

    Point_P1<NT> transform(const Point_P1<NT>& P) const
    {
        return Point_P1<NT>(m00 * P.hx() + m01 * P.hw(),
                            m10 * P.hx() + m11 * P.hw());
    }

    Point_P1<NT> operator()(const Point_P1<NT>& P) const
    {
        return transform(P);
    }
};

#endif // TRANSFORMATION_P1_H
