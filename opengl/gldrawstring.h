/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLDRAWSTRING_H
#define GLDRAWSTRING_H

#include <sys/time.h>
#include <string>
#include <sstream>

class GLstringRenderer
{
    void *font; // see 'man glutBitmapCharacter' for fonts to use
    GLfloat x;  // text position in window: range [0,0] (bottom left of window)
    GLfloat y;  // to [1,1] (top right of window).

public:
    GLstringRenderer(void *font, GLfloat x, GLfloat y) : font(font), x(x), y(y) {}

    void draw(std::string str)
    {
        GLboolean wasEnabled_GL_TEXTURE_2D     = glIsEnabled(GL_TEXTURE_2D);
        GLboolean wasEnabled_GL_LIGHTING       = glIsEnabled(GL_LIGHTING);
        GLboolean wasEnabled_GL_COLOR_LOGIC_OP = glIsEnabled(GL_COLOR_LOGIC_OP);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); {
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix(); {
                glLoadIdentity();
                gluOrtho2D(0.0, 1.0, 0.0, 1.0);
                glPushAttrib(GL_COLOR_BUFFER_BIT); { // save current colour

                    glDisable(GL_TEXTURE_2D);
                    glDisable(GL_LIGHTING);

                    glEnable(GL_COLOR_LOGIC_OP);
                    glLogicOp(GL_XOR);

                    glColor3f(1.0,1.0,1.0);
                    glRasterPos3f(x, y, 0.0);
                    for(std::string::iterator ch= str.begin(); ch!=str.end(); ++ch)
                        glutBitmapCharacter(font, static_cast<int>(*ch));
                } glPopAttrib();
            } glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        } glPopMatrix();

        if(wasEnabled_GL_TEXTURE_2D)     glEnable(GL_TEXTURE_2D);     else glDisable(GL_TEXTURE_2D);
        if(wasEnabled_GL_LIGHTING)       glEnable(GL_LIGHTING);       else glDisable(GL_LIGHTING);
        if(wasEnabled_GL_COLOR_LOGIC_OP) glEnable(GL_COLOR_LOGIC_OP); else glDisable(GL_COLOR_LOGIC_OP);
    }
};

#endif // GLDRAWSTRING_H
