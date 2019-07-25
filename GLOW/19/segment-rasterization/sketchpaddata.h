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

#include "raster_image/array2.h"
#include "geometry/E2/point_e2.h"

class SketchpadData
{
public:
    SketchpadData(int viewportWidth, int viewportHeight);

    void clear();

    void drawOnePixel(const Point_E2<int>& p);
    void setPixel(const Point_E2<int>& p);
    void doNothing(const Point_E2<int>& /*p*/) {}

    void drawPixels();

    bool getPixel(const Point_E2<int>& pin, Point_E2<int>& pout);

    float getTimeOfRandomLines(int numberOfLines);

    void drawSegment(const Point_E2<int>& source, const Point_E2<int>& target);
    void setSegment(const Point_E2<int>& source, const Point_E2<int>& target);
    void timeSegment(const Point_E2<int>& source, const Point_E2<int>& target);

private:
    typedef void (SketchpadData::* fp)(const Point_E2<int>& p);
    void rasterizeSegment(const Point_E2<int>& sourcePoint, const Point_E2<int>& targetPoint, fp myfp);

    static const int pixelSize;
    static const int pixelSeparation;
    static const int pixelIncrement; // pixelSize + pixelSeparation

    int viewportWidth;               // "real" pixels
    int viewportHeight;

    int numXpixels;                  // our pixels
    int numYpixels;

    Array2<bool> pixels;

};

#endif // SKETCHPADDATA_H
