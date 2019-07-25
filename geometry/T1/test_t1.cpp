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
typedef Epsilon_double MyDouble;

#include "geometry/T1/point_t1.h"
#include "geometry/T1/transformation_t1.h"
typedef Point_T1<MyDouble>                   Point_T1d;
typedef Transformation_T1<MyDouble> Transformation_T1d;

#include "geometry/T1/segment_t1.h"
typedef Segment_T1<MyDouble>               Segment_T1d;

#include <cassert>
#include <iostream>
using namespace std;

void test_equality()
{
    Point_T1d P1(4,5);
    Point_T1d P2(8,10);
    Point_T1d P3(-12,-15);

    assert(P1 == P2);
    assert(P1 != P3);
    assert(P2 != P3);
}

void test_order()
{
    Point_T1d P1(2);
    Point_T1d P2(5);
    Point_T1d P3(-3);

    assert(P1 < P2);
    assert(P3 < P1);

    Point_T1d P4(2);
    Point_T1d P5(5);
    Point_T1d P6(-3);

    assert(P1 < P2);
    assert(P3 < P1);
}

int main()
{
    test_equality();
    test_order();
}
