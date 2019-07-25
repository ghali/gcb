/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef EULERANGLESWINDOW_H
#define EULERANGLESWINDOW_H

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowViewTransform.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "euleranglessubwindow.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 650;

class EulerAnglesWindow
    : public GlowFixedSizeWindow,
      public GlowPushButtonReceiver,
      public GlowSliderReceiver
{
public:
    EulerAnglesWindow()
        : GlowFixedSizeWindow("Euler Angles",
                              GlowWindow::autoPosition, GlowWindow::autoPosition,
                              initViewportWidth, initViewportHeight,
                              Glow::rgbBuffer,
                              Glow::noEvents)
    {
        myEulerAnglesSubwindow = new EulerAnglesSubwindow(this);

        GlowWidgetSubwindow* palette = new GlowWidgetSubwindow(this, 0, 500, 500, 150);

        GlowPanelParams panelParams;
        panelParams.x = 10;
        panelParams.y = 10;
        panelParams.width = 480;
        panelParams.height = 130;
        panelParams.style = GlowPanelWidget::etchedStyle;
        GlowPanelWidget* panel = new GlowPanelWidget(palette, panelParams);

        GlowLabeledSliderParams sliderParams;
        sliderParams.receiver = this;
        sliderParams.min = 0.0;
        sliderParams.max = 360.0;
        sliderParams.initial = 0.0;
        sliderParams.numTicks = 9;
        sliderParams.minmaxTemplate = "%5.1f";
        sliderParams.labelSpacing = 10;
        sliderParams.y = 30;
        sliderParams.width = 140;
        sliderParams.labelPosition = GlowLabeledSliderWidget::topLabelPosition;

        sliderParams.labelTemplate = "x=%5.1f";
        sliderParams.x = 20;
        xangle = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "y=%5.1f";
        sliderParams.x = 170;
        yangle = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "z=%5.1f";
        sliderParams.x = 330;
        zangle = new GlowLabeledSliderWidget(panel, sliderParams);


        GlowPushButtonParams pbparams;
        pbparams.receiver = this;
        pbparams.x = 20;
        pbparams.y = 90;
        pbparams.width = 80;
        pbparams.text = "Quit";
        quitButton = new GlowPushButtonWidget(panel, pbparams);
    }

protected:
    virtual void OnMessage(const GlowPushButtonMessage & /*message*/)
    {
        exit(0);
    }

    virtual void OnMessage(const GlowSliderMessage & /*message*/)
    {
        myEulerAnglesSubwindow->setEulerAngles(xangle->GetValue(), yangle->GetValue(), zangle->GetValue());
    }
private:
    EulerAnglesSubwindow * myEulerAnglesSubwindow;

    GlowPushButtonWidget * quitButton;

    GlowLabeledSliderWidget *      xangle;
    GlowLabeledSliderWidget *      yangle;
    GlowLabeledSliderWidget *      zangle;
};

#endif // EULERANGLESWINDOW_H
