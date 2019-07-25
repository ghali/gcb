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

#include "precisionwindow.h"

// initial values
const int initPixelWidth = 512;
const int initPixelHeight = 512;

// We use double-buffering, but there is no explicit glSwapBuffers()
// because GLOW swaps the buffers for us.
PrecisionWindow::PrecisionWindow(PrecisionData* data, bool debug) :
    GlowWindow("Precision",
               GlowWindow::autoPosition, GlowWindow::autoPosition,
               initPixelWidth, initPixelHeight,
               Glow::rgbBuffer | Glow::doubleBuffer,
               Glow::keyboardEvents),
    myPrecisionData(data),
    debugMode(debug)
{
    glColor3f(0.0f, 0.0f, 0.0f);
}

//----------------------------------------------------------------
void
PrecisionWindow::drawPrecisionData()
{
    glPointSize(1.0);

    glBegin(GL_POINTS);
    for(int i=0; i<myPrecisionData->resolution; i++)
        for(int j=0; j<myPrecisionData->resolution; j++) {
            switch(myPrecisionData->A(i,j)) {
            case LEFT_TURN:
                glColor3f(0.8f, 0.2f, 0.2f);
                break;
            case RIGHT_TURN:
                glColor3f(0.2f, 0.8f, 0.2f);
                break;
            case COLINEAR:
                glColor3f(0.2f, 0.2f, 0.8f);
                break;
            default:
                break;
            }
            glVertex2f(i,j);
        }
    glEnd();
    glFlush();
}

// Redraw function
//----------------------------------------------------------------
void
PrecisionWindow::OnEndPaint()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, myPrecisionData->resolution,    0, myPrecisionData->resolution);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    drawPrecisionData();
    glFinish();
}

void
PrecisionWindow::OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
{
    switch (key) {
    case 'q':
    case 'Q':
        exit(0);
    case Glow::escapeKey:
        exit(0);  // window should really be scheduled for deletion
    default:
        ;
    }
}
