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
#include <algorithm>

#include "glowMessageWindow.h"

#include "sketchpadwindow.h"
#include "opengl/gldraw_e2.h"

const int initViewportWidth = 750;
const int initViewportHeight = 750;

const Point_E2d wmin(-9.2,-9.2);
const Point_E2d wmax( 9.2, 9.2);

int SketchpadWindow::howManyOfMe = 0;

SketchpadWindow::SketchpadWindow(bool readFromFile) :
    GlowWindow("Sketchpad",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initViewportWidth, initViewportHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::keyboardEvents | Glow::mouseEvents | Glow::motionEvents
               | Glow::dragEvents | Glow::focusEvents),

    viewportWidth(initViewportWidth),
    viewportHeight(initViewportHeight),
    myRasterImage(wmin, wmax),
    myInputState(STARTING)
{
    GLdraw_E2<double>::setup_projection(wmin, wmax);
    ++howManyOfMe;

    if(readFromFile) 
        while(!cin.eof()) {
            int numSides;
            cin >> numSides;
            for(int i=0;i<numSides;++i) {
                double x, y;
                cin >> x >> y;
                simplePoly.push_back(Point_E2d(x,y));
            }
            myRasterImage.scanConvert(simplePoly);
            allPolygons.push_back(simplePoly);
            simplePoly.clear();
        }
}

void
SketchpadWindow::quitProg()
{
    howManyOfMe--;
    Close();
    if(!howManyOfMe) exit(0);
}

void draw(const Polygon_E2d& p) { GLdraw_E2<double>::draw_polygon(p); }

void
SketchpadWindow::OnEndPaint()
{
    GLdraw_E2<double>::clear_screen();

    myRasterImage.drawGrid();
    myRasterImage.drawPixels();

    std::for_each(allPolygons.begin(), allPolygons.end(), draw);

    switch(myInputState) {
    case STARTING:
        break;
    case ENTERING_SIMPLE_POLY:
    case ENTERING_DONE:
        GLdraw_E2<double>::draw_polygon(simplePoly);
        break;
    }
}

void
SketchpadWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'c': case 'C':
        myRasterImage.clear();
        simplePoly.clear();
        allPolygons.clear();
        myInputState = STARTING;
        Refresh();
        break;
    case 'q': case 'Q': case Glow::escapeKey: quitProg();
    default: ;
    }
}

void
SketchpadWindow::OnReshape(int width, int height)
{
    // To simplify things, we don't tell myRasterImage about
    // the new window size. We should then derive SketchpadWindow
    // from GlowFixedSizeWindow, but not all window managers keep
    // the window fixed.

    ::glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;

    GLdraw_E2<double>::setup_projection(wmin, wmax);
}

void
SketchpadWindow::OnMouseDown(Glow::MouseButton button,
                             int x, int y, Glow::Modifiers /*modifiers*/)
{
    switch(myInputState) {
    case ENTERING_DONE:         // restart
        allPolygons.push_back(simplePoly);
        simplePoly.clear();
    case STARTING:
        currentPoint = GLdraw_E2<double>::unproject(Point_E2i(x,y));
        simplePoly.push_back(currentPoint);
        simplePoly.push_back(currentPoint);
        myInputState = ENTERING_SIMPLE_POLY;
        break;
    case ENTERING_SIMPLE_POLY:
        currentPoint = GLdraw_E2<double>::unproject(Point_E2i(x,y));
        simplePoly.push_back(currentPoint);
        if(button == Glow::rightButton) {
            myRasterImage.scanConvert(simplePoly);
            myInputState = ENTERING_DONE;
        }
        break;
    }
    Refresh();
}

// Override GlowSubwindow::OnMouseMotion
void
SketchpadWindow::OnMouseMotion(int x, int y) // in glut it's: void passiveMotion(int x, int y)
{
    switch(myInputState) {
    case STARTING:
        break;
    case ENTERING_SIMPLE_POLY:
        currentPoint = GLdraw_E2<double>::unproject(Point_E2i(x,y));
        simplePoly.update_last_point(currentPoint);
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
