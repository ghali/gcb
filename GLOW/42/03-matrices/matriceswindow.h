/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef MATRICESWINDOW_H
#define MATRICESWINDOW_H

#include <iostream>
using namespace std;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowViewTransform.h"
#include "glowCheckBoxWidget.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "matricessubwindow.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 740;

class MatricesWindow
    : public GlowFixedSizeWindow,
      public GlowSliderReceiver,
      public GlowCheckBoxReceiver,
      public GlowPushButtonReceiver
{
public:
    MatricesWindow()
        : GlowFixedSizeWindow("Projection and ModelView Matrices",
                              GlowWindow::autoPosition, GlowWindow::autoPosition,
                              initViewportWidth, initViewportHeight,
                              Glow::rgbBuffer,
                              Glow::noEvents)
    {
        myMatricesSubwindow = new MatricesSubwindow(this);

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

        sliderParams.labelTemplate = "angle1 =%5.0f";
        sliderParams.x = 20;
        slider1 = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "angle2 =%5.0f";
        sliderParams.x = 170;
        slider2 = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "angle3=%5.0f";
        sliderParams.x = 330;
        slider3 = new GlowLabeledSliderWidget(panel, sliderParams);


        // FOV
        sliderParams.labelTemplate = "FOV=%5.0f";
        sliderParams.min = 10.0;
        sliderParams.max = 120.0;
        sliderParams.initial = 40.0;
        sliderParams.x = 20;
        sliderParams.y = 110;
        fovSlider = new GlowLabeledSliderWidget(panel, sliderParams);

        // Viewer
        sliderParams.labelTemplate = "Viewer=%5.0f";
        sliderParams.min = 10.0;
        sliderParams.max = 120.0;
        sliderParams.initial = 20.0;
        sliderParams.x = 170;
        viewerSlider = new GlowLabeledSliderWidget(panel, sliderParams);

        // Lock checkbox
        GlowCheckBoxParams checkBoxParams;
        checkBoxParams.receiver = this;
        checkBoxParams.text = "Lock";
        checkBoxParams.x = 330;
        checkBoxParams.y = 110;
        lockCheckBox = new GlowCheckBoxWidget(panel, checkBoxParams);

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

    double lockedFOV() {
        double FOV = 1200.0/viewerSlider->GetValue();
        fovSlider->SetValue(FOV);
        fovSlider->Refresh();
        return FOV;
    }
    double lockedViewer() {
        double viewer = 1200.0/fovSlider->GetValue();
        viewerSlider->SetValue(viewer);
        viewerSlider->Refresh();
        return viewer;
    }

    virtual void OnMessage(const GlowSliderMessage& message)
    {
        if (message.widget == slider1 || message.widget == slider2 || message.widget == slider3)
            myMatricesSubwindow->setAngles(slider1->GetValue(), slider2->GetValue(), slider3->GetValue());
        else if (message.widget == fovSlider)
            if (lockCheckBox->GetState() == GlowCheckBoxWidget::on)
                myMatricesSubwindow->setCamera(fovSlider->GetValue(), lockedViewer());
            else
                myMatricesSubwindow->setCamera(fovSlider->GetValue(), viewerSlider->GetValue());
        else if (message.widget == viewerSlider)
            if (lockCheckBox->GetState() == GlowCheckBoxWidget::on)
                myMatricesSubwindow->setCamera(lockedFOV(), viewerSlider->GetValue());
            else
                myMatricesSubwindow->setCamera(fovSlider->GetValue(), viewerSlider->GetValue());
    }
    virtual void OnMessage(const GlowCheckBoxMessage & /*message*/)
    {
        if (lockCheckBox->GetState() == GlowCheckBoxWidget::on)
            myMatricesSubwindow->setCamera(fovSlider->GetValue(), lockedViewer());
    }
private:
    MatricesSubwindow * myMatricesSubwindow;

    GlowLabeledSliderWidget *       slider1;
    GlowLabeledSliderWidget *       slider2;
    GlowLabeledSliderWidget *       slider3;

    GlowLabeledSliderWidget *     fovSlider;
    GlowLabeledSliderWidget *  viewerSlider;

    GlowCheckBoxWidget *       lockCheckBox;

    GlowPushButtonWidget *       quitButton;
};

#endif // MATRICESWINDOW_H
