/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/T3/geometry_t3.h"

#include "geometry/T3/point_t3.h"
#include "geometry/T3/vector_t3.h"
#include "geometry/T3/segment_t3.h"
#include "geometry/T3/intersection_t3.h"
#include "geometry/T3/predicates_t3.h"
#include "geometry/free/clip_2.h"

#include "geometry/T3/transformation_t3.h"
#include "unit_cube_intersections_t3.h"

#include "misc/random_t3.h"

#include "misc/epsilon_double.h"

#include <cassert>
#include <iostream>
using namespace std;

typedef Geometry_T3<double> Geometry_T3d;

typedef Epsilon_double MyDouble;

typedef Point_T3<MyDouble>     Point_T3d;
typedef Vector_T3<MyDouble>   Vector_T3d;
typedef Segment_T3<MyDouble> Segment_T3d;
typedef Plane_T3<MyDouble>     Plane_T3d;

typedef Transformation_T3<MyDouble> Transformation_T3d;

void test_incidence()
{
    Point_T3d P1(3,4,5,6);
    Point_T3d P2(6,7,8,9);
    Point_T3d T3(7,8,9,11);

    Plane_T3d L123(P1, P2, T3);

    assert(L123.isIncident(P1));
    assert(L123.isIncident(P2));
    assert(L123.isIncident(T3));

    Point_T3d P4(9,10,11,13);
    Point_T3d P5(11,12,13,17);
    Point_T3d P6(12,13,14,19);

    Plane_T3d L456(P4, P5, P6);

    assert(L456.isIncident(P4));
    assert(L456.isIncident(P5));
    assert(L456.isIncident(P6));

    Point_T3d P7(10,11,13,23);
    Point_T3d P8(11,12,13,29);
    Point_T3d P9(12,13,14,31);

    Plane_T3d L789(P7, P8, P9);

    assert(L789.isIncident(P7));
    assert(L789.isIncident(P8));
    assert(L789.isIncident(P9));

    Point_T3d i = intersection(L123, L456, L789);

    assert(L123.isIncident(i));
    assert(L456.isIncident(i));
    assert(L789.isIncident(i));

    assert(are_coplanar(P1, P2, T3, i));
    assert(are_coplanar(P4, P5, P6, i));
    assert(are_coplanar(P7, P8, P9, i));
}

void test_addition()
{
    {
        Point_T3d P1(2,3,4,5);
        Point_T3d P2(1,-2,3,-7);
        Vector_T3d v = P2 - P1;
        Point_T3d P3 = P1 + v;
        assert( P2 == P3 );
    }
    {
        Point_T3d P1(2,3,4,5);
        Point_T3d P2(-1,2,-3,7);
        Vector_T3d v = P2 - P1;
        Point_T3d P3 = P1 + v;
        assert( P2 == P3 );
    }
}

void test_unit_cube_clip_segment()
{

    Segment_T3d seg(Point_T3d(1,0,0,10),
                    Point_T3d(2,0,0,10));
    Segment_T3d saveseg = seg;

    unit_cube_clip(seg);
    assert(seg == saveseg);
}

void test_clip_2()
{
    typedef Geometry_T3d::Point      Point_T3d;
    typedef Geometry_T3d::Hyperplane Plane_T3d;
    typedef Geometry_T3d::Polygon  Polygon_T3d;

    Point_T3d pnts[] = { Point_T3d(-2,-2, 0),
                         Point_T3d(-2, 2, 0),
                         Point_T3d( 2, 2, 0),
                         Point_T3d( 2,-2, 0) };
    Polygon_T3d poly(pnts+0,pnts+sizeof(pnts)/sizeof(Point_T3d));
    const Point_T3d A(0,0,0);
    const Point_T3d B(0,0,1);
    const Point_T3d C(0,1,0);
    Plane_T3d plane = Plane_T3d (A,B,C);
    bool b = positive_half_space_clip<Geometry_T3d>(plane, poly);
    assert(b);

    const Point_T3d rslt[] = { Point_T3d(0, -2, 0, 1),
                               Point_T3d(-2, -2, 0, 1),
                               Point_T3d(-2, 2, 0, 1),
                               Point_T3d(-0, 2, 0, 1) };
    assert( std::equal(poly.begin(), poly.end(), rslt+0) );
}

int main()
{
    test_incidence();
    test_addition();
    test_unit_cube_clip_segment();
    test_clip_2();
}
