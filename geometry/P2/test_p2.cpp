/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/P2/point_p2.h"
#include "geometry/P2/line_p2.h"
#include "geometry/P2/intersection_p2.h"
#include "geometry/P2/predicates_p2.h"

#include "misc/epsilon_double.h"
typedef Epsilon_double MyDouble;

#include <cassert>

typedef Point_P2<MyDouble>   Point_P2d;
typedef Line_P2<MyDouble>     Line_P2d;

void test_point_equality()
{
    Point_P2d P1(2,3,1);
    Point_P2d P2(4,6,2);

    assert( P1 == P2 );
}

void test_line_equality()
{
    Line_P2d P1(2,3,1);
    Line_P2d P2(4,6,2);
    Line_P2d P3(-4,-6,-2);

    assert( P1 == P2 );
    assert( P1 == P3 );
    assert( P2 == P3 );
}

void test_incidence()
{
    Point_P2d P1(3,4,5);
    Point_P2d P2(6,7,8);

    Line_P2d L12(P1, P2);

    assert(L12.is_incident(P1));
    assert(L12.is_incident(P2));

    Point_P2d P3(9,10,11);
    Point_P2d P4(13,17,19);

    Line_P2d L34(P3, P4);

    assert(L34.is_incident(P3));
    assert(L34.is_incident(P4));

    Point_P2d i = intersection(L12, L34);

    assert(L12.is_incident(i));
    assert(L34.is_incident(i));

    assert(are_colinear(P1, P2, i));
    assert(are_colinear(P3, P4, i));
}

int main()
{
    test_point_equality();
    test_line_equality();
    test_incidence();
}
