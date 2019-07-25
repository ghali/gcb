/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/E3/bbox_e3.h"

#include "misc/epsilon_double.h"
#include "geometry/E3/point_e3.h"
#include "geometry/E3/plane_e3.h"
#include "geometry/E3/vector_e3.h"
#include "geometry/E3/direction_e3.h"
#include "geometry/E3/line_e3.h"
#include "geometry/E3/transformation_e3.h"
#include "geometry/E3/triangle_e3.h"
#include "geometry/E3/polygon_e3.h"

#include "geometry/E3/predicates_e3.h"
#include "geometry/E3/polygon_normal_e3.h"
#include "geometry/E3/interpolation_e3.h"
#include "geometry/E3/intersection_e3.h"

#include <cassert>
#include <iostream>

typedef Epsilon_double MyDouble;

typedef Point_E3<MyDouble>   Point_E3d;
typedef Plane_E3<MyDouble>   Plane_E3d;
typedef Vector_E3<MyDouble> Vector_E3d;
typedef Direction_E3<MyDouble> Direction_E3d;
typedef Line_E3<MyDouble> Line_E3d;
typedef Segment_E3<MyDouble> Segment_E3d;
typedef Transformation_E3<MyDouble> Transformation_E3d;
typedef Triangle_E3<MyDouble>   Triangle_E3d;
typedef Polygon_E3<MyDouble>   Polygon_E3d;

typedef Bbox_E3<MyDouble>   Bbox_E3d;

void test_op()
{
    Point_E3d  P1(3.0,4.0,5.0);
    Point_E3d  P2(4.0,7.0,9.0);
    Vector_E3d V1(8.0,4.0,2.0);

    Point_E3d A1 = P1;
    A1 += V1;
    assert( Point_E3d(11.0,8.0,7.0) == A1 );
    A1 -= V1;
    assert( P1 == A1 );

    Vector_E3d V2(P1, P2);
    assert( Vector_E3d(1.0, 3.0, 4.0) == V2 );
}

void test_Transformation_E3()
{
    Point_E3d P1(5,7,9);
    Vector_E3d V1(11,13,17);

    Point_E3d P2 = P1 + V1;

    Transformation_E3d T(ORTHOGONAL, Point_E3d(4,5,6), Point_E3d(7,8,9));

    Point_E3d P1t = T(P1);
    Vector_E3d V1t = T(V1);

    Point_E3d P2t = T(P2);

    assert( P2t == P1t + V1t );
}

void test_Transformation_E3_operator_mult()
{
    Point_E3d P(3,4,5);

    Transformation_E3d T1(2,3,4,5, 6,7,8,9, 10,11,12,13);
    Transformation_E3d T2(14,15,16,17, 2,3,4,5, 6,7,8,9);

    Transformation_E3d T21 = T2 * T1; // T1 is applied first
        
    assert(T2(T1(P)) == T21(P));
}

void test_rotation()
{
    Point_E3d P1(1,2,3);

    Transformation_E3d T1(ROTATION,
                          Direction_E3d(3,4,5),
                          1.0);
    Point_E3d P2 = T1(P1);

    Transformation_E3d T2(ROTATION,
                          Direction_E3d(-3,-4,-5),
                          1.0);
    Point_E3d P3 = T2(P2);

    assert(P3 == P1);
}

void test_inverse()
{
    Transformation_E3d T1(2,4,5,3, 7,8,6,9, 11,12,10,13);

    Transformation_E3d T1inv = T1.inverse();
    Transformation_E3d T3 = T1 * T1inv;

    assert(T3.get_m00() == 1
           && T3.get_m11() == 1
           && T3.get_m22() == 1);
    assert(T3.get_m01() == 0
           && T3.get_m02() == 0
           && T3.get_m12() == 0
           && T3.get_m10() == 0
           && T3.get_m20() == 0
           && T3.get_m21() == 0);
    assert(T3.get_m03() == 0
           && T3.get_m13() == 0
           && T3.get_m23() == 0);

    Point_E3d P(2,3,5);
    assert(T1(T1inv(P)) == P);
    assert(T1inv(T1(P)) == P);
}

void test_Bbox_E3_operator_incr()
{
    Point_E3d P1(-5,-4,-3);
    Point_E3d P2( 7, 6, 5);

    Bbox_E3d box(P1);
    box += P2;

    assert( box == Bbox_E3d(P1, P2) );

    assert( box.center() == Point_E3d(1,1,1) );
}

void test_polygon_Bbox()
{
    Point_E3d P1(-5,-4,-3);
    Point_E3d P2( 5, 4, 3);

    Point_E3d P[] = { P1, P2, Point_E3d(-2, 2, 2) };
    Polygon_E3d poly(P, P+3);
    Bbox_E3d box = poly.get_Bbox();
    assert( box == Bbox_E3d(P1, P2) );
}

void test_polygon_quad_subdivide()
{
    Point_E3d P0(-20,-0.6,-20);
    Point_E3d P1( 20,-0.6,-20);
    Point_E3d P2( 20,-0.6, 20);
    Point_E3d P3(-20,-0.6, 20);
    const Point_E3d points[] = { P0, P1, P2, P3 };
    {
        Polygon_E3d P(points, points+4);

        Array2<Point_E3d> A = quad_subdivide(P, 4, 4);
        assert(A(0,0) == P0);
        assert(A(4,0) == P1);
        assert(A(4,4) == P2);
        assert(A(0,4) == P3);

        assert(A(2,1) == Point_E3d(  0,-0.6,-10));
        assert(A(2,2) == Point_E3d(  0,-0.6,  0));
        assert(A(1,2) == Point_E3d(-10,-0.6,  0));
    }
    {
        Polygon_E3d P(points, points+4);

        Array2<Point_E3d> A = quad_subdivide(P, 4, 2);
        assert(A(0,0) == P0);
        assert(A(4,0) == P1);
        assert(A(4,2) == P2);
        assert(A(0,2) == P3);


        assert(A(2,1) == Point_E3d(  0,-0.6,  0));
        assert(A(2,2) == Point_E3d(  0,-0.6, 20));
        assert(A(1,2) == Point_E3d(-10,-0.6, 20));
    }
}

void test_polygon_normal()
{
    const Point_E3d A[] = { Point_E3d( 15,-0.6,-15),
                            Point_E3d(-15,-0.6,-15),
                            Point_E3d(-15,-0.6, 15),
                            Point_E3d( 15,-0.6, 15) };
    Polygon_E3d P(A, A+4);
    Vector_E3d v = polygon_normal_vector<MyDouble>(P);
    assert( are_linearly_dependent( Vector_E3d(0,1,0), v ) );
}

void test_dominant()
{
    const Point_E3d A(5,5,5);
    const Point_E3d B(8,7,6);
    const Point_E3d C(7,8,6);
    const Point_E3d D(6,7,8);

    const Segment_E3d AB(A,B);
    const Segment_E3d AC(A,C);
    const Segment_E3d AD(A,D);

    assert( dominant(AB) == E3_POSX );
    assert( dominant(AC) == E3_POSY );
    assert( dominant(AD) == E3_POSZ );

    const Vector_E3d v1(1,1,0.01);
    assert( least_dominant(v1) == E3_POSZ );
}

void runme()
{
//    Direction_E3d d(1,0,1);
//
//    std::cout << "d: " << d << std::endl;
//
//    Transformation_E3d T1(ROTATION,
//                          Direction_E3d(0.0,1.0,0.0),
//                          M_PI/2.0);
//    Direction_E3d dh = T1(d);
//
//    std::cout << "dh: " << dh << std::endl;
//
////                          Direction_E3d(0.0,0.0,1.0),
//
//    Transformation_E3d T2(ROTATION,
//                          dh,
//                          -0.7);
//    Direction_E3d df = T2(d);
//
//    std::cout << "df: " << df << std::endl;

    Direction_E3d d(0,0,1);

    std::cout << "d: " << d << std::endl;

    Transformation_E3d T1(ROTATION,
                          Direction_E3d(0.0,1.0,0.0),
                          M_PI/2.0);
    Direction_E3d dh = T1(d);

    std::cout << "dh: " << dh << std::endl;

//                          Direction_E3d(0.0,0.0,1.0),

    Transformation_E3d T2(ROTATION,
                          dh,
                          -0.7);
    Direction_E3d df = T2(d);

    std::cout << "df: " << df << std::endl;


}

const Point_E3d A(4,4,0);        // E--C--B
const Point_E3d B(6,6,0);        //    | /|
const Point_E3d C(4,6,0);        //    |/ |
const Point_E3d D(6,4,0);        //    A--D
const Point_E3d E(2,6,0);

const Point_E3d C1(4,6,2);

const Point_E3d P1(4,4,2);
const Point_E3d P2(4,4,-2);

const Plane_E3d ABC(A,B,C);

const Plane_E3d ADB(A, D, B);

void
test_oriented_side_plane_point()
{
    assert( oriented_side(ADB, A) == ON_ORIENTED_BOUNDARY );
    assert( oriented_side(ADB, P1) == ON_POSITIVE_SIDE );
    assert( oriented_side(ADB, P2) == ON_NEGATIVE_SIDE );
}

void
test_intersection_plane_line()
{
    Point_E3d P = intersection(ADB, Line_E3d(P2,P1));
    assert( P == A );
}

void
test_intersection_plane_triangle()
{
    Point_E3d P;
    Segment_E3d S;
    //{
    //Triangle_E3d Tadb(A, D, B);
    //Intersection_type_E3 it1 = intersection(ADB, Tadb, P, S);
    //assert( it1 == IS_TRIANGLE_E3 );
    //}

    {
        Triangle_E3d Tabc1(A, B, C1);    
        Plane_E3d plane(Vector_E3d(0,0,1), -1);
        Intersection_type_E3 it2 = intersection(plane, Tabc1, P, S);
        assert( it2 == IS_SEGMENT_E3 );
        assert( S == Segment_E3d(Point_E3d(4,5,1),
                                 Point_E3d(5,6,1)) );
    }
}

int main()
{
//    test_op();
//    test_Transformation_E3();
//    test_Transformation_E3_operator_mult();
//    test_rotation();
//    test_inverse();
//    test_Bbox_E3_operator_incr();
//    test_polygon_Bbox();
//    test_polygon_quad_subdivide();
//    test_polygon_normal();
//
//    test_dominant();
//
//    runme();
//
//    test_oriented_side_plane_point();
    test_intersection_plane_triangle();
}
