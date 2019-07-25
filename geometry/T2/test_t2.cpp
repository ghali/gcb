/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/T2/point_t2.h"

#include "misc/epsilon_double.h"

#include <cassert>

typedef Epsilon_double MyDouble;

typedef Point_T2<MyDouble>         Point_T2d;

void test_equality()
{
    Point_T2d P1(2,3,5);
    Point_T2d P2(4,6,10);
    Point_T2d P3(-4,-6,-10);

    assert( P1 == P2 );
    assert( P1 != P3 );
    assert( P2 != P3 );
}

int main()
{
    test_equality();
}
