/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_P2_H
#define PREDICATES_P2_H

#include <iostream>
using namespace std;

#include "misc/determinant.h"

template<typename T>
bool
are_colinear(const Point_P2<T>& p1,
             const Point_P2<T>& p2,
             const Point_P2<T>& p3)
{
    T d = determinant(p1.hx(), p1.hy(), p1.hw(),
                      p2.hx(), p2.hy(), p2.hw(),
                      p3.hx(), p3.hy(), p3.hw());

    T zero(static_cast<T>(0));
    return (d==zero);
}

template<typename T>
bool
are_cocircular(const Point_P2<T>& p0,
               const Point_P2<T>& p1,
               const Point_P2<T>& p2,
               const Point_P2<T>& p3)
{
    T unity(static_cast<T>(1));
    T d1 = determinant(p0.x() * p0.x(), p0.x(), p0.y(), unity,
                       p1.x() * p1.x(), p1.x(), p1.y(), unity,
                       p2.x() * p2.x(), p2.x(), p2.y(), unity,
                       p3.x() * p3.x(), p3.x(), p3.y(), unity);

    T zero(static_cast<T>(0));
    return (d1==zero);
}

#endif // PREDICATES_P2_H
