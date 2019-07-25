/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERSECTION_P3_H
#define INTERSECTION_P3_H

#include <cassert>

#include "misc/determinant.h"
#include "geometry/P3/point_p3.h"
#include "geometry/P3/plane_p3.h"
#include "geometry/P3/predicates_p3.h"

template<typename T>
class Point_P3;

template<typename T>
class Plane_P3;

template<typename T>
Point_P3<T>
intersection(const Plane_P3<T>& l1, const Plane_P3<T>& l2, const Plane_P3<T>& l3)
{
    T detx = + determinant(l1.Y(), l1.Z(), l1.W(),
                           l2.Y(), l2.Z(), l2.W(),
                           l3.Y(), l3.Z(), l3.W());
    T dety = - determinant(l1.X(), l1.Z(), l1.W(),
                           l2.X(), l2.Z(), l2.W(),
                           l3.X(), l3.Z(), l3.W());
    T detz = + determinant(l1.X(), l1.Y(), l1.W(),
                           l2.X(), l2.Y(), l2.W(),
                           l3.X(), l3.Y(), l3.W());
    T detw = - determinant(l1.X(), l1.Y(), l1.Z(),
                           l2.X(), l2.Y(), l2.Z(),
                           l3.X(), l3.Y(), l3.Z());

    return Point_P3<T>(detx, dety, detz, detw);
}

#endif // INTERSECTION_P3_H
