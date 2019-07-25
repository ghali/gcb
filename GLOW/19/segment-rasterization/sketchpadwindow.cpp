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
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include "glowMessageWindow.h"

#include "sketchpadwindow.h"

const int numberOfRandomLines = 1000000;

const int initViewportWidth = 750;
const int initViewportHeight = 750;

int SketchpadWindow::howManyOfMe = 0;

SketchpadWindow::SketchpadWindow() :
    GlowWindow("Sketchpad",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initViewportWidth, initViewportHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::keyboardEvents | Glow::mouseEvents | Glow::motionEvents
               | Glow::dragEvents | Glow::focusEvents),

    viewportWidth(initViewportWidth),
    viewportHeight(initViewportHeight),
    mySketchpadData (viewportWidth, viewportHeight),
    hoveringOverPixel(false),
    dragging(false)
{
    setupProjection(viewportWidth, viewportHeight);
    ++howManyOfMe;
}

SketchpadWindow::~SketchpadWindow()
{
}

void
SketchpadWindow::quitProg()
{
    howManyOfMe--;
    Close();
    if(!howManyOfMe) exit(0);
}

void
SketchpadWindow::showTime(float t)
{
    ostringstream os;
    os << "Wall clock time spent to rasterize " << numberOfRandomLines << " lines is "
       << std::fixed << std::setprecision(3) << t << " seconds" << std::endl;

    GlowMessageWindow* gmw = new GlowMessageWindow("Timing result", 300, 300,
                                                   os.str().c_str(), "OK", NULL);
    gmw->Show();
}

void
SketchpadWindow::OnEndPaint()
{
    ::glClear(GL_COLOR_BUFFER_BIT);
    mySketchpadData.drawPixels();

    if(hoveringOverPixel) {
        ::glColor3f(1.0f, 1.0f, 0.0f); // yellow = hovering over a pixel
        mySketchpadData.drawOnePixel(hoveringPixel);
    }

    if(dragging) {
        ::glColor3f(1.0f, 1.0f, 0.0f); // yellow = color for dragging
        mySketchpadData.drawSegment(draggingSource, draggingTarget);
        // mySketchpadData.drawOnePixel(draggingSource);
        // mySketchpadData.drawOnePixel(draggingTarget);
    }

    ::glFinish();
}

void
SketchpadWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
{
    float t;
    switch (key) {
    case 'c': case 'C': mySketchpadData.clear(); Refresh(); break;
    case 'q': case 'Q': case Glow::escapeKey: quitProg();
    case 'r': case 'R':
        t = mySketchpadData.getTimeOfRandomLines(numberOfRandomLines);
        showTime(t);
    default: ;
    }
}

void
SketchpadWindow::OnReshape(int width, int height)
{
    // To simplify things, we don't tell mySketchpadData about
    // the new window size. We should then derive SketchpadWindow
    // from GlowFixedSizeWindow, but not all window managers keep
    // the window fixed.

    ::glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;

    setupProjection(viewportWidth, viewportHeight);
}

void
SketchpadWindow::OnMouseDown(Glow::MouseButton /*button*/, int x, int y, Glow::Modifiers /*modifiers*/)
{
    hoveringOverPixel = false;
    if(!dragging) {
        Point_E2<int> temp = unproject(Point_E2<int>(x, y));
        dragging = mySketchpadData.getPixel(temp, draggingSource);
        draggingTarget = draggingSource;
    }
    Refresh();
}

void
SketchpadWindow::OnMouseDrag(int x, int y)
{
    Point_E2<int> temp = unproject(Point_E2<int>(x, y));
    dragging = mySketchpadData.getPixel(temp, draggingTarget);

    Refresh();
}

void
SketchpadWindow::OnMouseUp(Glow::MouseButton /*button*/, int x, int y, Glow::Modifiers /*modifiers*/)
{
    dragging = false;

    Point_E2<int> temp = unproject(Point_E2<int>(x, y));
    bool drawSegment = mySketchpadData.getPixel(temp, draggingTarget);

    if(drawSegment)
        mySketchpadData.setSegment(draggingSource, draggingTarget);

    Refresh();
}

void
SketchpadWindow::OnMouseMotion(int x, int y)
{
    if(!dragging) { // because onMouseMotion is called once on window entry
        Point_E2<int> temp = unproject(Point_E2<int>(x, y));

        hoveringOverPixel = mySketchpadData.getPixel(temp, hoveringPixel);

        Refresh();
    }
}

void
SketchpadWindow::OnMouseExit()
{
    hoveringOverPixel = false;
    Refresh();
}

void
SketchpadWindow::setupProjection(int viewportWidth, int viewportHeight)
{
    ::glMatrixMode(GL_PROJECTION);
    ::glPushMatrix();
    ::glLoadIdentity();
    ::gluOrtho2D(0, viewportWidth, 0, viewportHeight);

    ::glMatrixMode(GL_MODELVIEW);
    ::glPushMatrix();
    ::glLoadIdentity();

    ::glDisable(GL_DEPTH_TEST);
    ::glDisable(GL_LIGHTING);

    ::glEnable(GL_LINE_SMOOTH);
    ::glEnable(GL_POINT_SMOOTH);
    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    ::glClearColor(0.0, 0.0, 0.0, 1.0);
    ::glColor3f(1.0f, 0.0f, 0.0f);
    ::glLineWidth(3.0);
    ::glPointSize(7.0);
}

Point_E2<int>
SketchpadWindow::unproject(const Point_E2<int>& pin)
{
    GLint realy = static_cast<GLint>(viewportHeight - pin.y() - 1);
    int xout = pin.x();
    int yout = realy;
    return Point_E2<int>(xout, yout);
}

