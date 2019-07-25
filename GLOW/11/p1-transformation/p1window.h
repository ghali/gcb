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
    GlowSliderWidget*         cSlider;
    GlowSliderWidget*         dSlider;

    GlowLabelWidget* determinantIndicator;

    double a,b,c,d;
    Transformation_P1d PT;
    vector<Point_P1d > P;

    GLUquadricObj * qobj;
public:
    P1Window() : GlowWindow("P1 Window", GlowWindow::autoPosition, GlowWindow::autoPosition,
                            500, 500, Glow::rgbBuffer | Glow::doubleBuffer,
                            Glow::keyboardEvents),
                 PT(1.0, 0.0, 0.0, 1.0),
                 P(4)
    {
        controlWindow = new GlowQuickPaletteWindow("Controls", GlowWindow::autoPosition, GlowWindow::autoPosition,
                                                   GlowQuickPalette::vertical);
        GlowQuickPanelWidget* panel_det = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "");
        GlowQuickPanelWidget* panel_sliders = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "", GlowQuickPalette::horizontal);
        GlowQuickPanelWidget* panel1 = panel_sliders->AddPanel(GlowQuickPanelWidget::etchedStyle, "", GlowQuickPalette::vertical);
        GlowQuickPanelWidget* panel2 = panel_sliders->AddPanel(GlowQuickPanelWidget::etchedStyle, "", GlowQuickPalette::vertical);

        determinantIndicator = panel_det->AddLabel("determinant= +4.00000");

        aSlider = panel1->AddSlider(-2, 2, 2, GlowSliderWidget::defaultOptions,
                                    5, "%.1f", "a:\n%.1f", this);
        cSlider = panel1->AddSlider(-2, 2, 0, GlowSliderWidget::defaultOptions,
                                    5, "%.1f", "c:\n%.1f", this);

        bSlider = panel2->AddSlider(-2, 2, 0, GlowSliderWidget::defaultOptions,
                                    5, "%.1f", "b:\n%.1f", this);
        dSlider = panel2->AddSlider(-2, 2, 2, GlowSliderWidget::defaultOptions,
                                    5, "%.1f", "d:\n%.1f", this);

        controlWindow->Pack();

        a = d = 2.0;
        b = c = 0.0;

        P[0] = Point_P1d( 1,0);
        P[1] = Point_P1d( 1,1);
        P[2] = Point_P1d( 0,1);
        P[3] = Point_P1d(-1,1);

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

        PT = Transformation_P1d(a,b,c,d);
    }

    void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawAxis();

        glEnable(GL_POINT_SMOOTH);
        glPointSize(9.0);

        glBegin(GL_POINTS); {
            glColor3d(0.68,0.0,0.0);  glVertex2f(P[0].hx(), P[0].hw());
//            glColor3d(0.0,0.68,0.0);  glVertex2f(P[1].hx(), P[1].hw());
            glColor3d(0.0,0.0,0.68);  glVertex2f(P[2].hx(), P[2].hw());
//            glColor3d(0.68,0.68,0.0); glVertex2f(P[3].hx(), P[3].hw());
        } glEnd();

        vector<Point_P1d > Pt(P.size()); // transformed projective points
        std::transform(P.begin(), P.end(), Pt.begin(), PT);

        vector<Point_S1d > Sp(P.size()); // spherical points
        P1_to_S1 obj;
        std::transform(Pt.begin(), Pt.end(), Sp.begin(), obj);

        glBegin(GL_POINTS); {
            glColor3d(1.0,0.0,0.0);  glVertex2f(Pt[0].hx(), Pt[0].hw()); glVertex2f(Sp[0].x(), Sp[0].y()); glVertex2f(Pt[0].hx()/Pt[0].hw(),1.0);
//            glColor3d(0.0,1.0,0.0);  glVertex2f(Pt[1].hx(), Pt[1].hw()); glVertex2f(Sp[1].x(), Sp[1].y()); glVertex2f(Pt[1].hx()/Pt[1].hw(),1.0);
            glColor3d(0.0,0.0,1.0);  glVertex2f(Pt[2].hx(), Pt[2].hw()); glVertex2f(Sp[2].x(), Sp[2].y()); glVertex2f(Pt[2].hx()/Pt[2].hw(),1.0);
//            glColor3d(1.0,1.0,0.0);  glVertex2f(Pt[3].hx(), Pt[3].hw()); glVertex2f(Sp[3].x(), Sp[3].y()); glVertex2f(Pt[3].hx()/Pt[3].hw(),1.0);
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
            PT = Transformation_P1d(a,b,c,d);
        }
        if (message.widget == bSlider) {
            b = message.value;
            PT = Transformation_P1d(a,b,c,d);
        }
        if (message.widget == cSlider) {
            c = message.value;
            PT = Transformation_P1d(a,b,c,d);
        }
        if (message.widget == dSlider) {
            d = message.value;
            PT = Transformation_P1d(a,b,c,d);
        }

        std::ostringstream os;
        os << std::setprecision(4);
        os << "determinant= " << a * d - b * c;
        determinantIndicator->SetText(os.str().c_str());

        Refresh();
    }


    void OnReshape(int width, int height)
    {
        glViewport(0, 0, width, height);

        setupProjectionMatrices();
    }
};

#endif // P1WINDOW_H
