/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "glow.h"
using namespace glow;

class CapomanSubwindow : public GlowSubwindow,
                         public GlowKeyboardFilter
{
public:
    CapomanSubwindow(GlowWindow* parent)
        : GlowSubwindow(parent, 0, 0, 500, 500,
                        Glow::rgbBuffer | Glow::depthBuffer | Glow::doubleBuffer,
                        Glow::keyboardEvents)
    {
        meshList = glGenLists(1);

        glNewList(meshList, GL_COMPILE); {
            glBegin(GL_LINES); {
                for(float x=-15.0f; x<=15.0f; x+=2.0) {
                    glVertex3f(x,-0.6,-15);
                    glVertex3f(x,-0.6, 15);
                }
                for(float z=-15.0f; z<=15.0f; z+=2.0) {
                    glVertex3f(-15,-0.6,z);
                    glVertex3f( 15,-0.6,z);
                }
            } glEnd();
        } glEndList();

        glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);

        setupLighting();
    }

    void setupLighting()
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.998 };
        GLfloat diffuse[] = { 0.3, 1.0, 0.3, 0.998 };
        GLfloat lmodel_ambient[] = { 0.2, 0.4, 0.2, 0.998 };
        GLfloat local_view[] = { 0.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

        GLfloat position[] = { 6, 4, -1, 0.0 };
        glLightfv (GL_LIGHT0, GL_POSITION, position);
    }

protected:
    virtual void OnEndPaint()
    {
        // Set up projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, 1.0, 1.0, 100.0);

        // set up modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 40.0, 20.0,
                  0,0,0, 0,1,0);

        // draw
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_LIGHTING);
        glColor3f(0.7,0.7,0.7);
        glCallList(meshList);

        glEnable(GL_LIGHTING);

        // exercise goes here...
    }

    virtual bool OnFilter(glow::GlowKeyboardData& message)
    {
        switch(message.key)
        {
        case 'a': case 'A': /*handle event*/; Refresh(); return false;
        case 'q': case 'Q': case Glow::escapeKey:
            exit(0);
        default:
            ;
        }
        return true;
    }

    virtual void OnKeyboard(Glow::KeyCode key, int /*x*/, int /*y*/,
                            Glow::Modifiers /*modifiers*/)
    {
        switch (key) {
        case 'q': case 'Q': case Glow::escapeKey:
            exit(0);
        default:
            ;
        }
    }
private:
    GLuint meshList;
};
