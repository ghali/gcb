/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SKETCHPADDATA_H
#define SKETCHPADDATA_H

#include <vector>
#include <iostream>
using namespace std;

#include "geometry_types.h"

class SketchpadData
{
private:
    Polygon2d model;
    Polygon2d keyframe1;
    Polygon2d keyframe2;

    Vector2d     scale1;
    double      rotate1;
    Vector2d translate1;
    Transformation_E2d T1;

    Vector2d     scale2;
    double      rotate2;
    Vector2d translate2;
    Transformation_E2d T2;

    double _alpha;              // in [0..1]
    int _interpolationMethod;
public:
    SketchpadData();
    void resetKeyFrame1();
    void resetKeyFrame2();

    void drawNextFrame();

    void setInterpolationMethod(int interpolationMethod);
    void setAlpha(double d) { _alpha = d; }

    void setScale1x(double d)     { scale1 = Vector2d(d,scale1.y()); resetKeyFrame1(); }
    void setScale1y(double d)     { scale1 = Vector2d(scale1.x(),d); resetKeyFrame1(); }
    void setRotate1(double d)     { rotate1 = d;        resetKeyFrame1(); }
    void setTranslate1x(double d) { translate1 = Vector2d(d,translate1.y()); resetKeyFrame1(); }
    void setTranslate1y(double d) { translate1 = Vector2d(translate1.x(),d); resetKeyFrame1(); }

    void setScale2x(double d)     { scale2 = Vector2d(d,scale2.y()); resetKeyFrame2(); }
    void setScale2y(double d)     { scale2 = Vector2d(scale2.x(),d); resetKeyFrame2(); }
    void setRotate2(double d)     { rotate2 = d;        resetKeyFrame2(); }
    void setTranslate2x(double d) { translate2 = Vector2d(d,translate2.y()); resetKeyFrame2(); }
    void setTranslate2y(double d) { translate2 = Vector2d(translate2.x(),d); resetKeyFrame2(); }
};

#endif // SKETCHPADDATA_H
