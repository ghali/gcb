/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef AFFINEWINDOW_H
#define AFFINEWINDOW_H

#include <vector>
using std::vector;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowSliderWidget.h"
using namespace glow;

#include "geometry/E2/point_e2.h"
#include "geometry/E2/transformation_e2.h"

Rotation ROTATION;

class AffineWindow : public GlowWindow, public GlowSliderReceiver
{
    GlowQuickPaletteWindow* controlWindow;
    GlowSliderWidget*         angleSlider;
    Transformation_E2<double> AT;
    vector<Point_E2<double> > P;
public:
    AffineWindow() : GlowWindow("Affine Window", GlowWindow::autoPosition, GlowWindow::autoPosition,
                                500, 500, Glow::rgbBuffer | Glow::doubleBuffer,
                                Glow::keyboardEvents),
                     P(4)
    {
        controlWindow = new GlowQuickPaletteWindow("Controls", GlowWindow::autoPosition, GlowWindow::autoPosition,
                                                   GlowQuickPalette::vertical);
        angleSlider = controlWindow->AddSlider(0, 90, 90, GlowSliderWidget::defaultOptions,
                                               5, "%.1f", "Value:\n%.1f", this);
        controlWindow->Pack();

        P[0] = Point_E2<double>(0,0);
        P[1] = Point_E2<double>(1,0);
        P[2] = Point_E2<double>(1,1);
        P[3] = Point_E2<double>(0,1);
    }

    void setupProjectionMatrices()
    {
        ::glMatrixMode(GL_PROJECTION);
        ::glPushMatrix();
        ::glLoadIdentity();

//        ::gluOrtho2D(-GlowSubwindow::Width()/2,  GlowSubwindow::Width()/2,
//                     -GlowSubwindow::Height()/2, GlowSubwindow::Height()/2);

        ::gluOrtho2D(-.5, 2.5,  -.5, 2.5);

        ::glMatrixMode(GL_MODELVIEW);
        ::glLoadIdentity();

        ::glEnable(GL_LINE_SMOOTH);
        ::glEnable(GL_BLEND);
        ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }

    void OnEndPaint()
    {
        ::glClear(GL_COLOR_BUFFER_BIT);
        ::glLoadIdentity();

        ::glBegin(GL_LINE_LOOP); {
            for(int i=0; i<4; ++i)
                ::glVertex2f(P[i].x(), P[i].y());
        } ::glEnd();

        ::glBegin(GL_LINE_LOOP); {
            for(int i=0; i<4; ++i) {
                Point_E2<double> Po = P[i];
                Point_E2<double> Pt = AT.transform(Po);
                ::glVertex2f(Pt.x(), Pt.y());
            }
        } ::glEnd();
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
        if (message.widget == angleSlider) {
            double angle = message.value;
            // AT = Transformation_E2<double>(ROTATION, angle * M_PI/180.0);
            AT = Transformation_E2<double>(1.0, cos(angle * M_PI/180.0), 0.0,
                                           0.0, sin(angle * M_PI/180.0), 0.0);
        }
        Refresh();
    }

    void OnReshape(int width, int height)
    {
        ::glViewport(0, 0, width, height);

        setupProjectionMatrices();
    }
};

#endif // AFFINEWINDOW_H
