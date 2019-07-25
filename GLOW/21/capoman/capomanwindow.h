/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CAPOMANWINDOW_H
#define CAPOMANWINDOW_H

#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

#include "glow.h"
#include "glowQuickPalette.h"
#include "glowMessageWindow.h"
#include "glowPushButtonWidget.h"
using namespace glow;

#include "misc/clock.h"
#include "misc/conversions.h"
#include "capomansubwindow.h"

const int initViewportWidth  = 500;
const int initViewportHeight = 640;

const int PLAYTIME = 5;         // seconds

class CapomanWindow
    : public GlowFixedSizeWindow,
      public GlowIdleReceiver,
      public GlowPushButtonReceiver
{
public:
    CapomanWindow()
        : GlowFixedSizeWindow("Capoman",
                              GlowWindow::autoPosition, GlowWindow::autoPosition,
                              initViewportWidth, initViewportHeight,
                              Glow::rgbBuffer,
                              Glow::noEvents),
          messageLabel(NULL),
          myClock()
    {
        myCapomanSubwindow = new CapomanSubwindow(this);

        GlowWidgetSubwindow* palette = new GlowWidgetSubwindow(this, 0, 500, 500, 140);

        GlowPanelParams panelParams;
        panelParams.x = 10;
        panelParams.y = 10;
        panelParams.width = 480;
        panelParams.height = 120;
        panelParams.style = GlowPanelWidget::etchedStyle;
        panel = new GlowPanelWidget(palette, panelParams);

        GlowLabelParams labelParams;
        labelParams.x = 50;
        labelParams.y = 45;
        labelParams.width = 100;
        labelParams.text = "    ";
        remainingTimeLabel = new GlowLabelWidget(panel, labelParams);

        displayMessage("Welcome!");

        GlowPushButtonParams pbparams;
        pbparams.receiver = this;
        pbparams.x = 300;
        pbparams.y = 40;
        pbparams.width = 80;
        pbparams.text = "Play";
        playButton = new GlowPushButtonWidget(panel, pbparams);

        Glow::RegisterFilter(myCapomanSubwindow);
    }

    void displayMessage(const char * c)
    {
        if(messageLabel)
            delete messageLabel;

        GlowLabelParams labelParams;
        labelParams.x = 150;
        labelParams.y = 45;
        labelParams.width = 100;
        labelParams.text = c;
        messageLabel = new GlowLabelWidget(panel, labelParams);
    }

protected:
    virtual void OnMessage(const GlowIdleMessage & /*message*/)
    {
        float seconds = myClock.getSecondsSinceStart();
        if(seconds - lastSeconds > 0.01) {
            Refresh();
            lastSeconds = seconds;
        }

        int remainingTime = PLAYTIME - int(myClock.getSecondsSinceStart());
        remainingTimeLabel->SetText( integer_to_char_const_ptr(remainingTime) );

        if(remainingTime <=0) {
            playButton->Show();
            Glow::UnregisterIdle(this);
            displayMessage("Time is up!");
        }
    }

    virtual void OnMessage(const GlowPushButtonMessage & /*message*/)
    {
        myClock = Clock();
        displayMessage("Play hard!");
        playButton->Hide();
        Glow::RegisterIdle(this);
    }

private:
    CapomanSubwindow * myCapomanSubwindow;

    GlowPanelWidget * panel;
    GlowLabelWidget * remainingTimeLabel;
    GlowLabelWidget * messageLabel;
    GlowPushButtonWidget * playButton;

    float lastSeconds;
    Clock myClock;
};

#endif // CAPOMANWINDOW_H
