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
#include "geometry/E1/transformation_e1.h"
#include "geometry/E1/predicates_e1.h"
#include "geometry/E1/interpolation_e1.h"

#include <cassert>

typedef Epsilon_double MyDouble;

typedef Point_E1<MyDouble>       Point_E1d;
typedef Vector_E1<MyDouble>     Vector_E1d;
typedef Segment_E1<MyDouble>   Segment_E1d;
typedef Transformation_E1<MyDouble> Transformation_E1d;

void test_transformation()
{
    Point_E1d P(5);

    Transformation_E1d T(TRANSLATION, Vector_E1d(2));
    Point_E1d Q = T(P);

    assert( (Q.x() == P.x() + 2) );
}

void test_composition_of_transformations()
{
    Point_E1d P(3);

    Transformation_E1d T1(2,3);
    Transformation_E1d T2(8,9);

    Transformation_E1d T21 = T2 * T1; // T1 is applied first

    assert(T2(T1(P)) == T21(P));
}

void test_transformation_and_equality_of_segments()
{
    Point_E1d A(2);
    Point_E1d B(4);
    Point_E1d C(6);
    Point_E1d D(8);
    Segment_E1d AC(A, C);
    Segment_E1d BD(B, D);

    Transformation_E1d T(TRANSLATION, Vector_E1d(2));
    Segment_E1d AC_t = T(AC);
    assert( AC_t == BD );
}

void test_scale()
{
    Point_E1d P1(5);
    Vector_E1d V1(11);

    Point_E1d P2 = P1 + V1;

    Transformation_E1d T(SCALE, Vector_E1d(33.0));

    Point_E1d P1t = T(P1);
    Vector_E1d V1t = T(V1);

    Point_E1d P2t = T(P2);

    assert( P2t == P1t + V1t );
}

void test_point_point_classification()
{
    Point_E1d P1(3);
    Point_E1d P2(5);
    assert( oriented_side(P1, P2) == ON_POSITIVE_SIDE );
}        

void test_point_segment_classification()
{
    Segment_E1d S( Point_E1d(-5.0), Point_E1d(4.0) );
    Point_E1d P(2);
    assert( classify(S, P) == INSIDE_SET );
}

void test_inverse()
{
    Point_E1d P0(2);
    Transformation_E1d T(-4,-7);
    Transformation_E1d inverseT = T.inverse();

    Point_E1d P1 = T(P0);
    Point_E1d P2 = inverseT(P1);
    assert(P0 == P2);
}

void test_segment_interpolation()
{
    Point_E1d A(3), B(4);
    Point_E1d C(7), D(9);
    Segment_E1d from(A,B);
    Segment_E1d to(C,D);
    Transformation_E1d T = interpolate(from, to);
    assert(T(A) == C);
    assert(T(B) == D);
}

int main()
{
    test_transformation();
    test_composition_of_transformations();
    test_transformation_and_equality_of_segments();
    test_scale();
    test_point_point_classification();
    test_point_segment_classification();
    test_inverse();
    test_segment_interpolation();
}
