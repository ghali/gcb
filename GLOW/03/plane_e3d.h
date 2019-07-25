/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PLANE_E3D_H
#define PLANE_E3D_H

#include "point_E3d.h"
#include "vector_E3d.h"

class Plane_E3d {
    Vector_E3d N;
    double d;
public:
    Plane_E3d(const Point_E3d& p1, const Point_E3d& p2, const Point_E3d& p3)
    {
        Vector_E3d v1 = p2 - p1;
        Vector_E3d v2 = p3 - p2;
        N = cross_product(v1, v2);
        d = dot_product((Point_E3d(0,0,0) - p1), N);
    }

    Vector_E3d getNormal() const { return N; }
    double getD() const { return d; }
};

#endif // PLANE_E3D_H
