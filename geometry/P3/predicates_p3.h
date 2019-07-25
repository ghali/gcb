/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_P3_H
#define PREDICATES_P3_H

#include <iostream>
using namespace std;

#include "misc/orientation.h"
#include "misc/determinant.h"

#include "geometry/P3/point_p3.h"
#include "geometry/P3/plane_p3.h"
#include "geometry/P3/line_p3.h"

template<typename T>
bool
are_coplanar(const Point_P3<T>& p1,
             const Point_P3<T>& p2,
             const Point_P3<T>& p3,
             const Point_P3<T>& p4)
{
    T d = determinant(p1.hx(), p1.hy(), p1.hz(), p1.hw(),
                      p2.hx(), p2.hy(), p2.hz(), p2.hw(),
                      p3.hx(), p3.hy(), p3.hz(), p3.hw(),
                      p4.hx(), p4.hy(), p4.hz(), p4.hw());

    T zero(static_cast<T>(0));
    return (d==zero);
}

template<typename T>
bool
are_cospherical(const Point_P3<T>& p0,
                const Point_P3<T>& p1,
                const Point_P3<T>& p2,
                const Point_P3<T>& p3,
                const Point_P3<T>& p4)
{
    T unity(static_cast<T>(1));
    T d1 = determinant(p0.x() * p0.x(), p0.x(), p0.y(), p0.z(), unity,
                       p1.x() * p1.x(), p1.x(), p1.y(), p1.z(), unity,
                       p2.x() * p2.x(), p2.x(), p2.y(), p2.z(), unity,
                       p3.x() * p3.x(), p3.x(), p3.y(), p3.z(), unity,
                       p4.x() * p4.x(), p4.x(), p4.y(), p4.z(), unity);

    T zero(static_cast<T>(0));
    return (d1==zero);
}

template<typename T>
bool
are_incident(const Point_P3<T>& P,
             const Plane_P3<T>& pl)
{
    const T d = P.hx() * pl.X() + P.hy() * pl.Y() + P.hz() * pl.Z() + P.hw() * pl.W();
    const T zero(0);

    return (d == zero);
}

template<typename T>
bool
are_incident(const Line_P3<T>& L,
             const Line_P3<T>& M)
{
    // synonyms: "have point in common", "have plane in common"

    const T d = 
        + L.pxw() * M.pyz()
        + L.pyz() * M.pxw()
        - L.pyw() * M.pxz()
        - L.pxz() * M.pyw()
        + L.pxy() * M.pzw()
        + L.pzw() * M.pxy();
    const T zero(0);

    return (d == zero);
}

#endif // PREDICATES_P3_H
