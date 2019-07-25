/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SLERP_ON_S1_WINDOW_H
#define SLERP_ON_S1_WINDOW_H

#include <iostream>
using namespace std;

#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using std::vector;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowLabelWidget.h"
#include "glowSliderWidget.h"
using namespace glow;

typedef double MyDouble;
#include "geometry/S1/point_s1.h"
typedef Point_S1<MyDouble> Point_S1d;

#include "slerp_on_s1_subwindow.h"

class Slerp_on_s1_window
    : public GlowWindow,
      public GlowSliderReceiver
{
    Slerp_on_s1_subwindow * mySlerp_on_s1_subwindow;

    GlowSliderWidget*         angle0Slider;
    GlowSliderWidget*         angle1Slider;
    GlowSliderWidget*  interpolationSlider;

    GlowLabelWidget* determinantIndicator;

    double angle0, angle1, i;
public:
    Slerp_on_s1_window() : GlowWindow("Slerp on S1", GlowWindow::autoPosition, GlowWindow::autoPosition,
                                      500, 700, Glow::rgbBuffer | Glow::doubleBuffer,
                                      Glow::noEvents),
                           angle0(0.0), angle1(M_PI/2.0), i(0.5)
    {
        mySlerp_on_s1_subwindow = new Slerp_on_s1_subwindow(this);

        GlowWidgetSubwindow* palette = new GlowWidgetSubwindow(this, 0, 500, 500, 200);

        GlowPanelParams panelParams;
        panelParams.x = 10;
        panelParams.y = 10;
        panelParams.width = 480;
        panelParams.height = 180;
        panelParams.style = GlowPanelWidget::etchedStyle;
        GlowPanelWidget* panel = new GlowPanelWidget(palette, panelParams);

        GlowLabeledSliderParams sliderParams;
        sliderParams.receiver = this;
        sliderParams.min = 0.0;
        sliderParams.max = 2 * M_PI;
        sliderParams.numTicks = 9;
        sliderParams.minmaxTemplate = "%5.1f";
        sliderParams.labelSpacing = 0;
        sliderParams.x = 120;
        sliderParams.width = 300;
        //default: sliderParams.labelPosition = GlowLabeledSliderWidget::leftLabelPosition;

        sliderParams.labelTemplate = "angle0=%5.1f";
        sliderParams.initial = angle0;
        sliderParams.y = 20;
        angle0Slider = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.labelTemplate = "angle1=%5.1f";
        sliderParams.initial = angle1;
        sliderParams.y = 70;
        angle1Slider = new GlowLabeledSliderWidget(panel, sliderParams);

        sliderParams.min = 0.0;
        sliderParams.max = 1.0;
        sliderParams.initial = i;
        sliderParams.labelTemplate = "i=%5.1f";
        sliderParams.y = 120;
        interpolationSlider = new GlowLabeledSliderWidget(panel, sliderParams);

        mySlerp_on_s1_subwindow->setPoints(angle0, angle1, i);
    }

    void OnMessage(const GlowSliderMessage& message)
    {
        if (message.widget == angle0Slider)
            angle0 = message.value;
        if (message.widget == angle1Slider)
            angle1 = message.value;
        if (message.widget == interpolationSlider)
            i = message.value;

        mySlerp_on_s1_subwindow->setPoints(angle0, angle1, i);
        Refresh();
    }
};

#endif // SLERP_ON_S1_WINDOW_H
