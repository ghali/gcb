/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

// We must include the intersections and predicates of whichever
// geometry we intend to use generically.
#include "geometry/E2/intersection_E2.h"

// #include "geometry/free/splitting/Splitter.h"
#include "splitting_2.h"

// ... which saves us from having a wrapper for each geometry.
// #include "splitting_E2.h"

#include <cassert>
#include "geometry_types.h"

void test_splitting_E2()
{
    const Point_E2d P[] = { /*0: LL*/ Point_E2d(-6,-1),
                            /*1: UL*/ Point_E2d(-6, 6),
                            /*2: UR*/ Point_E2d( 5, 6),
                            /*3: LR*/ Point_E2d( 5,-1) };
    Point_E2d LL = P[0];
    Point_E2d UL = P[1];
    Point_E2d UR = P[2];
    Point_E2d LR = P[3];

    const Hyperplane_E2d Ha[] = { Hyperplane_E2d(P[0], P[1]),
                                  Hyperplane_E2d(P[1], P[2]), 
                                  Hyperplane_E2d(P[2], P[3]), 
                                  Hyperplane_E2d(P[3], P[0]) };

    const std::vector<Hyperplane_E2d> H(Ha, Ha+4);
    const std::vector<bool> BL(4, false);

    const Convex_polytope_E2d polygon( H, BL );

    const Point_E2d A(4, 2), B( 0, 2);
    const Hyperplane_E2d AB(A, B);

    Convex_polytope_E2d positive_polygon, negative_polygon;

    // typedef Splitter<MyDouble, Geometry_E2<MyDouble> > Splitter_E2d;
    // Splitter_E2d::split( polygon, AB,
    //                      positive_polygon, negative_polygon );

    split<Geometry_E2d>( polygon, AB,
                         positive_polygon, negative_polygon );


    // split( ( a_polygon,
    //                        splitting_line, // Segment_E2<NT>
    //                        positive_side,
    //                        negative_side );

    std::vector<Hyperplane_E2d> pos_lines = positive_polygon.get_lines();
    std::vector<Hyperplane_E2d>::const_iterator p = pos_lines.begin();

    assert( *p++ == Hyperplane_E2d(LL, UL) );
    assert( *p++ == Hyperplane_E2d(B, A) );
    assert( *p++ == Hyperplane_E2d(UR, LR) );
    assert( *p++ == Hyperplane_E2d(LR, LL) );
    assert( p == pos_lines.end());

    std::vector<Hyperplane_E2d> neg_lines = negative_polygon.get_lines();
    std::vector<Hyperplane_E2d>::const_iterator n = neg_lines.begin();

    assert( *n++ == Hyperplane_E2d(LL, UL) );
    assert( *n++ == Hyperplane_E2d(UL, UR) );
    assert( *n++ == Hyperplane_E2d(UR, LR) );
    assert( *n++ == AB );
    assert( n == neg_lines.end());
}

int main()
{
    test_splitting_E2();
}
