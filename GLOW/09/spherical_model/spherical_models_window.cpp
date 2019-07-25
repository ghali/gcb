/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "spherical_models_window.h"

// initial values
const int initPixelWidth = 600;
const int initPixelHeight = 600;

Spherical_models_window::Spherical_models_window()
    : GlowWindow("Spherical_Models",
                 GlowWindow::autoPosition, GlowWindow::autoPosition,
                 initPixelWidth, initPixelHeight,
                 Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                 Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
      myfps(),
      myGLstringRenderer(GLUT_BITMAP_HELVETICA_12, 0.05, 0.05),
      myGLimageWriter()
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

    mySpherical_models_dataviewer = new Spherical_models_dataviewer(_manip);

}

bool Spherical_models_window::OnBeginPaint()
{
    return true;                // do draw children
}

void Spherical_models_window::OnEndPaint()
{
//     myGLstringRenderer.draw(myfps.getFrameRate());
}

void Spherical_models_window::OnMouseDown(Glow::MouseButton button, int x, int y, Glow::Modifiers modifiers)
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
            case Glow::ctrlModifier:
                _manip->BeginScaleDrag(xn, yn);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Spherical_models_window::OnMouseDrag(int x, int y)
{
    if (_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->InDrag(xn, yn);
    }
}

void Spherical_models_window::OnMouseUp(Glow::MouseButton /*button*/, int x, int y,
                                        Glow::Modifiers /*modifiers*/)
{
    if (_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->EndDrag(xn, yn);
    }
}

// Respond to reshape events
void Spherical_models_window::OnReshape(int width, int height)
{
    int bigger = std::max( width, height );
    ::glViewport(0, 0, bigger, bigger); // cheaply ensure 1:1 aspect
}

void
Spherical_models_window::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                                    Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 't': mySpherical_models_dataviewer->setObject('t'); break;
    case 'c': mySpherical_models_dataviewer->setObject('c'); break;
    case 'o': mySpherical_models_dataviewer->setObject('o'); break;
    case 'i': mySpherical_models_dataviewer->setObject('i'); break;
    case 'd': mySpherical_models_dataviewer->setObject('d'); break;

    case 'w': myGLimageWriter.writeImage("image", GlowSubwindow::Width(), GlowSubwindow::Height()); break;
    case 'q': case 'Q': case Glow::escapeKey: exit(0);
    default: ;
    }
    Refresh();
}
