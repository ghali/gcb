/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ORBITSWINDOW_H
#define ORBITSWINDOW_H

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
#include "glowViewTransform.h"
using namespace glow;

#include "misc/clock.h"
#include "orbitsdataviewer.h"

class OrbitsWindow :
    public GlowWindow,
    public GlowIdleReceiver
{
public:
    OrbitsWindow();
    virtual ~OrbitsWindow();

protected:
    virtual bool OnBeginPaint();
    virtual void OnEndPaint();

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    virtual void OnReshape(int width, int height);

    virtual void OnMessage(const GlowIdleMessage& message);

private:
    OrbitsDataViewer * myOrbitsDataViewer;
    GlowViewManipulator *          _manip;

    Clock myclock;
    float lastSeconds;
};

#endif // ORBITSWINDOW_H
