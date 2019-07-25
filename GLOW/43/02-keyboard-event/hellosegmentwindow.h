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

const int initViewportWidth = 640;
const int initViewportHeight = 480;

class HelloSegmentWindow : public GlowWindow
{
public:
    HelloSegmentWindow()
        : GlowWindow("HelloSegmentWindow",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer,
                     Glow::keyboardEvents)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, initViewportWidth, 0, initViewportHeight);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    }

protected:
    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES); {
            glVertex2f(160.0f, 120.0f);
            glVertex2f(480.0f, 360.0f);
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
};

#endif // HELLOSEGMENTWINDOW_H
