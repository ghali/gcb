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
using namespace glow;

#include "misc/clock.h"
const int initViewportWidth = 640;
const int initViewportHeight = 480;

class HelloSegmentWindow : public GlowWindow, public GlowIdleReceiver
{
    Clock myClock;
    float lastSeconds;
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

        Glow::RegisterIdle(this);
    }

protected:
//----------------setupProjectionMatrices_Begin----------------
    void setupProjectionMatrices()
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        int W = GlowSubwindow::Width()/2;
        int H = GlowSubwindow::Height()/2;
        gluOrtho2D(-W, W, -H, H);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }
//----------------setupProjectionMatrices_End----------------

    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
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
        default:
            ;
        }
    }

    virtual void OnMessage(const GlowIdleMessage& /*message*/)
    {
        float seconds = myClock.getSecondsSinceStart();
        if(seconds - lastSeconds > 0.01) {
            Refresh();
            lastSeconds = seconds;
        }
    }

//----------------OnReshape_Begin----------------
    virtual void OnReshape(int width, int height)
    {
        GlowSubwindow::OnReshape(width, height);

        setupProjectionMatrices();
    }
//----------------OnReshape_End----------------
};

#endif // HELLOSEGMENTWINDOW_H
