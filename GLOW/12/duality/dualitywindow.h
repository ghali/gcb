/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DUALITYWINDOW_H
#define DUALITYWINDOW_H

#include "glow.h"
using namespace glow;

#include "dualitydata.h"

class DualityWindow : public GlowWindow
{
public:

    DualityWindow(float foreground, float background);
    virtual ~DualityWindow();

protected:

    virtual void drawAxis();

    // Refresh event
    virtual void OnEndPaint();

    // Function "callbacks" to mouse events:
    virtual void OnMouseDown(Glow::MouseButton button,
                             int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseUp(Glow::MouseButton button,
                           int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    static void
    unproject(const Point_E2i& pi, Point_E2d& pd);

    static void
    checkErrors();

private:

    DualityData* myDualityData;
    bool dragging;

    Point_E2d lastPoint;

    GLUquadricObj * qobj;

    float foreground, background;
};

#endif // DUALITYWINDOW_H
