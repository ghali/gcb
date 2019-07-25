/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SCENE_H
#define SCENE_H

class Scene : public GlowComponent
{
    GLuint axisList;
public:
    Scene(GlowComponent* parent)
            : GlowComponent(parent)
    {
        axisList = glGenLists(1);
        GLUquadricObj* qobj = gluNewQuadric();
        gluQuadricOrientation(qobj, GLU_OUTSIDE);

        //----------------Axis----------------
        gluQuadricCallback(qobj, GLU_ERROR, NULL /*errorCallback*/);
        gluQuadricNormals(qobj, GLU_SMOOTH);
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricTexture(qobj, GL_TRUE);
        glNewList(axisList, GL_COMPILE); {
            glPushMatrix(); {
                gluCylinder(qobj, 0.02, 0.02, 1.4, 15, 50); // along the +ve z-axis
                glTranslated(0,0,1.35);
                glutSolidCone(0.1, 0.4, 20, 50);
                glRotated(180, 0,1,0);
                glutSolidCone(0.1, 0.0, 20, 20); // close arrow
            } glPopMatrix();
        } glEndList();
    }

    void drawAxis()
    {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        /*x*/glPushMatrix(); {glRotated(90, 0,1,0);glColor3f(1,0,0);glCallList(axisList); }glPopMatrix();
        /*y*/glPushMatrix(); {glRotated(-90, 1,0,0);glColor3f(0,1,0);glCallList(axisList); }glPopMatrix();
        /*z*/glColor3f(0,0,1);glCallList(axisList);
    }

    virtual void OnEndPaint()
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawAxis();
        glColor3f(0,0,0);
        glLineWidth(1.0);
        glutWireSphere(1.0 /*radius*/, 20 /*slices*/, 20 /*stacks*/);
    }
};

#endif // SCENE_H
