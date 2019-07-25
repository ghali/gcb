/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "misc/color_3.h"
typedef Color_3<unsigned char> Color;

#include "view_e2.h"

#include <cassert>
#include <iostream>
using namespace std;

typedef double                       MyDouble;
typedef Point_E2<MyDouble>          Point_E2d;
typedef Triangle_E2<MyDouble>    Triangle_E2d;
typedef Bbox_E2<MyDouble>            Bbox_E2d;
typedef View_E2<MyDouble, Color>     View_E2d;

typedef Point_S1<MyDouble>          Point_S1d;

typedef View_E2d::Scene                 Scene;
typedef View_E2d::Interior_list Interior_list;

void test1()
{
    const Point_E2d A(4, 2), B( 0, 2), C( 2, 3);
    const Point_E2d D(1, 4), E(-5, 4), F(-2, 5);
    const Triangle_E2d T1( A, B, C ), T2( D, E, F );
    const Color red(1,0,0), green(0,1,0);

    Scene triangles;
    triangles.push_back( std::make_pair(T1, red) );
    triangles.push_back( std::make_pair(T2, green) );

    const Point_E2d observer(0, 0);
    const Bbox_E2d bbox( Point_E2d(-6,-1), Point_E2d(5,6) );
#if 0 
    const View_E2d view( triangles, bbox, observer );

    Interior_list view_segments = view.get_view_segments();

    Interior_list::const_iterator ci = view_segments.begin();
    assert( ci->first.source() == Point_S1d(observer, A) );
    assert( ci->first.target() == Point_S1d(observer, B) );
    assert( ci->second == red );
    ci++;

    assert( ci->first.source() == Point_S1d(observer, B) );
    assert( ci->first.target() == Point_S1d(observer, E) );
    assert( ci->second == green );
    ci++;

    assert( ci == view_segments.end() );

    const Point_S1d v1(1,1), v2(-1,1);
    assert( view.classify(v1) == std::make_pair(INSIDE_SET, red) );
    assert( view.classify(v2) == std::make_pair(INSIDE_SET, green) );
#endif
}

int main()
{
    test1();
}
