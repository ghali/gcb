/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <iostream>
using namespace std;

#include "geometry/E2/point_e2.h"
#include "geometry/E2/line_e2.h"

#include "geometry/E2/intersection_e2.h"

int main()
{
    Line_E2<int> L1(Point_E2<int>(-6, -1), Point_E2<int>(2, 2));
    Line_E2<int> L2(Point_E2<int>(2, -2), Point_E2<int>(-2, 2));
    Point_E2<int> P = intersection(L1, L2);

    cout << P << endl;
}
