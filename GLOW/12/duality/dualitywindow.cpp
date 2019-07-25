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
using namespace std;

#include "dualitywindow.h"

// initial values
const int initPixelWidth = 600;
const int initPixelHeight = 600;

// We use single buffering only
DualityWindow::DualityWindow(float foreground, float background) 
    : GlowWindow("Duality",
                 GlowWindow::autoPosition, GlowWindow::autoPosition,
                 initPixelWidth, initPixelHeight,
                 Glow::rgbBuffer, // | Glow::doubleBuffer,
                 Glow::mouseEvents | Glow::dragEvents | Glow::keyboardEvents),
      dragging(false),
      foreground(foreground), background(background)
{
    myDualityData = new DualityData();

    glColor3f(foreground, foreground, foreground);
    glLineWidth(3.0);

    /* GLUquadricObj * */ qobj = gluNewQuadric();
}

DualityWindow::~DualityWindow()
{
    delete myDualityData;
    gluDeleteQuadric(qobj);
}

//----------------------------------------------------------------
void DualityWindow::drawAxis()
{
    glBegin(GL_LINES); {
        glVertex2f(-2.0, 0.0);
        glVertex2f( 2.0, 0.0);

        glVertex2f(0.0, -2.0);
        glVertex2f(0.0,  2.0);
    } glEnd();

    gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
    gluQuadricNormals(qobj, GLU_NONE);

    gluPartialDisk(qobj, 0.0, 1.0, 60, 1, 0.0, 360.0);
}

// Redraw function
//----------------------------------------------------------------
void
DualityWindow::OnEndPaint()
{
    glClearColor(background, background, background, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0,  -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    drawAxis();

    myDualityData->drawScene(foreground, background);

    glFinish();

    checkErrors();
}

void
DualityWindow::unproject(const Point_E2i& pi, Point_E2d& pd)
{
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    GLint realy;  // OpenGL y-coordinate

    glGetIntegerv (GL_VIEWPORT, viewport);
    glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);

    //  note viewport[3] is height of window in pixels
    realy = viewport[3] - (GLint) pi.y() - 1;

    GLdouble x, y;
    GLdouble w;                 // the returned z coord is ignored

    gluUnProject( (GLdouble) pi.x(), (GLdouble) realy, 0.0,
                  mvmatrix, projmatrix, viewport, &x, &y, &w );

    pd = Point_E2d(x, y);
}

void
DualityWindow::OnMouseDown(Glow::MouseButton /*button*/,
                           int x, int y, Glow::Modifiers /*modifiers*/)
{
    // Ignore mousedowns if we're already dragging
    if (!dragging)
    {
        dragging = true;

        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR);

        Point_E2d pd;
        unproject(Point_E2i(x,y), pd);
        
        myDualityData->draw_point_and_dual(pd);
        lastPoint = pd;
    }
}

void
DualityWindow::OnMouseDrag(int x, int y)
{
    myDualityData->draw_point_and_dual(lastPoint);
    Point_E2d pd;
    unproject(Point_E2i(x,y), pd);
    myDualityData->draw_point_and_dual(pd);
    lastPoint = pd;
}

void
DualityWindow::OnMouseUp(Glow::MouseButton /*button*/,
                         int x, int y, Glow::Modifiers /*modifiers*/)
{
    dragging = false;

    myDualityData->draw_point_and_dual(lastPoint);

    glDisable(GL_COLOR_LOGIC_OP);
    Point_E2d pd;
    unproject(Point_E2i(x,y), pd);
    myDualityData->draw_point_and_dual(pd);

    myDualityData->insertPoint(pd);
}

void
DualityWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                          Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'd': case 'D': std::cout << *myDualityData << std::endl; break;
    case 'q': case 'Q': case Glow::escapeKey: Close(); exit(0);
    default:
        ;
    }
}

void
DualityWindow::checkErrors()
{
    int i;
    bool founderror = false;

    while((i = glGetError())) {
        founderror = true;
        std::cerr << "ERROR: " << i << std::endl;
        std::cerr << "       " << gluErrorString(i) << std::endl;
    }
    if(founderror)
        exit(1);
}
