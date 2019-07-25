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
#include <cmath>
using std::cos;
using std::sin;

#include "viewdataviewer.h"

ViewDataViewer::ViewDataViewer(GlowComponent* parent, int width, int height)
    : GlowComponent(parent),
      width(width), height(height)
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.998 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.998 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 0.998 };
    GLfloat local_view[] = { 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    //----------------------------------------------------------------
    setCamera();
    glPushMatrix();

    //----------------------------------------------------------------
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);
}

void
ViewDataViewer::drawAxis()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    /*x*/
    glPushMatrix(); {
        glRotated(90, 0,1,0);
        glColor3f(1,0,0);
        glutSolidTorus(0.025, 2.0, 20, 60);
    } glPopMatrix();
    /*y*/
    glPushMatrix(); {
        glRotated(-90, 1,0,0);
        glColor3f(0,1,0);
        glutSolidTorus(0.025, 2.0, 20, 60);
    } glPopMatrix();
    /*z*/
    glColor3f(0,0,1);
    glutSolidTorus(0.025, 2.0, 20, 60);
    glEnable(GL_LIGHTING);
}

void
ViewDataViewer::setCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( fov, 1.0 /*aspect*/, znear, 100.0 /*Z-far*/ );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,0,
              cos(cameraPitch) * cos(cameraYaw),
              sin(cameraPitch),
              cos(cameraPitch) * sin(cameraYaw),
              0,1,0);
}

void
ViewDataViewer::OnEndPaint()
{
    setCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxis();

    //----------------------------------------------------------------
    // Light
    GLfloat position0[] = { 0, 1, 0, 0.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, position0);

    //----------------------------------------------------------------
    // Render
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.75 };
    // GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 0.75 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 0.75 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 0.75 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.75 };
    // GLfloat no_shininess[] = { 0.0 };
    // GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    // GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color); // no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glPushMatrix(); {

        glRotated(90, 1,0,0);

        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        glutWireSphere(2.0, 48, 20);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

    } glPopMatrix();
}
