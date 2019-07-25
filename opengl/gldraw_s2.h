/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLDRAW_S2_H
#define GLDRAW_S2_H

#include <fstream>
#include <cstdlib>
#include <cmath>

#include "glow.h"
#include "glowAux.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/circle_s2.h"

typedef double MyDouble;
typedef Point_S2<MyDouble> PointS2d;
typedef Circle_S2<MyDouble> CircleS2d;

struct GLdraw_S2
{
    GLuint axisList;
    GLuint cylinderForVectorList;
    GLuint thinCylinderForVectorList;

    GLdraw_S2()
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
        // initialize Camera
        glMatrixMode(GL_PROJECTION);
        gluPerspective( 20.0 /*fov*/, 1.0 /*aspect*/, 1.0 /*Z-near*/, 100.0 /*Z-far*/ );
        glMatrixMode(GL_MODELVIEW);
        gluLookAt(8,4,4,   0,0,0,   0,1,0);

        glPushMatrix();

        //----------------------------------------------------------------
        // initialize quadric
        GLUquadricObj *qobj;

        axisList = glGenLists(1);
        qobj = gluNewQuadric();
        gluQuadricCallback(qobj, GLU_ERROR, NULL /*errorCallback*/);

        gluQuadricNormals(qobj, GLU_SMOOTH);
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluQuadricNormals(qobj, GLU_FLAT);

        glNewList(axisList, GL_COMPILE); {
            glPushMatrix(); {
                gluCylinder(qobj, 0.02, 0.02, 1.4, 15, 50); // along the +ve z-axis
                glTranslated(0,0,1.35);
                glutSolidCone(0.1, 0.4, 20, 50);
                glRotated(180, 0,1,0);
                glutSolidCone(0.1, 0.001, 20, 20); // base of cone
            } glPopMatrix();
        } glEndList();

        cylinderForVectorList = glGenLists(1);

        glNewList(cylinderForVectorList, GL_COMPILE); {
            gluCylinder(qobj, 0.07, 0.07, 0.95, 15, 50); // along the +ve z-axis
        } glEndList();

        thinCylinderForVectorList = glGenLists(1);

        glNewList(thinCylinderForVectorList, GL_COMPILE); {
            gluCylinder(qobj, 0.03, 0.03, 1.0, 15, 50); // along the +ve z-axis
        } glEndList();

        //----------------------------------------------------------------
        // other initializations
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glClearColor(1,1,1,1);
        glCullFace(GL_FRONT);
    }

    static void
    switchToTransparent()
    {
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    }

    static void
    unswitchFromTransparent()
    {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }

    static void
    errorCallback()
    {
        std::exit(0);
    }

    void
    drawAxis()
    {
        const float tone1 = 0.6;
        const float tone2 = 0.2;

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        /*x*/ glPushMatrix(); { glRotated(90, 0,1,0); glColor3f(tone2,tone2,tone1); glCallList(axisList); } glPopMatrix();
        /*y*/ glPushMatrix(); { glRotated(-90, 1,0,0); glColor3f(tone2,tone2,tone1); glCallList(axisList); } glPopMatrix();
        /*z*/ glColor3f(tone2,tone2,tone1); glCallList(axisList);
    }

    void draw(const PointS2d& sp,
              bool headOnly = false,
              bool thin = true,
              const glow::GlowColor& color = glow::GlowColor::yellow)
    {
        GLfloat colorArray[] = {static_cast<float>(color[0])/255.0f,
                                static_cast<float>(color[1])/255.0f,
                                static_cast<float>(color[2])/255.0f,
                                static_cast<float>(color[3])/255.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorArray);

        glPushMatrix(); {
            double Zangle = sp.getZangle();
            double Xangle = sp.getXangle();

            glRotated(-Zangle, 0,0,1);
            glRotated(-Xangle, 1,0,0);

            // representative spherical point
            glPushMatrix(); {
                glTranslated(0,0,1);
                glutSolidSphere(thin ? 0.07 : 0.1, 28, 10);
            } glPopMatrix();

            if(!headOnly) {
                // representative cylinder for vector of spherical point
                glPushMatrix(); {
                    if(thin)
                        glCallList(thinCylinderForVectorList);
                    else
                        glCallList(cylinderForVectorList);
                } glPopMatrix();

                // cone to complete above vector:
                glPushMatrix(); {
                    glTranslated(0,0,0.65);
                    glutSolidCone(thin ? 0.10 : 0.2, 0.4, 20, 50);
                    glRotated(180, 0,1,0);
                    glutSolidCone(thin ? 0.10 : 0.2, 0.001, 20, 20);
                } glPopMatrix();
            }
        } glPopMatrix();
    }

    void
    draw_spherical_circle(const CircleS2d& sp, double innerRadius = 0.01)
    {
        GLfloat torusColor[] = {1.1, 1.0, 0.1, 1.0};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, torusColor);

        glPushMatrix(); {

            double Zangle = sp.get_Point_S2().getZangle();
            double Xangle = sp.get_Point_S2().getXangle();

            glRotated(-Zangle, 0,0,1);
            glRotated(-Xangle, 1,0,0);

            glutSolidTorus(innerRadius, 1.0, 20, 70);
        } glPopMatrix();
    }

    void
    draw_unit_sphere()
    {

        GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.75 };
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

        switchToTransparent();
        glutSolidSphere(1.0, 50, 20);
        unswitchFromTransparent();
    }

    void
    drawTriangle(const vector<PointS2d>& rP, int i, int j, int k, glow::GlowColor c)
    {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        c.Apply();
        glBegin(GL_TRIANGLES); {
            glVertex3d(rP[i].x(), rP[i].y(), rP[i].z());
            glVertex3d(rP[j].x(), rP[j].y(), rP[j].z());
            glVertex3d(rP[k].x(), rP[k].y(), rP[k].z());
        } glEnd();        
    }
};

#endif // GLDRAW_S2_H
