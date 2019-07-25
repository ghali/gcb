/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLDRAW_H
#define GLDRAW_H

#include "glow.h"
#include "glowAux.h"

struct GLdraw
{
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
};

#endif // GLDRAW_H
