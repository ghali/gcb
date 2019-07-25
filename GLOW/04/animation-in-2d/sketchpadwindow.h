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

#include "glowPushButtonWidget.h"
#include "glowCheckBoxWidget.h"
#include "glowQuickPalette.h"
#include "glowPanelWidget.h"
#include "glowLabelWidget.h"
#include "glowViewTransform.h"

using namespace glow;

#include "sketchpaddata.h"

class SketchpadWindow :
    public GlowWindow,
    public GlowIdleReceiver,
    public GlowSliderReceiver,
    public GlowCheckBoxReceiver,
    public GlowRadioButtonReceiver
{
public:
    SketchpadWindow();

protected:
    virtual void OnEndPaint();

    virtual void OnMessage(const GlowIdleMessage& message);

    virtual void OnKeyboard(Glow::KeyCode key, int x, int y, Glow::Modifiers modifiers);

    virtual void OnReshape(int width, int height);

    virtual void OnMessage(const GlowSliderMessage& message);

    virtual void OnMessage(const GlowCheckBoxMessage& message);

    virtual void OnMessage(const GlowRadioButtonMessage& message);

private:
    void quitProg();
    static int howManyOfMe;

    SketchpadData mySketchpadData;

    int viewportWidth, viewportHeight;

    int structureDrawn;

    double _alpha;              // in [0..1]
    bool basculateUp;

    // Glow widgets
    GlowQuickPaletteWindow* controlWindow;

    GlowSliderWidget*     mySlider;

    GlowSliderWidget*     scale1x;
    GlowSliderWidget*     scale1y;
    GlowSliderWidget*     rotate1;
    GlowSliderWidget*     translate1x;
    GlowSliderWidget*     translate1y;

    GlowSliderWidget*     scale2x;
    GlowSliderWidget*     scale2y;
    GlowSliderWidget*     rotate2;
    GlowSliderWidget*     translate2x;
    GlowSliderWidget*     translate2y;

    GlowCheckBoxWidget* animationCheckbox;

    GlowQuickRadioGroupWidget* _RBGroup;
    GlowRadioButtonWidget*   _rb1;
    GlowRadioButtonWidget*   _rb2;
    GlowRadioButtonWidget*   _rb3;
};

#endif // SKETCHPADWINDOW_H
