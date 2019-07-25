/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ARCBALLWINDOW_H
#define ARCBALLWINDOW_H

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowViewTransform.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "opengl/fpscounter.h"
#include "topsubwindow.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 600;

class ArcballWindow : public GlowFixedSizeWindow,
                      public GlowPushButtonReceiver
{
    TopSubwindow * myTopSubwindow;

    FPScounter myfps;

    GlowLabelWidget * fpsIndicator;

    GlowPushButtonWidget * quitButton;

public:
    ArcballWindow()
        : GlowFixedSizeWindow("Arcball Window",
                              GlowWindow::autoPosition, GlowWindow::autoPosition,
                              initViewportWidth, initViewportHeight,
                              Glow::rgbBuffer,
                              Glow::noEvents),
          myfps()
    {
        GlowWidgetSubwindow* palette = new GlowWidgetSubwindow(this, 0, 500, 500, 100);

        GlowPanelParams panelParams;
        panelParams.x = 5;
        panelParams.y = 5;
        panelParams.width = 490;
        panelParams.height = 90;
        panelParams.style = GlowPanelWidget::etchedStyle;
        GlowPanelWidget* panel = new GlowPanelWidget(palette, panelParams);

        GlowLabelParams labelParams;
        labelParams.x = 50;
        labelParams.y = 35;
        labelParams.width = 100;
        labelParams.text = "0000.00 fps";
        fpsIndicator = new GlowLabelWidget(panel, labelParams);

        GlowPushButtonParams pbparams;
        pbparams.x = 300;
        pbparams.y = 35;
        pbparams.width = 100;
        pbparams.text = "Quit";
        pbparams.receiver = this;
        quitButton = new GlowPushButtonWidget(panel, pbparams);

        myTopSubwindow = new TopSubwindow(this, &myfps, fpsIndicator);
    }

protected:
    virtual void OnMessage(const GlowPushButtonMessage& /*message*/)
    {
        exit(0);
    }

//    virtual void OnReshape(int width, int height)
//    {
//        GlowSubwindow::OnReshape(width, height);
//
//        myTopSubwindow->setupProjectionMatrices();
//    }
};

#endif // ARCBALLWINDOW_H
