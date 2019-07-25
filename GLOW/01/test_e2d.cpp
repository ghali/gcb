/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "point_e2d.h"
#include "vector_e2d.h"
#include "segment_e2d.h"
#include "direction_e2d.h"
#include "line_e2d.h"

#include <cassert>

void test_point_equality()
{
    Point_E2d P1(2,1);
    Point_E2d P2(7,4);
    Point_E2d & P3 = P1;

    assert( P1 == P1 );
    assert( P1 == P3 );
    assert( P1 != P2 );
}

void test_point_equality_through_reference()
{
    Point_E2d P(1,2);

    const Point_E2d & Q = P;
    assert( Q == Q );
}

void test_operators()
{
    Point_E2d p1(2,1), p2(7,4);
    Vector_E2d v1(3,5), v2(4,8);

    Point_E2d p3 = p1 + v1;
    assert( p3 == Point_E2d(5,6) );

    Vector_E2d v3 = v1 + v2;
    assert( v3 == Vector_E2d(7,13) );

    Vector_E2d v4 = p3 - p1;
    assert( v4 == v1 );
}

int main()
{
    test_point_equality();
    test_point_equality_through_reference();
    test_operators();
}
