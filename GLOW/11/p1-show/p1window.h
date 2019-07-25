/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef P1WINDOW_H
#define P1WINDOW_H

#include <iostream>
using namespace std;

#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using std::vector;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowLabelWidget.h"
#include "glowSliderWidget.h"
using namespace glow;

#include "geometry/P1/point_p1.h"
#include "geometry/P1/transformation_p1.h"

typedef double MyDouble;

typedef Point_P1<MyDouble>                   Point_P1d;
typedef Transformation_P1<MyDouble> Transformation_P1d;

#include "geometry/S1/point_s1.h"
typedef Point_S1<MyDouble>                   Point_S1d;

struct P1_to_S1
{
    Point_S1d operator() (const Point_P1d& p)
    {
        return Point_S1d(p.hx(), p.hw());
    }
};

class P1Window : public GlowWindow, public GlowSliderReceiver
{
    GlowQuickPaletteWindow* controlWindow;
    GlowSliderWidget*         aSlider;
    GlowSliderWidget*         bSlider;

    GlowLabelWidget* determinantIndicator;

    double a,b;
    Point_P1d P;

    GLUquadricObj * qobj;
public:
    P1Window() : GlowWindow("P1 Window", GlowWindow::autoPosition, GlowWindow::autoPosition,
                            500, 500, Glow::rgbBuffer | Glow::doubleBuffer,
                            Glow::keyboardEvents),
                 a(1.0), b(1.0), P(a,b)
    {
        controlWindow = new GlowQuickPaletteWindow("Controls", GlowWindow::autoPosition, GlowWindow::autoPosition,
                                                   GlowQuickPalette::vertical);

        aSlider = controlWindow->AddSlider(-2, 2, a, GlowSliderWidget::defaultOptions,
                                           5, "%.1f", "x:\n%.1f", this);
        bSlider = controlWindow->AddSlider(-2, 2, b, GlowSliderWidget::defaultOptions,
                                           5, "%.1f", "w:\n%.1f", this);

        controlWindow->Pack();

        /* GLUquadricObj * */ qobj = gluNewQuadric();
    }

    virtual ~P1Window()
    {
        gluDeleteQuadric(qobj);
    }

    void drawAxis()
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(3.0);

        glBegin(GL_LINES); {
            glVertex2f(-2.0, 0.0);
            glVertex2f( 2.0, 0.0);

            glVertex2f(0.0, -2.0);
            glVertex2f(0.0,  2.0);

            glVertex2f(-2.0, 1.0);
            glVertex2f( 2.0, 1.0);
        } glEnd();

        gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
        gluQuadricNormals(qobj, GLU_NONE);

        gluPartialDisk(qobj, 0.0, 1.0, 60, 1, 0.0, 360.0);
    }

    void setupProjectionMatrices()
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        gluOrtho2D(-2.5, 2.5,  -2.5, 2.5);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    }

    void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawAxis();

        glEnable(GL_POINT_SMOOTH);
        glPointSize(9.0);

        glBegin(GL_POINTS); {
            glColor3d(0.68,0.0,0.0);  glVertex2f(P.hx(), P.hw());
        } glEnd();

        P1_to_S1 obj;
        Point_S1d Sp = obj(P);

        glBegin(GL_POINTS); {
            glColor3d(1.0,0.0,0.0);
            glVertex2f(Sp.x(), Sp.y());
            glVertex2f(P.hx()/P.hw(),1.0);
        } glEnd();

        glBegin(GL_LINES); {
            glColor3d(1.0,0.0,0.0);
            glVertex2f(Sp.x(), Sp.y());
            glColor3d(1.0,0.0,0.0);
            glVertex2f(P.hx()/P.hw(),1.0);
            glVertex2f(Sp.x(), Sp.y());
            glVertex2f(P.hx()/P.hw(),1.0);
        } glEnd();
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

    void OnMessage(const GlowSliderMessage& message)
    {
        if (message.widget == aSlider) {
            a = message.value;
            P = Point_P1d(a,b);
        }
        if (message.widget == bSlider) {
            b = message.value;
            P = Point_P1d(a,b);
        }

        Refresh();
    }

    void OnReshape(int width, int height)
    {
        glViewport(0, 0, width, height);

        setupProjectionMatrices();
    }
};

#endif // P1WINDOW_H
