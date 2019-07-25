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

class MatricesSubwindow : public GlowSubwindow
{
private:
    GLuint meshList;
    
    double angle1, angle2, angle3;

    double fovAngle;
    double viewerxyz;
public:
    MatricesSubwindow(GlowWindow* parent)
        : GlowSubwindow(parent, 0, 0, 500, 500,
                        Glow::rgbBuffer | Glow::depthBuffer | Glow::doubleBuffer,
                        Glow::keyboardEvents),
          angle1(0), angle2(0), angle3(0),
          fovAngle(40.0), viewerxyz(20.0)
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

    void setAngles(double x, double y, double z)
    {
        angle1 = x; angle2 = y; angle3 = z;
        Refresh();
    }

    void setCamera(double fov, double location)
    {
        fovAngle = fov;
        viewerxyz = location;

        Refresh();
    }

protected:
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

//----------------OnEndPaint_1_Begin----------------
virtual void OnEndPaint()
{
    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
                   fovAngle,
                   1.0 /*aspect*/,
                   1.0 /*Znear*/,
                   1000.0 /*Zfar*/);

    // set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              viewerxyz/1.5,
              viewerxyz,
              viewerxyz*1.4,
              0,0,0, 0,1,0);

    // draw
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glColor3f(0.7,0.7,0.7);
    glCallList(meshList);

    glEnable(GL_LIGHTING);
//----------------OnEndPaint_1_End----------------

//----------------OnEndPaint_2_Begin----------------
    glPushMatrix(); {
        glRotated(angle1, 0,1,0);

        glPushMatrix(); {
            glScaled(5,0.5,0.5);
            glTranslated(0.5,0,0);
            glutSolidCube(1.0);
        } glPopMatrix();

        glTranslated(5,0,0);
        glRotated(angle2, 0,0,1);

        glPushMatrix(); {
            glScaled(5,0.5,0.5);
            glTranslated(0.5,0,0);
            glutSolidCube(1.0);
        } glPopMatrix();

        glTranslated(5,0,0);
        glRotated(angle3, 0,0,1);

        glPushMatrix(); {
            glScaled(5,0.5,0.5);
            glTranslated(0.5,0,0);
            glutSolidCube(1.0);
        } glPopMatrix();

    } glPopMatrix();
}
//----------------OnEndPaint_2_End----------------
};
