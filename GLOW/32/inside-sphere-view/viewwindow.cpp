/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "viewwindow.h"

// initial values
const int initPixelWidth = 800;
const int initPixelHeight = 800;

const float initFOV = 60.0;
const float initZnear = 0.1;

ViewWindow::ViewWindow()
    : GlowWindow("View",
                 500, 0,
                 initPixelWidth, initPixelHeight,
                 Glow::rgbaBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                 Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
      myfps(),
      cameraYaw(0), cameraPitch(0)
{
    //----------------------------------------------------------------
    // myViewDataViewer
    //----------------------------------------------------------------
    myViewDataViewer = new ViewDataViewer(this, initPixelWidth, initPixelHeight);

    myViewDataViewer->setYawAndPitch(cameraYaw, cameraPitch);
    myViewDataViewer->setFOVandZnear(initFOV, initZnear);

    //----------------------------------------------------------------
    // Control window
    //----------------------------------------------------------------
    _controlWindow = new GlowQuickPaletteWindow("Controls", 0, 0);

    _controlWindow->AddLabel("View");

    fovslider   = _controlWindow->AddSlider(3.0,210.0,initFOV, GlowSliderWidget::defaultOptions,
                                            10,"%5.1f", "FOV=%5.1f",this);

    fovslider->Reshape(400, 100); // resize ignored.. what is the right way?

    znearslider = _controlWindow->AddSlider(1e-9,2.0, initZnear, GlowSliderWidget::logarithmic,
                                            10,"%5.1f", "ZNear=%5.10f",this);

    _fpsIndicator = _controlWindow->AddLabel("0000.00 fps");

    _quitButton = _controlWindow->AddPushButton("Quit", this);

    _controlWindow->Pack();
    //----------------------------------------------------------------
    // Recall that the control window must be initialized last.
    //----------------------------------------------------------------
}

ViewWindow::~ViewWindow()
{
    delete _controlWindow;
}

bool ViewWindow::OnBeginPaint()
{
    return true;                // do draw children
}

void ViewWindow::OnEndPaint()
{
    _fpsIndicator->SetText( myfps.getFrameRate().c_str() );
}

void ViewWindow::OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers)
{
    float xn, yn;
    NormalizeCoordinates(x, y, xn, yn);
    switch (button) {
    case Glow::leftButton:
        switch (modifiers) {
        case Glow::noModifier:
            beginXdrag = xn;
            beginYdrag = yn;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void ViewWindow::OnMouseDrag(int x, int y)
{
    float xn, yn;
    NormalizeCoordinates(x, y, xn, yn);

    cameraYaw   += (xn - beginXdrag) * 2.0;
    cameraPitch += (yn - beginYdrag) * 1.0;

    if(cameraPitch > M_PI_2)
        cameraPitch = M_PI_2;
    if(cameraPitch < -M_PI_2)
        cameraPitch = -M_PI_2;

    beginXdrag = xn;
    beginYdrag = yn;

    myViewDataViewer->setYawAndPitch(cameraYaw, cameraPitch);

    Refresh();
}

void ViewWindow::OnMouseUp(Glow::MouseButton /*button*/, int /*x*/, int /*y*/,
                           Glow::Modifiers /*modifiers*/)
{
}

void ViewWindow::OnReshape(int width, int height)
{
    int bigger = std::max( width, height );
    glViewport(0, 0, bigger, bigger); // Ensure aspect ratio is 1:1.
    myViewDataViewer->SetSize(width, height);
}

void ViewWindow::OnMessage(const GlowPushButtonMessage& message)
{
    if (message.widget == _quitButton) {
        exit(0);
    }
}

void
ViewWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                       Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case ' ':
        cameraYaw = cameraPitch = 0;
        myViewDataViewer->setYawAndPitch(cameraYaw, cameraPitch);
        Refresh();
        break;
    case 'q':
    case 'Q':
    case Glow::escapeKey:
        exit(0);                // We assume a single window is instantiated.
    default:
        ;
    }
}

void
ViewWindow::OnMessage(const GlowSliderMessage & /*message*/)
{
    myViewDataViewer->setFOVandZnear(fovslider->GetValue(), znearslider->GetValue());

    Refresh();
}
