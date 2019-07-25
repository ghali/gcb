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

#include "geometry/P1/point_p1.h"
#include "geometry/P1/transformation_p1.h"
typedef Point_P1<MyDouble>                   Point_P1d;
typedef Transformation_P1<MyDouble> Transformation_P1d;

#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    {
        Point_P1d P1(4,5);
        Point_P1d P2(8,10);
        Point_P1d P3(-12,-15);

        assert(P1 == P2);
        assert(P1 == P3);
        assert(P1 == P3);
    }
}
