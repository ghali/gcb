/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SKETCHPADWINDOW_H
#define SKETCHPADWINDOW_H

#include "glow.h"
using namespace glow;

#include "sketchpaddata.h"

class SketchpadWindow : public GlowWindow
{
public:
    SketchpadWindow();
    virtual ~SketchpadWindow();

protected:
    virtual void OnEndPaint();

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);
    virtual void OnReshape(int width, int height);

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseMotion(int x, int y);
    virtual void OnMouseExit();

    void setupProjection(int viewportWidth, int viewportHeight);

    inline Point_E2<int>
    unproject(const Point_E2<int>& pin);

private:
    void showTime(float t);
    void quitProg();

    static int howManyOfMe;

    int viewportWidth;
    int viewportHeight;

    SketchpadData mySketchpadData;

    bool hoveringOverPixel;
    Point_E2<int> hoveringPixel;

    bool dragging;
    Point_E2<int> draggingSource;
    Point_E2<int> draggingTarget;
};

#endif // SKETCHPADWINDOW_H
