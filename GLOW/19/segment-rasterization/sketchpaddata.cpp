/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <cmath>
#include <sys/time.h>

#include "glow.h"
using namespace glow;

#include "misc/random_e2.h"
#include "sketchpaddata.h"

#ifdef GLOW_OPTION_DEBUG
const int SketchpadData::pixelSize       = 30;
const int SketchpadData::pixelSeparation = 5;
#else
const int SketchpadData::pixelSize       = 10;
const int SketchpadData::pixelSeparation = 1;
#endif
const int SketchpadData::pixelIncrement  = SketchpadData::pixelSize + SketchpadData::pixelSeparation;


SketchpadData::SketchpadData(int _viewportWidth, int _viewportHeight)
    : viewportWidth(_viewportWidth), viewportHeight(_viewportHeight)
{
    numXpixels = viewportWidth / (pixelSize + pixelSeparation) + 1;
    numYpixels = viewportHeight / (pixelSize + pixelSeparation) + 1;

    pixels = Array2<bool>(numXpixels, numYpixels, false);
}

void
SketchpadData::clear()
{
    for(int x=0; x<numXpixels; x++)
        for(int y=0; y<numYpixels; y++)
            pixels(x,y) = false;
}

bool
SketchpadData::getPixel(const Point_E2<int>& pin, Point_E2<int>& pout)
{
    int xout = pin.x() / pixelIncrement;
    int yout = pin.y() / pixelIncrement;
    int xremainder = pin.x() % pixelIncrement;
    int yremainder = pin.y() % pixelIncrement;
    pout = Point_E2<int>(xout, yout);

    return (xremainder < pixelSize && yremainder < pixelSize);
}

void
SketchpadData::setPixel(const Point_E2<int>& p)
{
    pixels(p.x(),p.y()) = true;
}

// gettimeofday is only available under linux
float
getClockTime(const timeval& T0)
{
    timeval T1;
    gettimeofday(&T1, NULL);
    return float(T1.tv_sec - T0.tv_sec) + float(T1.tv_usec - T0.tv_usec) / 1000000.0;
}  

float
SketchpadData::getTimeOfRandomLines(int numberOfLines)
{
    timeval T0;
    gettimeofday(&T0, NULL);    // defined in <sys/time.h>
    while(numberOfLines--) {
        Point_E2<int> source, target;
        set_to_random(source);
        set_to_random(target);
        timeSegment(source, target);
    }
    return getClockTime(T0);
}

// inline
void
SketchpadData::drawOnePixel(const Point_E2<int>& p)
{
    ::glBegin(GL_POLYGON); {
        ::glVertex2f(p.x() * pixelIncrement            , p.y() * pixelIncrement            );
        ::glVertex2f(p.x() * pixelIncrement + pixelSize, p.y() * pixelIncrement            );
        ::glVertex2f(p.x() * pixelIncrement + pixelSize, p.y() * pixelIncrement + pixelSize);
        ::glVertex2f(p.x() * pixelIncrement            , p.y() * pixelIncrement + pixelSize);
    } ::glEnd();
}

// inline
void
SketchpadData::drawPixels()
{
    for(int x=0; x<numXpixels; x++)
        for(int y=0; y<numYpixels; y++) {
            if(!pixels(x,y))
                if(!(x%5) || !(y%5))
                    ::glColor3f(0.0f, 0.0f, 1.0f); // blue = pixel 'off'
                else
                    ::glColor3f(0.0f, 0.0f, 0.7f); // blue = pixel 'off'
            else
                ::glColor3f(1.0f, 0.0f, 0.0f); // red  = pixel 'on'
            drawOnePixel(Point_E2<int>(x,y));
        }
}

void
SketchpadData::rasterizeSegment(const Point_E2<int>& sourcePoint, const Point_E2<int>& targetPoint, fp myfp)
{
    Point_E2<int> source = sourcePoint;
    Point_E2<int> target = targetPoint;

    int dx = target.x() - source.x();
    int dy = target.y() - source.y();

    if(!dx && !dy)
        (this->*myfp)(source);
    else if(abs(dx) > abs(dy)) {
        // We now know we are in one of octants 1,4,5,8

        if(dx < 0) {              // if we're in octants 4 or 5
            swap(source, target); // map them to 8 and 1
            dx = -dx;
            dy = -dy;
        }

        // Handle octants 1 and 8
        float dyOverdx = static_cast<float>(dy)/static_cast<float>(dx);

        for(int xi=0; xi<=dx; ++xi) {
            float yt = dyOverdx * static_cast<float>(xi);
            int yi = static_cast<int>(std::floor(yt + 0.5));
            (this->*myfp)(Point_E2<int>(source.x() + xi, source.y() + yi));
        }
    }
    else {
        // We now know we are in one of octants 2,3,6,7

        if(sourcePoint.y() > targetPoint.y()) { // octants 6,7?
            swap(source,target); // map them to 3,2
            dx = -dx;
            dy = -dy;
        }

        // Handle octants 2 and 3
        float dxOverdy = static_cast<float>(dx)/static_cast<float>(dy);

        for(int yi=0; yi<=dy; ++yi) {
            float xt = dxOverdy * static_cast<float>(yi);
            int xi = static_cast<int>(std::floor(xt + 0.5));
            (this->*myfp)(Point_E2<int>(source.x() + xi, source.y() + yi));
        }
    }
}

void
SketchpadData::drawSegment(const Point_E2<int>& source, const Point_E2<int>& target)
{
    rasterizeSegment(source, target, &SketchpadData::drawOnePixel);
}

void
SketchpadData::setSegment(const Point_E2<int>& source, const Point_E2<int>& target)
{
    rasterizeSegment(source, target, &SketchpadData::setPixel);
}

void
SketchpadData::timeSegment(const Point_E2<int>& source, const Point_E2<int>& target)
{
    rasterizeSegment(source, target, &SketchpadData::doNothing);
}
