/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SPHERICAL_MODELSWINDOW_H
#define SPHERICAL_MODELSWINDOW_H

#include "glow.h"
#include "glowViewTransform.h"
using namespace glow;

#include "opengl/fpscounter.h"
#include "opengl/gldrawstring.h"
#include "opengl/glimagewriter.h"

#include "spherical_models_dataviewer.h"

class Spherical_models_window :
    public GlowWindow
{
public:
    Spherical_models_window();
    virtual ~Spherical_models_window() {}

protected:
    virtual bool OnBeginPaint();
    virtual void OnEndPaint();

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    virtual void OnReshape(int width, int height);

private:
    Spherical_models_dataviewer * mySpherical_models_dataviewer;
    GlowViewManipulator *            _manip;
    FPScounter                        myfps;
    GLstringRenderer     myGLstringRenderer;
    GLimageWriter           myGLimageWriter;
};

#endif // SPHERICAL_MODELSWINDOW_H
