/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_E3D_H
#define PREDICATES_E3D_H

#include "point_E3d.h"
#include "dominant_E3d.h"
#include "misc/determinant.h"
//----------------dominant_Vector_E3d_Begin----------------
Dominant_E3 dominant(const Vector_E3d& V)
{
    return dominant(V.x(), V.y(), V.z());
}
//----------------dominant_Vector_E3d_End----------------

enum Orientation
    {
        ON_NEGATIVE_SIDE = -1,
        ON_ORIENTED_BOUNDARY,
        ON_POSITIVE_SIDE
    };

template<typename T>
Orientation
orientation(const Point_E3d& p1,
            const Point_E3d& p2,
            const Point_E3d& p3,
            const Point_E3d& p4)
{
    double d = determinant(p1.x(), p1.y(), p1.z(), 1.0,
                           p2.x(), p2.y(), p2.z(), 1.0,
                           p3.x(), p3.y(), p3.z(), 1.0,
                           p4.x(), p4.y(), p4.z(), 1.0);

    if(d > 0)
        return ON_POSITIVE_SIDE;
    else if(d < 0)
        return ON_NEGATIVE_SIDE;
    else
        return ON_ORIENTED_BOUNDARY;
}

Orientation
orientation(const Plane_E3d& plane,
            const Point_E3d& point)
{
    Vector_E3d V = plane.getNormal();
    double d = V.x() * point.x() + V.y() * point.y() + V.z() * point.z() + plane.getD();

    if(d > 0)
        return ON_POSITIVE_SIDE;
    else if(d < 0)
        return ON_NEGATIVE_SIDE;
    else
        return ON_ORIENTED_BOUNDARY;
}

#endif // PREDICATES_E3D_H
