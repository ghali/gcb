/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_T2_H
#define PREDICATES_T2_H

#include <iostream>
using namespace std;

#include "misc/determinant.h"
#include "misc/orientation.h"

template<typename NT>
Oriented_side
oriented_side(const Point_T2<NT>& p1,
              const Point_T2<NT>& p2,
              const Point_T2<NT>& p3)
{
    NT unity(static_cast<NT>(1));
    NT d = determinant(p1.x(), p1.y(), unity,
                       p2.x(), p2.y(), unity,
                       p3.x(), p3.y(), unity);

    if(d > 0)
        return ON_POSITIVE_SIDE; // LEFT_TURN;
    else if(d < 0)
        return ON_NEGATIVE_SIDE; // RIGHT_TURN;
    else
        return ON_ORIENTED_BOUNDARY; // COLINEAR;
}

template<typename NT>
Oriented_side
oriented_side(const Line_T2<NT>& L,
              const Point_T2<NT>& p)
{
    return oriented_side(L.source(), L.target(), p);
}

#endif // PREDICATES_T2_H
