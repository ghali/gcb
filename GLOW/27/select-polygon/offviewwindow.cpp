/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "offviewwindow.h"
#include "offviewdataviewer.h"

// initial values
const int initPixelWidth  = 800;
const int initPixelHeight = 800;

OffviewWindow::OffviewWindow(string filename)
    : GlowWindow("Offview", GlowWindow::autoPosition, GlowWindow::autoPosition,
                 initPixelWidth, initPixelHeight,
                 Glow::rgbBuffer | Glow::doubleBuffer | Glow::depthBuffer,
                 Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
      myGLstringRenderer(GLUT_BITMAP_HELVETICA_12, 0.05, 0.05),
      extrude_is_dragging(false)
{
    //----------------------------------------------------------------
    // Manipulator
    //----------------------------------------------------------------
    GlowViewManipulatorParams manipparams = GlowViewManipulatorParams::defaults;
    // manipparams.draw = true;
    _manip = new GlowViewManipulator(this, manipparams);

    _manip->SetSpinnable(true);

    myOffviewDataViewer = new OffviewDataViewer(filename, _manip);
}

OffviewWindow::~OffviewWindow()
{
}

bool OffviewWindow::OnBeginPaint()
{
    return true;                // do draw children
}

void OffviewWindow::OnEndPaint()
{
    myGLstringRenderer.draw(myfps.getFrameRate());
}

void OffviewWindow::OnMouseDown(Glow::MouseButton button,
                                int x, int y,
                                Glow::Modifiers modifiers)
{
    if(!_manip->IsDragging())
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
                myOffviewDataViewer->pickPolygon(x,y);
                break;
            default:
                break;
            }
            break;
        case Glow::middleButton:
            _manip->BeginScaleDrag(xn, yn);
            break;
        case Glow::rightButton:
            myOffviewDataViewer->extrude_faces();
            extrude_is_dragging = true;
            extrude_ystart = yn;
            break;
        default:
            break;
        }
    }
}

void OffviewWindow::OnMouseDrag(int x, int y)
{
    if(_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->InDrag(xn, yn);
    }

    if(extrude_is_dragging)
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        myOffviewDataViewer->extrude_drag(yn, extrude_ystart);
    }
}

void OffviewWindow::OnMouseUp(Glow::MouseButton /*button*/,
                              int x, int y,
                              Glow::Modifiers /*modifiers*/)
{
    if(_manip->IsDragging())
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        _manip->EndDrag(xn, yn);
    }
    if(extrude_is_dragging)
    {
        float xn, yn;
        NormalizeCoordinates(x, y, xn, yn);
        extrude_is_dragging = false;
    }
}

void OffviewWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                               Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'q': case 'Q': case Glow::escapeKey: 
        exit(0);
    default: ;
    }
}

void OffviewWindow::OnReshape(int width, int height)
{
    int bigger = std::max( width, height );
    // Update the viewport to specify the entire window
    ::glViewport(0, 0, bigger, bigger);
}

void OffviewWindow::OnMessage(const GlowPushButtonMessage & /*message*/)
{
}

void OffviewWindow::OnMessage(const GlowCheckBoxMessage & /*message*/)
{
}
