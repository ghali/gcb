/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RASTERIMAGE_H
#define RASTERIMAGE_H

#include <vector>
#include <iostream>
using namespace std;

#include "raster_image/array2.h"

#include "geom_types.h"

class RasterImage
{
public:
    RasterImage(const Point_E2d& wmin, const Point_E2d& wmax);

    void clear();

    void drawGrid() const;
    void drawOnePixel(const Point_E2i& p);
    void drawPixels();

    void setPixel(const Point_E2i& p, int i = 1);

    void scanConvert(Polygon_E2d& polygon);
private:
    Point_E2d wmin, wmax;
    Point_E2i rmin, rmax;

    int numXpixels;
    int numYpixels;

    Array2<unsigned int> pixels;
};

#endif // RASTERIMAGE_H
