/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef ORBITSDATAVIEWER_H
#define ORBITSDATAVIEWER_H

#include <string>
using std::string;

#include "glow.h"
using namespace glow;
#include "glowAux.h"

#include "misc/clock.h"
#include "geom_types.h"

#include "opengl/gldraw_s2.h"
#include "opengl/glimagewriter.h"


class OrbitsDataViewer : public GlowComponent
{
public:
    OrbitsDataViewer(GlowComponent* parent)
        : GlowComponent(parent),
          gldraw(),
          lastSeconds(myclock.getSecondsSinceStart()),
          myGLimageWriter()
    {}

    void
    writeImage(const string& filename, int viewportWidth, int viewportHeight)
    {
        myGLimageWriter.writeImage(filename, viewportWidth, viewportHeight);
    }

protected:
    virtual void OnEndPaint()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gldraw.drawAxis();
        glEnable(GL_LIGHTING);

        GLfloat position[] = { 6, 4, -1, 0.0 };
        glLightfv (GL_LIGHT0, GL_POSITION, position);

        animation1();

        gldraw.draw_unit_sphere();
    }

    void
    animation1()
    {
        double s = myclock.getSecondsSinceStart();
        double i = s - 2.0 * M_PI * std::floor(s / 2.0 / M_PI);

        Direction_E3d orthogonalToEarth(0.0,1.0,0.0);
        RotationS2d rotOrthogonalToEarth(i, orthogonalToEarth);

        PointS2d path(orthogonalToEarth);
        gldraw.draw(path);

        PointS2d earth(0,0,1);
        PointS2d rotatingEarth = rotOrthogonalToEarth.rotate(earth);
        gldraw.draw(rotatingEarth,true,false);

        PointS2d moon(0,0.3,1);
        PointS2d rotatingMoon = rotOrthogonalToEarth.rotate(moon);
        gldraw.draw(rotatingMoon,true);
    }

private:
    GLdraw_S2 gldraw;

    Clock myclock;
    float lastSeconds;

    GLimageWriter myGLimageWriter;
};

#endif // ORBITSDATAVIEWER_H
