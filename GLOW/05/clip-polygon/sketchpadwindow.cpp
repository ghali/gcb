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
#include <cstdlib>
#include "opengl/gldraw_e2.h"
#include "sketchpaddata.h"
#include "sketchpadwindow.h"

// initial values
int SketchpadWindow::howManyOfMe = 0;
const int initViewportWidth = 640;
const int initViewportHeight = 480;


SketchpadWindow::SketchpadWindow() :
    GlowWindow("Sketchpad",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initViewportWidth, initViewportHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents | Glow::motionEvents ),

    mySketchpadData(),
    myInputState(STARTING),

    viewportWidth(initViewportWidth),
    viewportHeight(initViewportHeight)
{
    GLdraw_E2<MyDouble>::setup_projection(Point_E2d(0,0),
                                          Point_E2d(viewportWidth, viewportHeight));
    ++howManyOfMe;
}

void
SketchpadWindow::quitProg()
{
    howManyOfMe--;
    Close();
    if(!howManyOfMe) exit(0);
}

// Redraw function
//----------------------------------------------------------------
void
SketchpadWindow::OnEndPaint()
{
    GLdraw_E2<MyDouble>::clear_screen();

    mySketchpadData.drawClippingPolygon();

    switch(myInputState) {
    case STARTING:
        break;
    case ENTERING_SIMPLE_POLY:
    case ENTERING_DONE:
        mySketchpadData.drawPolygon();
        break;
    }
}

//----------------------------------------------------------------
void
SketchpadWindow::OnMouseDown(Glow::MouseButton button,
                             int x, int y, Glow::Modifiers /*modifiers*/)
{
    switch(myInputState) {
    case ENTERING_DONE:         // restart
        mySketchpadData.clear();
    case STARTING:
        currentPoint = GLdraw_E2<MyDouble>::unproject(Point_E2i(x,y));
        mySketchpadData.insertPoint(currentPoint);
        mySketchpadData.insertPoint(currentPoint);
        myInputState = ENTERING_SIMPLE_POLY;
        break;
    case ENTERING_SIMPLE_POLY:
        currentPoint = GLdraw_E2<MyDouble>::unproject(Point_E2i(x,y));
        mySketchpadData.insertPoint(currentPoint);
        if(button == Glow::rightButton) {
            myInputState = ENTERING_DONE;
        }
        break;
    }
    Refresh();
}

// OnMouseMotion is defined in GlowSubwindow
void
SketchpadWindow::OnMouseMotion(int x, int y) // in glut it's: void passiveMotion(int x, int y)
{
    switch(myInputState) {
    case STARTING:
        break;
    case ENTERING_SIMPLE_POLY:
        currentPoint = GLdraw_E2<MyDouble>::unproject(Point_E2i(x,y));
        mySketchpadData.updateLastPoint(currentPoint);
        break;
    case ENTERING_DONE:
        break;
    }
    Refresh();
}

void
SketchpadWindow::OnMouseDrag(int /*x*/, int /*y*/)
{}

void
SketchpadWindow::OnMouseUp(Glow::MouseButton /*button*/,
                           int /*x*/, int /*y*/, Glow::Modifiers /*modifiers*/)
{
    switch(myInputState) {
    case STARTING:
        break;
    case ENTERING_SIMPLE_POLY:
        break;
    case ENTERING_DONE:
        break;
    }
    Refresh();
}

void
SketchpadWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'q': case 'Q': case Glow::escapeKey: quitProg();
    default:
        ;
    }
}

void
SketchpadWindow::OnReshape(int width, int height)
{
    ::glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;

    GLdraw_E2<MyDouble>::setup_projection(Point_E2d(0,0),
                                          Point_E2d(viewportWidth, viewportHeight));
}
