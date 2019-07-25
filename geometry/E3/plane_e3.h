/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PLANE_E3_H
#define PLANE_E3_H

#include "geometry/E3/point_e3.h"
#include "geometry/E3/vector_e3.h"

template<typename NT>
class Plane_E3
{
    // a Point_E3<NT> P lying on the plane satisfies the equation:
    // P.V + d = 0
    Vector_E3<NT> V;
    NT d;

public:
    Plane_E3() : V(), d() {}
    Plane_E3(const Vector_E3<NT>& V, const NT& d) : V(V), d(d) {}

    Plane_E3(const Point_E3<NT>& p1,
             const Point_E3<NT>& p2,
             const Point_E3<NT>& p3)
    {
        Vector_E3<NT> v1 = p2 - p1;
        Vector_E3<NT> v2 = p3 - p2;
        V = cross_product(v1, v2);
        Point_E3<NT> O(0,0,0);
        d = dot_product((O - p1), V);
    }

    Vector_E3<NT> get_vector_e3() const { return V; }
    NT get_d() const { return d; }
};

#endif // PLANE_E3_H
