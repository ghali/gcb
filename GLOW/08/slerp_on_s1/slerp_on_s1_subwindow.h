/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SLERP_ON_S1_SUBWINDOW_H
#define SLERP_ON_S1_SUBWINDOW_H

#include <iostream>
using namespace std;

#include "glow.h"
using namespace glow;

typedef double MyDouble;
#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"
#include "geometry/S1/interpolation_s1.h"
typedef Point_S1<MyDouble> Point_S1d;
typedef Segment_S1<MyDouble> Segment_S1d;

#include "opengl/gldraw_s1.h"
typedef GLdraw_S1<MyDouble> GLdraw_S1d;


class Slerp_on_s1_subwindow
    : public GlowSubwindow
{
    double angle0, angle1, i;
    Segment_S1d mySegment;
    Point_S1d Pi;

    GLdraw_S1d myGLdraw;    
public:
    Slerp_on_s1_subwindow(GlowWindow* parent)
        : GlowSubwindow(parent, 0, 0, 500, 500,
                        Glow::rgbBuffer | Glow::doubleBuffer,
                        Glow::keyboardEvents),
          angle0(0.0), angle1(M_PI/2.0), i(0.0),
          mySegment(Point_S1d(cos(angle0), sin(angle0)),
                    Point_S1d(cos(angle1), sin(angle1))),
          myGLdraw()
    {
    }

    void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        myGLdraw.drawAxis(2.0);

        glEnable(GL_POINT_SMOOTH);
        glPointSize(9.0);

        myGLdraw.draw(mySegment.source(), glow::GlowColor::red);
        myGLdraw.draw(mySegment.target(), glow::GlowColor::blue);
        myGLdraw.draw(Pi, glow::GlowColor::green);
    }

    void setPoints(double _angle0, double _angle1, double _i)
    {
        angle0 = _angle0;
        angle1 = _angle1;
        i = _i;
        Point_S1d P0(cos(angle0), sin(angle0));
        Point_S1d P1(cos(angle1), sin(angle1));
        mySegment = Segment_S1d(P0, P1);
        Pi = interpolate(P0, P1, i);
        //Pi = combination_method2(P0, P1, i);

        Refresh();
    }

    void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                    Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey: exit(0);
        default:
            ;
        }
    }

    void OnReshape(int width, int height)
    {
        glViewport(0, 0, width, height);

        myGLdraw.setupProjectionMatrices(2.5);
    }
};

#endif // SLERP_ON_S1_SUBWINDOW_H
