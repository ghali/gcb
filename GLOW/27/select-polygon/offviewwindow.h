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

#include <string>
#include <algorithm>
using std::string;

#include "glow.h"

#include "glowPushButtonWidget.h"
#include "glowCheckBoxWidget.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
#include "glowViewTransform.h"

using namespace glow;

#include "opengl/fpscounter.h"
#include "opengl/gldrawstring.h"

class OffviewData;
class OffviewDataViewer;

class OffviewWindow :
    public GlowWindow,
    public GlowPushButtonReceiver,
    public GlowCheckBoxReceiver
{
public:
    OffviewWindow(string filename);

    virtual ~OffviewWindow();

protected:

    virtual bool OnBeginPaint();

    virtual void OnEndPaint();

    virtual void OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);
    virtual void OnMouseDrag(int x, int y);
    virtual void OnMouseUp(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    virtual void OnReshape(int width, int height);

    virtual void OnMessage(const GlowPushButtonMessage& message);
    virtual void OnMessage(const GlowCheckBoxMessage& message);

private:

    GlowViewManipulator * _manip;

    OffviewDataViewer * myOffviewDataViewer;

    FPScounter myfps;

    GLstringRenderer myGLstringRenderer;

    bool extrude_is_dragging;
    float extrude_ystart;
};

#endif // OFFVIEWWINDOW_H
