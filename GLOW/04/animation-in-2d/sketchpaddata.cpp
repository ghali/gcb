// sketchpaddata.C
// $Id: sketchpaddata-question.C,v 1.2 2007/03/03 07:30:50 ghali Exp $

#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
using std::transform;

#include "geometry_types.h"
#include "opengl/gldraw_e2.h"
#include "sketchpaddata.h"

Identity IDENTITY;
Scale SCALE;
Rotation ROTATION;
Translation TRANSLATION;

SketchpadData::SketchpadData()
{
    model.push_back(Point2d(0,0));
    model.push_back(Point2d(4,0));
    model.push_back(Point2d(4,4));
    model.push_back(Point2d(2,6));
    model.push_back(Point2d(0,4));

    resetKeyFrame1();
    resetKeyFrame2();
}

void
SketchpadData::resetKeyFrame1()
{
    Transformation_E2d ATS1(SCALE, scale1);
    Transformation_E2d ATR1(ROTATION, rotate1);
    Transformation_E2d ATT1(TRANSLATION, translate1);

    T1 = ATT1 * ATR1 * ATS1;

    keyframe1 = T1.transform(model);
}

void
SketchpadData::resetKeyFrame2()
{
    Transformation_E2d ATS2(SCALE, scale2);
    Transformation_E2d ATR2(ROTATION, rotate2);
    Transformation_E2d ATT2(TRANSLATION, translate2);

    T2 = ATT2 * ATR2 * ATS2;

    keyframe2 = T2.transform(model);
}

void mydraw(const Point2d& p) {
    GLdraw_E2<double>::draw_point(p);
}

struct LinearInterpolation
{
    // function object
    // ...
};

void
SketchpadData::drawNextFrame()
{
    GLdraw_E2<double>::draw_polygon(model,     GlowColor::red,  GlowColor::red);
    GLdraw_E2<double>::draw_polygon(keyframe1, GlowColor::blue, GlowColor::red);
    GLdraw_E2<double>::draw_polygon(keyframe2, GlowColor::blue, GlowColor::red);
}

void
SketchpadData::setInterpolationMethod(int interpolationMethod)
{
    _interpolationMethod = interpolationMethod;
}

