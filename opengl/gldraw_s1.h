/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLDRAW_S1_H
#define GLDRAW_S1_H

#include <fstream>
#include <cstdlib>
#include <cmath>

#include "glow.h"
#include "glowAux.h"

#include "geometry/S1/point_s1.h"

template<typename NT>
struct GLdraw_S1
{
    GLUquadricObj * qobj;

    GLdraw_S1()
    {
        /* GLUquadricObj * */ qobj = gluNewQuadric();
    }

    ~GLdraw_S1()
    {
        gluDeleteQuadric(qobj);
    }

    void draw(const Point_S1<NT>& P, const glow::GlowColor& c = glow::GlowColor::yellow)
    {
        c.Apply();
        glBegin(GL_POINTS); {
            glVertex2f(P.x(), P.y());
        } glEnd(); 
    }

    void drawAxis(double bound = 1.5)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(3.0);

        glBegin(GL_LINES); {
            glVertex2f(-bound, 0.0);
            glVertex2f( bound, 0.0);

            glVertex2f(0.0, -bound);
            glVertex2f(0.0,  bound);

            glVertex2f(-bound, 1.0);
            glVertex2f( bound, 1.0);
        } glEnd();

        gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
        gluQuadricNormals(qobj, GLU_NONE);

        gluPartialDisk(qobj, 0.0, 1.0, 60, 1, 0.0, 360.0);
    }

    void setupProjectionMatrices(double bound = 1.5)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        gluOrtho2D(-bound, bound,  -bound, bound);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    }
};

#endif // GLDRAW_S1_H
