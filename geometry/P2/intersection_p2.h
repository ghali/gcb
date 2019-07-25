/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERSECTION_P2_H
#define INTERSECTION_P2_H

#include <cassert>

#include "misc/determinant.h"
#include "geometry/P2/point_p2.h"
#include "geometry/P2/line_p2.h"

template<typename T>
class Point_P2;

template<typename T>
class Line_P2;

//----------------P2_intersection_Begin----------------
template<typename T>
Point_P2<T>
intersection(const Line_P2<T>& l1, const Line_P2<T>& l2)
{
    T detx = + determinant(l1.Y(), l1.W(),  l2.Y(), l2.W());
    T dety = - determinant(l1.X(), l1.W(),  l2.X(), l2.W());
    T detw = + determinant(l1.X(), l1.Y(),  l2.X(), l2.Y());

    assert((detx != 0) || (dety != 0) || (detw != 0));

    return Point_P2<T>(detx, dety, detw);
}
//----------------P2_intersection_End----------------

#endif // INTERSECTION_P2_H
