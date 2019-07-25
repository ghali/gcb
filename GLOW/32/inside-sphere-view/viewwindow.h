/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef OFFVIEWWINDOW_H
#define OFFVIEWWINDOW_H

#include "glow.h"
#include "glowPushButtonWidget.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
#include "glowViewTransform.h"
using namespace glow;

#include "opengl/fpscounter.h"
#include "viewdataviewer.h"

class ViewWindow :
    public GlowWindow,
    public GlowPushButtonReceiver,
    public GlowSliderReceiver
{
public:
    ViewWindow();
    virtual ~ViewWindow();

protected:
    virtual bool OnBeginPaint();
    virtual void OnEndPaint();

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    virtual void OnReshape(int width, int height);

    virtual void OnMessage(const GlowPushButtonMessage& message);

    virtual void OnMessage(const GlowSliderMessage& message);

private:
    ViewDataViewer *  myViewDataViewer;

    FPScounter myfps;

    GlowLabelWidget *          _fpsIndicator;
    GlowQuickPaletteWindow *  _controlWindow;
    GlowPushButtonWidget *       _quitButton;

    GlowLabeledSliderWidget *      fovslider;
    GlowLabeledSliderWidget *    znearslider;

    double beginXdrag, beginYdrag;
    double cameraYaw, cameraPitch;
};

#endif // OFFVIEWWINDOW_H
