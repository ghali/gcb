/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DRAW_H
#define DRAW_H

#include "geom_types.h"
#include "raster_image/image_color_4.h"
typedef Image<Color_4<GLubyte> > ColorImageGLubyte;

template<typename T>
struct Draw
{
    static void clearColorAndDepth()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void selectWireframe(bool useWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, useWireframe ? GL_LINE : GL_FILL);
    }

    static GLuint
    initTexture(const char * imageFile)
    {    
        ColorImageGLubyte textureImage(imageFile);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GLuint texName;
        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     textureImage.ncols(), textureImage.nrows(),
                     0, GL_RGBA, GL_UNSIGNED_BYTE,
                     textureImage.getData());

        return texName;
    }

    static void setViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void
    calcView(const TankCamera& mytankcamera)
    {
        const Point_E3d& currEye = mytankcamera.getCurrEye();
        const Point_E3d& currCoi = mytankcamera.getCurrCoi();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(currEye.x(),  currEye.y(),  currEye.z(),
                  currCoi.x(),  currCoi.y(),  currCoi.z(),
                  0.0, 1.0, 0.0);
    }

    static void
    initialiseGL(const TankCamera&)
    {
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_SMOOTH);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);

        glMatrixMode(GL_PROJECTION);
        gluPerspective( 40.0, 1.0, 1.0, 1000.0 );

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

        GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1.0};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);

        glLineWidth(2.0);
    }

    static void
    handleLightMotion(double angle)
    {
        GLfloat myLightPosition[] = {50,10,50, 1};

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);

        glPushMatrix(); {

            glRotated(angle, 0.0, 1.0, 0.0);
        
            glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

            glColor3f(1.0,1.0,1.0);
            glTranslatef(50, 10, 50);
            glutSolidSphere(1,8,8);

        } glPopMatrix();
    }

    static void drawAxis()
    {
        // Display axes while debugging.
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);

        const double y=0.01;    // avoid z-fighting with terrain
        glColor3f(0.5,0.5,0.5);
        glutSolidOctahedron();  // origin
        glBegin(GL_LINES); {
            glColor3f(1,0,0);
            glVertex3f(0,y,0); glVertex3f(100,y,0); // x-axis
            glColor3f(0,1,0);
            glVertex3f(0,y,0); glVertex3f(0,100,0); // y-axis
            glColor3f(0,0,1);
            glVertex3f(0,y,0); glVertex3f(0,y,100); // z-axis
        } glEnd();
    }

    static void
    displayMonoliths()
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glDisable(GL_TEXTURE_2D);

        GLfloat monolithsAmbient[] = { 0.3, 0.6, 1.0, 1.0 };
        GLfloat monolithsSpecular[] = { 0.3, 0.6, 1.0, 1.0 };
        GLfloat monolithsDiffuse[] = { 0.3, 0.3, 1.0, 1.0 };
        GLfloat monolithsShininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, monolithsAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, monolithsDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, monolithsSpecular);
        glMaterialfv(GL_FRONT, GL_SHININESS, monolithsShininess);

        for(int i=0; i<=5; i++)
            for(int j=0; j<=5; j++) {

                glPushMatrix(); {
                    glTranslatef(i*20 - 50, 10, j*20 - 50);
                    glScalef(1,20,1);
                    glutSolidSphere(0.5,12,12);
                } glPopMatrix();
            }
        glEnable(GL_TEXTURE_2D);
    }

    // This is a stub. Terrain needs its own object.
    static void
    drawTerrain(GLuint terrainTextureName)
    {
        GLfloat terrainAmbient[] = { 0.8, 1.0, 0.8, 1.0 };
        GLfloat terrainSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat terrainShininess[] = { 2.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, terrainAmbient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, terrainSpecular);
        glMaterialfv(GL_FRONT, GL_SHININESS, terrainShininess);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, terrainTextureName);

        GLfloat xyplane[] = {0,0,0.2,0};
        GLfloat yzplane[] = {0.2,0,0,0};
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        glTexGenfv(GL_S, GL_OBJECT_PLANE, xyplane);
        glTexGenfv(GL_T, GL_OBJECT_PLANE, yzplane);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);


        glNormal3f(0.0, 1.0, 0.0);
        for(double x=-50; x<50; x+=10) {
            glBegin(GL_QUAD_STRIP); {
                for(double z=-50; z<=50; z+=10) {
                    glVertex3d(x+10, 0, z);
                    glVertex3d(x, 0, z);
                }
            } glEnd();
        }
    }

    // This is a stub. Each moving object needs its own object.
    static void
    drawMovingTarget(const Point_E3d& MovingCB, GLuint textureNumber)
    {
        GLfloat targetAmbient[] = { 0.4, 0.2, 0.2, 1.0 };
        GLfloat targetDiffuse[] = { 0.6, 0.3, 0.3, 1.0 };
        GLfloat targetSpecular[] = { 0.6, 0.3, 0.3, 1.0 };
        GLfloat targetShininess[] = { 5.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, targetAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, targetDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, targetSpecular);
        glMaterialfv(GL_FRONT, GL_SHININESS, targetShininess);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D, textureNumber);

        glPushMatrix(); {

            glTranslatef(MovingCB.x(), MovingCB.y(), MovingCB.z());

            glBegin(GL_QUADS); {
                glNormal3f(-1.0, 0.0, 0.0);
                glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0 ,  0.0);
                glTexCoord2f(4.0, 0.0); glVertex3f(0.0, 0.0 , 10.0);
                glTexCoord2f(4.0, 4.0); glVertex3f(0.0, 10.0, 10.0);
                glTexCoord2f(0.0, 4.0); glVertex3f(0.0, 10.0,  0.0);
            } glEnd();
        } glPopMatrix();
    }
};

#endif // DRAW_H
