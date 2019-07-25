/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLVERTEXDEMOWINDOW_H
#define GLVERTEXDEMOWINDOW_H

#include <iostream>
using std::cerr;
using std::endl;

#include "glow.h"
using namespace glow;

const int initViewportWidth  = 644;
const int initViewportHeight = 484;

class GLvertexDemoWindow : public GlowWindow
{
public:
    GLvertexDemoWindow()
        : GlowWindow("glGetError Demo Window",
                     GlowWindow::autoPosition, GlowWindow::autoPosition,
                     initViewportWidth, initViewportHeight,
                     Glow::rgbBuffer | Glow::doubleBuffer,
                     Glow::noEvents)
    {}

protected:
    virtual void OnEndPaint()
    {
        glBegin(GL_FLOAT); {    // nonsense
            ;
        } glEnd();

        checkErrors();
    }

//----------------checkErrors_Begin----------------
    static void checkErrors()
    {
        GLenum errorCode = 0;
        bool errorFound = false;
        while((errorCode = glGetError()) != GL_NO_ERROR) {
            errorFound = true;
            cerr << "ERROR: "
                 << errorCode << endl;
            cerr << "       "
                 << gluErrorString(errorCode) << endl;
        }
        if(errorFound)
            exit(1);
    }
//----------------checkErrors_End----------------
};

#endif // GLVERTEXDEMOWINDOW_H
