/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef OFFVIEWDATAVIEWER_H
#define OFFVIEWDATAVIEWER_H

#include <string>
using std::string;

#include "glow.h"
using namespace glow;

class ViewDataViewer : public GlowComponent
{
public:
    ViewDataViewer(GlowComponent* parent, int width, int height);

    void SetSize(int _width, int _height) { width = _width; height = _height; }

    void setFOVandZnear(double _fov, double _znear) { fov = _fov; znear = _znear; }
    void setYawAndPitch(double y, double p) { cameraYaw = y; cameraPitch = p; }

protected:
    void drawAxis();
    void setCamera();
    virtual void OnEndPaint();

private:
    int width, height;
    double fov, znear;
    double cameraYaw, cameraPitch;
};

#endif // OFFVIEWDATAVIEWER_H
