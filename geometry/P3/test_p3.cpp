/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/P3/point_p3.h"
#include "geometry/P3/plane_p3.h"
#include "geometry/P3/line_p3.h"
#include "geometry/P3/intersection_p3.h"
#include "geometry/P3/predicates_p3.h"

#include "geometry/P3/transformation_p3.h"

#include "misc/epsilon_double.h"

#include <cassert>
#include <iostream>
using namespace std;

typedef Epsilon_double MyDouble;

typedef Point_P3<MyDouble>   Point_P3d;
typedef Plane_P3<MyDouble>   Plane_P3d;
typedef Line_P3<MyDouble>     Line_P3d;

typedef Transformation_P3<MyDouble> Transformation_P3d;

void test_equality()
{
    Point_P3d P1(2,3,4,5);
    Point_P3d P2(-4,-6,-8,-10);

    assert( P1 == P2 );
}

void test_incidence()
{
    // Test
    //     are_incident(const Point_P3<T>& P, const Plane_P3<T>& pl)
    //     are_coplanar( four points )
    //     are_incident(const Line_P3<T>& L1, const Line_P3<T>& L2)

    Point_P3d P1(3,4,5,6);
    Point_P3d P2(6,7,8,9);
    Point_P3d P3(7,8,9,11);

    Plane_P3d L123(P1, P2, P3);

    assert(are_incident(P1, L123));
    assert(are_incident(P2, L123));
    assert(are_incident(P3, L123));

    {
        Line_P3d L12(P1, P2);
        Line_P3d L23(P2, P3);
        assert(are_incident(L12, L23));
    }

    Point_P3d P4(9,10,11,13);
    Point_P3d P5(11,12,13,17);
    Point_P3d P6(12,13,14,19);

    Plane_P3d L456(P4, P5, P6);

    {
        Line_P3d L45(P4, P5);
        Line_P3d L56(P5, P6);
        assert(are_incident(L45, L56));
    }

    assert(are_incident(P4, L456));
    assert(are_incident(P5, L456));
    assert(are_incident(P6, L456));

    Point_P3d P7(10,11,13,23);
    Point_P3d P8(11,12,13,29);
    Point_P3d P9(12,13,14,31);

    Plane_P3d L789(P7, P8, P9);

    {
        Line_P3d L78(P7, P8);
        Line_P3d L89(P8,P9);
        assert(are_incident(L78, L89));
    }

    assert(are_incident(P7, L789));
    assert(are_incident(P8, L789));
    assert(are_incident(P9, L789));

    Point_P3d i = intersection(L123, L456, L789);

    assert(are_incident(i, L123));
    assert(are_incident(i, L456));
    assert(are_incident(i, L789));

    assert(are_coplanar(P1, P2, P3, i));
    assert(are_coplanar(P4, P5, P6, i));
    assert(are_coplanar(P7, P8, P9, i));
}

int main()
{
    test_equality();
    test_incidence();
}
