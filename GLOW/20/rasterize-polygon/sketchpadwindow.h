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

#include <vector>

#include "glow.h"
using namespace glow;

#include "./rasterimage.h"

enum InputState
{
    STARTING,                   // no points entered yet
    ENTERING_SIMPLE_POLY,       // one or more points entered
    ENTERING_DONE
};

class SketchpadWindow : public GlowWindow
{
public:
    SketchpadWindow(bool readFromFile);

protected:
    virtual void OnEndPaint();

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);
    virtual void OnReshape(int width, int height);

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseMotion(int x, int y);

private:
    void quitProg();
    static int howManyOfMe;

    int viewportWidth;
    int viewportHeight;

    RasterImage     myRasterImage;
    Polygon_E2d          simplePoly;
    std::vector<Polygon_E2d> allPolygons;
    InputState       myInputState;

    Point_E2d sourcePoint, currentPoint;
};

#endif // SKETCHPADWINDOW_H
