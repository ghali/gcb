/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ROTATIONGROUPDATAVIEWER_H
#define ROTATIONGROUPDATAVIEWER_H

#include <string>
using std::string;

#include "glow.h"
using namespace glow;
#include "glowAux.h"

#include "misc/clock.h"
#include "geom_types.h"

#include "opengl/gldraw_s2.h"
#include "opengl/glimagewriter.h"

#include "geometry/S2/interpolation_s2.h"

class RotationGroupDataViewer : public GlowComponent
{
public:
    RotationGroupDataViewer(GlowComponent* parent)
        : GlowComponent(parent),
          gldraw(),
          lastSeconds(myclock.getSecondsSinceStart()),
          currentAnimation(1),
          myGLimageWriter()
    {}

    void
    writeImage(const string& filename, int viewportWidth, int viewportHeight)
    {
        myGLimageWriter.writeImage(filename, viewportWidth, viewportHeight);
    }

    void setAnimation(int i) { currentAnimation = i; }

protected:
    virtual void
    OnEndPaint()
    {
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gldraw.drawAxis();
        ::glEnable(GL_LIGHTING);

        GLfloat position[] = { 6, 4, -1, 0.0 };
        glLightfv (GL_LIGHT0, GL_POSITION, position);

        switch(currentAnimation) {
        case 1: animate1(); break;
        case 2: animate2(); break;
        case 3: animate3(); break;
        default: ;
        }

        gldraw.draw_unit_sphere();
    }

    void
    animate1()
    {
        glLineWidth(2.0);

        // draw moving points
        double s = myclock.getSecondsSinceStart();
        double i = (s - 5 * std::floor(s / 5.0))/5.0; // from 0 to 1 every 5 seconds

        Rotation_S2d R1(1.0, Direction_E3d(1,2,3));
        Rotation_S2d R2(2.0, Direction_E3d(-1,-3,3));

        Rotation_S2d R = slerp(R1, R2, i);

        std::pair<double,Direction_E3d> angleAndAxis = R.getAngleAndAxis();

        glPushMatrix(); {
            glRotated(angleAndAxis.first * 180.0 / M_PI,
                      angleAndAxis.second.x(), angleAndAxis.second.y(), angleAndAxis.second.z());

            // draw(Q,true,true,*cit);

            glutWireSphere(1.1, 20, 10);
        } glPopMatrix();
    }

    void
    animate2()
    {
    }
    void
    animate3()
    {
    }

private:
    GLdraw_S2 gldraw;

    Clock myclock;
    float lastSeconds;

    int currentAnimation;

    GLimageWriter myGLimageWriter;
};

#endif // ROTATIONGROUPDATAVIEWER_H
