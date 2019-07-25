/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <cassert>
#include <iostream>
using namespace std;

typedef float Grayscale;

#include "postscript/postscript.h"

#include "visibility_E2/view_e2.h"
typedef double                       MyDouble;
typedef Point_E2<MyDouble>          Point_E2d;
typedef Triangle_E2<MyDouble>    Triangle_E2d;
typedef Bbox_E2<MyDouble>            Bbox_E2d;
typedef View_E2<MyDouble, Grayscale> View_E2d;

typedef Point_S1<MyDouble>          Point_S1d;

typedef Postscript<MyDouble>     Postscript_d;

typedef View_E2d::Scene                 Scene;
typedef View_E2d::Interior_list Interior_list;

//----------------render_Begin----------------
void render(const Scene & triangles,
            const string & filename,
            const Point_E2d & observer,
            const View_E2d & view,
            const Bbox_E2d & bbox)
{
    Postscript_d PS(filename, bbox);

    Interior_list view_segments = view.get_view_segments();

    Scene::const_iterator triangle_ci = triangles.begin();
    PS.set_line_width(0.8);
    while( triangle_ci != triangles.end() ) {
        PS.set_gray_stroke( triangle_ci->second );
        PS.draw( triangle_ci->first );
        triangle_ci++;        
    }

    PS.set_gray_stroke( 0.0 );
    PS.draw(observer);

    Interior_list::const_iterator ci = view_segments.begin();
    while( ci != view_segments.end() ) {
        PS.set_gray_stroke( ci->second );
        PS.draw( ci->first.get_Segment_S1(), observer, 1.0 );
        ci++;
    }

    PS.close();
}
//----------------render_End----------------

void e2_to_s1_1()
{
    const Point_E2d A(4, 2), B( 0, 2), C( 2, 3);
    const Point_E2d D(1, 4), E(-4, 1), F(-2, 5);
    const Point_E2d G(3,4), H(2,5), I(4,5);
    const Point_E2d J(1,-1), K(4,1), L(3,-2);
    const Point_E2d M(2,-4), N(1,-5), O(-2,-4);
    const Point_E2d P(-3,-1), Q(-1,-3), R(-5,-2);
    const Triangle_E2d T1(A,B,C), T2(D,E,F), T3(G,H,I);
    const Triangle_E2d T4(J,K,L), T5(M,N,O), T6(P,Q,R);
    const Grayscale black(0.0), gray(0.6);

    Scene triangles;
    triangles.push_back( std::make_pair(T1, black) );
    triangles.push_back( std::make_pair(T2, gray) );
    triangles.push_back( std::make_pair(T3, black) );
    triangles.push_back( std::make_pair(T4, black) );
    triangles.push_back( std::make_pair(T5, gray) );
    triangles.push_back( std::make_pair(T6, black) );

//----------------call_render_Begin----------------
    const Point_E2d observer(0, 0);
    const Bbox_E2d bbox( Point_E2d(-6,-6), Point_E2d(5,6) );
    const View_E2d view( triangles, bbox, observer );

    render(triangles, "psout/e2_to_s1_scene1.eps", observer, view, bbox);
//----------------call_render_End----------------
}

int main()
{
    e2_to_s1_1();
}
