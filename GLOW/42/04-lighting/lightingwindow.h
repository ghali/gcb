/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <iostream>
using namespace std;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowViewTransform.h"
#include "glowCheckBoxWidget.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "lightingsubwindow.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 740;

class LightingWindow
    : public GlowFixedSizeWindow,
      public GlowSliderReceiver,
      public GlowCheckBoxReceiver,
      public GlowPushButtonReceiver
{
public:
    LightingWindow()
        : GlowFixedSizeWindow("Lighting",
                              GlowWindow::autoPosition, GlowWindow::autoPosition,
                              initViewportWidth, initViewportHeight,
                              Glow::rgbBuffer,
                              Glow::noEvents)
    {
        myLightingSubwindow = new LightingSubwindow(this);

        GlowWidgetSubwindow* palette = new GlowWidgetSubwindow(this, 0, 500, 500, 240);

        GlowPanelParams panelParams;
        panelParams.x = 10;
        panelParams.y = 10;
        panelParams.width = 480;
        panelParams.height = 220;
        panelParams.style = GlowPanelWidget::etchedStyle;
        GlowPanelWidget* panel = new GlowPanelWidget(palette, panelParams);

        GlowLabeledSliderParams sliderParams;
        sliderParams.receiver = this;
        sliderParams.min = -180.0;
        sliderParams.max = 180.0;
        sliderParams.initial = 0.0;
        sliderParams.numTicks = 9;
        sliderParams.minmaxTemplate = "%5.0f";
        sliderParams.labelSpacing = 10;
        sliderParams.y = 30;
        sliderParams.width = 140;
        sliderParams.labelPosition = GlowLabeledSliderWidget::topLabelPosition;

        sliderParams.labelTemplate = "Light =%5.0f";
        sliderParams.x = 20;
        lightSlider = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "Viewer =%5.0f";
        sliderParams.x = 170;
        viewerSlider = new GlowLabeledSliderWidget(panel, sliderParams);

        // Lights checkboxes
        GlowCheckBoxParams checkBoxParams;
        checkBoxParams.receiver = this;
        checkBoxParams.y = 110;
        checkBoxParams.state = GlowCheckBoxWidget::on;

        checkBoxParams.text = "Moving Light";
        checkBoxParams.x = 20;
        movingLightCheckBox = new GlowCheckBoxWidget(panel, checkBoxParams);

        checkBoxParams.text = "Static Light";
        checkBoxParams.x = 170;
        staticLightCheckBox = new GlowCheckBoxWidget(panel, checkBoxParams);

        checkBoxParams.text = "Head Light";
        checkBoxParams.x = 320;
        headLightCheckBox = new GlowCheckBoxWidget(panel, checkBoxParams);

        // Push Button
        GlowPushButtonParams pbparams;
        pbparams.receiver = this;
        pbparams.x = 20;
        pbparams.y = 170;
        pbparams.width = 80;
        pbparams.text = "Quit";
        quitButton = new GlowPushButtonWidget(panel, pbparams);
    }

protected:
    virtual void OnMessage(const GlowPushButtonMessage & /*message*/)
    {
        exit(0);
    }

    virtual void OnMessage(const GlowSliderMessage& message)
    {
        if (message.widget == lightSlider || message.widget == viewerSlider)
            myLightingSubwindow->setAngles(lightSlider->GetValue(), viewerSlider->GetValue());
    }
    virtual void OnMessage(const GlowCheckBoxMessage & /*message*/)
    {
        myLightingSubwindow->saveLights(movingLightCheckBox->GetState() == GlowCheckBoxWidget::on,
                                        staticLightCheckBox->GetState() == GlowCheckBoxWidget::on,
                                        headLightCheckBox->GetState() == GlowCheckBoxWidget::on);
    }
private:
    LightingSubwindow * myLightingSubwindow;

    GlowLabeledSliderWidget *        lightSlider;
    GlowLabeledSliderWidget *       viewerSlider;

    GlowCheckBoxWidget *     movingLightCheckBox;
    GlowCheckBoxWidget *     staticLightCheckBox;
    GlowCheckBoxWidget *       headLightCheckBox;

    GlowPushButtonWidget *       quitButton;
};
