/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef HELLOSEGMENTWINDOW_H
#define HELLOSEGMENTWINDOW_H

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowCheckBoxWidget.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "misc/clock.h"
const int initViewportWidth = 640;
const int initViewportHeight = 480;

class HelloSegmentWindow
    : public GlowWindow,
      public GlowIdleReceiver,
      public GlowCheckBoxReceiver,
      public GlowPushButtonReceiver
{
    Clock myClock;
    float lastSeconds;

    GLUquadricObj* qobj;

    GlowQuickPaletteWindow* controlWindow;
    GlowCheckBoxWidget*     circleCheckbox;
    GlowPushButtonWidget*   quitButton;

public:
    HelloSegmentWindow()
        : GlowWindow("HelloSegmentWindow",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer | Glow::doubleBuffer,
                     Glow::keyboardEvents),
          lastSeconds(0)
    {
        setupProjectionMatrices();

        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
        gluQuadricNormals(qobj, GLU_NONE);

        controlWindow = new GlowQuickPaletteWindow("Controls",
                                                   GlowWindow::autoPosition, GlowWindow::autoPosition, GlowQuickPalette::vertical);

        GlowQuickPanelWidget* panel = controlWindow->AddPanel(GlowQuickPanelWidget::etchedStyle, "Panel");

        circleCheckbox = panel->AddCheckBox("Circle", GlowCheckBoxWidget::on, this);
        quitButton     = controlWindow->AddPushButton("Quit", this );

        controlWindow->Pack();

        Glow::RegisterIdle(this);
    }

    ~HelloSegmentWindow()
    {
        gluDeleteQuadric(qobj);
    }

protected:
    void setupProjectionMatrices()
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        gluOrtho2D(-GlowSubwindow::Width()/2,  GlowSubwindow::Width()/2,
                   -GlowSubwindow::Height()/2, GlowSubwindow::Height()/2);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }

    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        if(circleCheckbox->GetState() == GlowCheckBoxWidget::on)
            gluPartialDisk(qobj, 200.0, 201.0, 60, 1, 0.0, 360.0);

        glRotatef(myClock.getSecondsSinceStart() * 100.0,  0,0,1);
        glBegin(GL_LINES); {
            glVertex2f(-160.0f, -120.0f);
            glVertex2f( 160.0f,  120.0f);
        } glEnd();
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey:
            Close();
            controlWindow->Close();
        default:
            ;
        }
    }

    virtual void OnMessage(const GlowIdleMessage& /*message*/)
    {
        float seconds = myClock.getSecondsSinceStart();
        if(seconds - lastSeconds > 0.001) {
            Refresh();
            lastSeconds = seconds;
        }
    }

    virtual void OnReshape(int width, int height)
    {
        GlowSubwindow::OnReshape(width, height);

        setupProjectionMatrices();
    }

    void OnMessage(const GlowCheckBoxMessage& /*message*/)
    {
        Refresh();
    }

    void OnMessage(const GlowPushButtonMessage& message)
    {
        if(message.widget == quitButton)
            exit(0);
    }
};

#endif // HELLOSEGMENTWINDOW_H
