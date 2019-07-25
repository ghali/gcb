/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_T1_H
#define TRANSFORMATION_T1_H

#include "geometry/T1/point_t1.h"
#include "geometry/T1/segment_t1.h"

template<typename NT>
class Transformation_T1
{
    NT m00, m01;
    NT m10, m11;
public:
    Transformation_T1(const NT& m00 = 1, const NT& m01 = 0,
                      const NT& m10 = 0, const NT& m11 = 1)
        : m00(m00), m01(m01), m10(m10), m11(m11)
    {}

    Point_T1<NT> transform(const Point_T1<NT>& P) const
    {
        return Point_T1<NT>(m00 * P.hx() + m01 * P.hw(),
                            m10 * P.hx() + m11 * P.hw());
    }

    Point_T1<NT> operator()(const Point_T1<NT>& P) const
    {
        return transform(P);
    }

    Segment_T1<NT> transform(const Segment_T1<NT>& s) const
    {
        return Segment_T1<NT>(transform(s.source()), transform(s.target()));
    }

    Segment_T1<NT> operator()(const Segment_T1<NT>& s) const
    {
        return transform(s);
    }
};

#endif // TRANSFORMATION_T1_H
