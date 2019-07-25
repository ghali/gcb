/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_E1_H
#define PREDICATES_E1_H

#include <iostream>
using namespace std;

#include "geometry/E1/point_e1.h"
#include "geometry/E1/segment_e1.h"

#include "misc/orientation.h"
#include "misc/determinant.h"

template<typename NT>
Oriented_side
oriented_side(const Point_E1<NT> & p1,
              const Point_E1<NT> & p2)
{
    NT d = p2.x() - p1.x();

    return enum_Oriented_side(d);
}

template<typename NT>
Set_membership
classify(const Segment_E1<NT> & segment,
         const Point_E1<NT> & point)
{
    Oriented_side s = oriented_side(segment.source(), point);
    Oriented_side t = oriented_side(segment.target(), point);

    if(s == ON_POSITIVE_SIDE && t == ON_NEGATIVE_SIDE)
        return INSIDE_SET;
    else if(s == ON_ORIENTED_BOUNDARY || t == ON_ORIENTED_BOUNDARY)
        return ON_SET_BOUNDARY;
    else
        return OUTSIDE_SET;
}

#endif // PREDICATES_E1_H
