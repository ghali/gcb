/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_S1_H
#define PREDICATES_S1_H

#include <iostream>
using namespace std;

#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"

#include "misc/orientation.h"
#include "misc/determinant.h"

// oriented_side returns ON_ORIENTED_BOUNDARY if p1 == p2 or p1 == p2.antipode()
//----------------S1_oriented_side_Begin----------------
template<typename NT>
Oriented_side
oriented_side(
              const Point_S1<NT>& p1,
              const Point_S1<NT>& p2)
{
    NT d = cross_product( p1.get_Direction_E2(), p2.get_Direction_E2() );

    return enum_Oriented_side(d);
}
//----------------S1_oriented_side_End----------------


//----------------S1_classify_Begin----------------
template<typename NT>
Set_membership
classify(
         const Segment_S1<NT>& segment,
         const Point_S1<NT>& P)
{
    const Point_S1<NT>& source = segment.source();
    const Point_S1<NT>& target = segment.target();

    Oriented_side side_of_source = oriented_side(source, P);
    Oriented_side side_of_target = oriented_side(target, P);

    if(
       side_of_source == ON_POSITIVE_SIDE &&
       side_of_target == ON_NEGATIVE_SIDE )
        return INSIDE_SET;
    else if(
            side_of_source == ON_ORIENTED_BOUNDARY &&
            inner_product(source.x(), source.y(), P.x(), P.y()) > 0
            ||
            side_of_target == ON_ORIENTED_BOUNDARY &&
            inner_product(target.x(), target.y(), P.x(), P.y()) > 0)
        return ON_SET_BOUNDARY;
    else
        return OUTSIDE_SET;
}
//----------------S1_classify_End----------------

template<typename NT>
Set_membership
classify_method2(const Segment_S1<NT>& segment,
                 const Point_S1<NT>& P)
{
    const NT zero(static_cast<NT>(0));

    NT inner = dot_product(segment.source().get_Direction_E2(), segment.target().get_Direction_E2());
    NT cross = cross_product(segment.source().get_Direction_E2(), segment.target().get_Direction_E2());

    NT inner2 = dot_product(segment.source().get_Direction_E2(), P.get_Direction_E2());
    NT cross2 = cross_product(segment.source().get_Direction_E2(), P.get_Direction_E2());

    if(cross > zero)
        return ((cross2 > zero) ? ( inner2 > inner ) : false);
    else
        return ((cross2 > zero) ? ( true ) : ( inner2 < inner ));
}

#endif // PREDICATES_S1_H
