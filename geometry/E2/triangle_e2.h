/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRIANGLE_E2_H
#define TRIANGLE_E2_H

#include "geometry/E2/point_e2.h"
#include "geometry/E2/predicates_e2.h"
#include "misc/determinant.h"

template<typename NT>
class Triangle_E2
{
    Point_E2<NT> p0;
    Point_E2<NT> p1;
    Point_E2<NT> p2;
public:
    Triangle_E2(const Point_E2<NT>& q0, const Point_E2<NT>& q1, const Point_E2<NT>& q2)
    {
        p0 = q0; p1 = q1; p2 = q2;
    }

    Point_E2<NT> P0() const { return p0; }
    Point_E2<NT> P1() const { return p1; }
    Point_E2<NT> P2() const { return p2; }


    Point_E2<NT> vertex(int i) const
    {
        switch(i) {
        case 0: return p0;
        case 1: return p1;
        case 2: return p2;
        }
    }

    NT get_signed_area() const
    {
        NT unity(1.0);
        NT half(1.0/2.0);
        NT area = half * determinant(p0.x(), p0.y(), unity,
                                     p1.x(), p1.y(), unity,
                                     p2.x(), p2.y(), unity);
        return area;
    }
};

#endif // TRIANGLE_E2_H
