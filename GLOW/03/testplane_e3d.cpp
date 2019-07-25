/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "plane_E3d.h"
#include "predicates_E3d.h"

#include <cassert>

int main()
{
    Point_E3d P1(3,4,5), P2(5,3,1), P3(9,4,7);

    Plane_E3d P(P1, P2, P3);

    assert(!orientation(P, P1));

    Point_E3d P4(99,99,99);
    assert(orientation(P, P4));
}
