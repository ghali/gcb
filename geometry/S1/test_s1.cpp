/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "misc/epsilon_double.h"
#include "intersection_s1.h"
#include "predicates_s1.h"
#include "interpolation_s1.h"
#include "transformation_s1.h"

#include <cassert>
#include <iostream>
using namespace std;

typedef Epsilon_double MyDouble;

typedef Point_S1<MyDouble>       Point_S1d;
typedef Segment_S1<MyDouble>   Segment_S1d;
typedef Rotation_S1<MyDouble> Rotation_S1d;

void test_equality()
{
    Point_S1d P1(2,3);
    Point_S1d P2(4,6);
    Point_S1d P3(-4,-6);

    assert( P1 == P2 );
    assert( P1 != P3 );
    assert( P2 != P3 );
}

void test_point_point_classification()
{
    Point_S1d P1( 1, 3);
    Point_S1d P2( 1, 5);
    Point_S1d P3(-1,-3);
    assert( oriented_side(P1, P2) == ON_POSITIVE_SIDE );
    assert( oriented_side(P1, P3) == ON_ORIENTED_BOUNDARY );
}

void test_point_segment_classification()
{
    Segment_S1d S( Point_S1d(1.0, -5.0), Point_S1d(1.0, 4.0) );
    Point_S1d P(1.0, 2.0);
    assert( classify(S, P) == INSIDE_SET );
}

void test_interpolation()
{
    const Point_S1d P0( 1, 1);
    const Point_S1d P1(-1, 1);
    const Point_S1d P2(-1,-1);
    const Point_S1d P3( 1,-1);

    const Point_S1d P01 = interpolate(P0, P1, MyDouble(0.5));
    const Point_S1d P10 = interpolate(P1, P0, MyDouble(0.5));
    assert(P01 == P10);

    const Point_S1d P12 = interpolate(P1, P2, MyDouble(0.5));
    const Point_S1d P21 = interpolate(P2, P1, MyDouble(0.5));
    assert(P12 == P21);

    const Point_S1d P23 = interpolate(P2, P3, MyDouble(0.5));
    const Point_S1d P32 = interpolate(P3, P2, MyDouble(0.5));
    assert(P23 == P32);

    const Point_S1d P30 = interpolate(P3, P0, MyDouble(0.5));
    const Point_S1d P03 = interpolate(P0, P3, MyDouble(0.5));
    assert(P30 == P03);
}

int main()
{
    test_equality();
    test_point_point_classification();
    test_point_segment_classification();
    test_interpolation();
}
