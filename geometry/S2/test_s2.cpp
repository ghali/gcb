/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/S2/point_s2.h"
#include "geometry/S2/circle_s2.h"
#include "geometry/S3/quaternion.h"
#include "geometry/S2/transformation_s2.h"

#include "misc/epsilon_double.h"

#include <cassert>

typedef Epsilon_double MyDouble;

typedef Point_S2<MyDouble>         Point_S2d;
typedef Circle_S2<MyDouble>       Circle_S2d;
typedef Direction_E3<MyDouble> Direction_E3d;
typedef Quaternion<MyDouble>    Quaternion_d;
typedef Rotation_S2<MyDouble>   Rotation_S2d;

void test_equality()
{
    Point_S2d P1(2,3,5);
    Point_S2d P2(4,6,10);
    Point_S2d P3(-4,-6,-10);

    assert( P1 == P2 );
    assert( P1 != P3 );
    assert( P2 != P3 );
}

void test_bases()
{
    Circle_S2d c1(2,3,4);

    Point_S2d c1b1 = c1.base1();
    Point_S2d c1b2 = c1.base2();

    assert( inner_product(c1.get_Point_S2(), c1b1) == 0 );
    assert( inner_product(c1.get_Point_S2(), c1b2) == 0 );
    assert( inner_product(c1b1, c1b2) == 0 );
}

void test_rotate_1()
{
    Point_S2d P(1,2,3);
    Rotation_S2d R(M_PI/2.0, Direction_E3d(1,2,3));
    Point_S2d Q = R.rotate(P);
    assert(P == Q);
}

void test_rotate_2()
{
    Point_S2d P(1,0,0);
    Rotation_S2d R(- M_PI/2.0, Direction_E3d(0,1,0));
    Point_S2d Q(0,0,1);
    Point_S2d Pr = R.rotate(P);
    assert(Pr == Q);
}

int main()
{
    test_equality();
    test_bases();
    test_rotate_1();
    test_rotate_2();
}
