/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <cmath>

#include "orbitswindow.h"

// initial values
const int initPixelWidth = 700;
const int initPixelHeight = 700;

OrbitsWindow::OrbitsWindow()
    : GlowWindow("Orbits",
                 GlowWindow::autoPosition, GlowWindow::autoPosition,
                 initPixelWidth, initPixelHeight,
                 Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                 Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents)
{
    //----------------------------------------------------------------
    // Manipulator
    //----------------------------------------------------------------
    GlowViewManipulatorParams manipparams = GlowViewManipulatorParams::defaults;
    manipparams.draw = true;
    // manipparams.axisConstraintsActive = true;
    // manipparams.axisConstraints.push_back(Vec3f(1,0,0));
    _manip = new GlowViewManipulator(this, manipparams);

    _manip->SetSpinnable(true);

    myOrbitsDataViewer = new OrbitsDataViewer(_manip);

    Glow::RegisterIdle(this);
}

OrbitsWindow::~OrbitsWindow()
{
}

bool OrbitsWindow::OnBeginPaint()
{
    return true;                // do draw children
}

void OrbitsWindow::OnEndPaint()
{
}

void OrbitsWindow::OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers)
{
    if (!_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        switch (button) {
        case Glow::leftButton:
            switch (modifiers) {
            case Glow::noModifier:
                _manip->BeginRotationDrag(xn, yn);
                break;
            case Glow::shiftModifier:
                _manip->BeginTranslationDrag(xn, yn);
                break;
            default:
                break;
            }
            break;
        case Glow::middleButton:
            _manip->BeginScaleDrag(xn, yn);
            break;
        default:
            break;
        }
    }
}

void OrbitsWindow::OnMouseDrag(int x, int y)
{
    if (_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->InDrag(xn, yn);
    }
}

void OrbitsWindow::OnMouseUp(Glow::MouseButton /*button*/, int x, int y,
                             Glow::Modifiers /*modifiers*/)
{
    if (_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->EndDrag(xn, yn);
    }
}

void OrbitsWindow::OnReshape(int width, int height)
{
    int bigger = std::max( width, height );
    ::glViewport(0, 0, bigger, bigger); // cheaply ensure 1:1 aspect
}

void
OrbitsWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                         Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'w': 
        myOrbitsDataViewer->writeImage("image", Width(), Height());
        break;
    case 'q':
    case 'Q':
    case Glow::escapeKey:
        exit(0);
    default:
        ;
    }
}

void
OrbitsWindow::OnMessage(const GlowIdleMessage & /*message*/)
{
    float seconds = myclock.getSecondsSinceStart();
    if(seconds - lastSeconds > 0.01) {
        Refresh();
        lastSeconds = seconds;
    }
}
