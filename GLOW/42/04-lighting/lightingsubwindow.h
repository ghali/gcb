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

// Mesh
const double sizeOfMesh = 50.0;
const double blockOfMesh = 2.0;

// Light Positions
GLfloat movingLP[] = { 30.0, 10.0, 0.0, 1.0 };
GLfloat staticLP[] = { 35.0, 10.0, -35.0, 1.0 };


class LightingSubwindow : public GlowSubwindow
{
public:
    LightingSubwindow(GlowWindow* parent)
        : GlowSubwindow(parent, 0, 0, 500, 500,
                        Glow::rgbBuffer | Glow::depthBuffer | Glow::doubleBuffer,
                        Glow::keyboardEvents),
          lightAngle(0), viewerAngle(0)
    {
        meshList = glGenLists(1);

        glNewList(meshList, GL_COMPILE); {
            glNormal3f(0.0, 1.0, 0.0);
            for(double x=-sizeOfMesh; x<sizeOfMesh; x+=blockOfMesh) {
                glBegin(GL_QUAD_STRIP); {
                    for(double z=-sizeOfMesh; z<=sizeOfMesh; z+=blockOfMesh) {
                        glVertex3d(x+blockOfMesh, 0, z);
                        glVertex3d(x, 0, z);
                    }
                } glEnd();
            }
        } glEndList();

        // glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);

        setProjectionMatrix();
        setModelViewMatrix(viewerAngle);

        setMovingLight();
        setStaticLight();
        setHeadLight();

        GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // default
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

        saveLights(true, true, true);
    }

    // Red, LIGHT0
    void setMovingLight()
    {
        GLfloat ambient[] = { 0.2, 0.0, 0.0, 1.0 };
        GLfloat diffuse[] = { 0.6, 0.3, 0.3, 1.0 };
        GLfloat specular[] = { 0.7, 0.3, 0.3, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }

    // Green, LIGHT1
    void setStaticLight()
    {
        GLfloat ambient[] = { 0.0, 0.2, 0.0, 1.0 };
        GLfloat diffuse[] = { 0.3, 0.6, 0.3, 1.0 };
        GLfloat specular[] = { 0.3, 0.7, 0.3, 1.0 };

        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

        glLightfv(GL_LIGHT1, GL_POSITION, staticLP);
    }

    // Blue, LIGHT2
    void setHeadLight()
    {
        GLfloat ambient[] = { 0.0, 0.0, 0.3, 1.0 };
        GLfloat diffuse[] = { 0.4, 0.4, 0.75, 1.0 };
        GLfloat specular[] = { 0.3, 0.3, 0.7, 1.0 };

        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular);

//----------------headlight_excerpt_Begin----------------
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT2, GL_POSITION, position);
//----------------headlight_excerpt_End----------------

        GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 96);
    }

    void setAngles(double la, double va)
    {
        lightAngle = la; viewerAngle = va;
        Refresh();
    }

    void setProjectionMatrix()
    {
        // Set up projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0 /*fov*/, 1.0 /*aspect*/,
                       1.0/*Znear*/, 1000.0/*Zfar*/);
    }
    void setModelViewMatrix(double a)
    {
        // set up modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(70.0 * std::sin(a * M_PI/180.0), 50.0, 70.0 * std::cos(a * M_PI/180.0),
                  0,0,0, 0,1,0);
    }

    void saveLights(bool _movingLightIsOn, bool _staticLightIsOn, bool _headLightIsOn)
    {
        movingLightIsOn = _movingLightIsOn;
        staticLightIsOn = _staticLightIsOn;
        headLightIsOn = _headLightIsOn;
        Refresh();
    }
    void setLights()
    {
        if (movingLightIsOn)
            glEnable(GL_LIGHT0);
        else
            glDisable(GL_LIGHT0);

        if (staticLightIsOn)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);

        if (headLightIsOn)
            glEnable(GL_LIGHT2);
        else
            glDisable(GL_LIGHT2);
    }
protected:

    virtual void OnEndPaint()
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setProjectionMatrix();

        setModelViewMatrix(0.0);

        // draw static light
        if (staticLightIsOn)
        {
            glPushMatrix(); {
                glDisable(GL_LIGHTING);
                glColor3f(0.0, 0.7, 0.0);

                glTranslated(staticLP[0], staticLP[1], staticLP[2]);
                glutSolidSphere(1.0,8,8);
            } glPopMatrix();
        }

        setModelViewMatrix(viewerAngle);

        // Set up and draw moving light
//----------------movingLightIsOn_Begin----------------
        if (movingLightIsOn)
        {
            glPushMatrix (); {
                glRotated(lightAngle, 0.0, 1.0, 0.0);
                GLfloat position[] = { 30.0, 10.0, 0.0, 1.0 };
                glLightfv(GL_LIGHT0, GL_POSITION, position);

                glDisable(GL_LIGHTING);
                glColor3f(1.0, 0.0, 0.0);

                glTranslated(movingLP[0],movingLP[1],movingLP[2]);
                glutSolidSphere(1.0,8,8);
            } glPopMatrix ();
        }
//----------------movingLightIsOn_End----------------

        // Set material and draw mesh
        GLfloat ambient_material[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat diffuse_material[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat specular_material[] = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat emission_material[] = { 0.0, 0.0, 0.0, 1.0 };

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_material);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_material);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
        glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);

        glEnable(GL_LIGHTING);
        setLights();
        glCallList(meshList);
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

    double lightAngle, viewerAngle, angle3;

    bool movingLightIsOn;
    bool staticLightIsOn;
    bool headLightIsOn;
};
