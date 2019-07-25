/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "glow.h"
using namespace glow;

#include "./rasterimage.h"
#include "opengl/gldraw_e2.h"
#include "geometry/E2/predicates_e2.h"

GlowColor axisColor(0,0,0.8);
GlowColor mainAxisColor(0,0.8,0.6);

RasterImage::RasterImage(const Point_E2d& wmin, const Point_E2d& wmax)
    : wmin(wmin), wmax(wmax)
{
    rmin = Point_E2i(int(wmin.x())  , int(wmin.y())  );
    rmax = Point_E2i(int(wmax.x())+1, int(wmax.y())+1);

    numXpixels = rmax.x() - rmin.x() + 1;
    numYpixels = rmax.y() - rmin.y() + 1;

    pixels = Array2<unsigned int>(numXpixels, numYpixels, false);
    pixels.init(0);

    clear();
}

void
RasterImage::clear()
{
    for(int x=0; x<numXpixels; x++)
        for(int y=0; y<numYpixels; y++)
            pixels(x,y) = 0;
}

void
RasterImage::drawGrid() const
{
    for(int x=rmin.x(); x<rmax.x(); ++x)
        GLdraw_E2<double>::draw_segment(Point_E2d(double(x),wmin.y()),
                                        Point_E2d(double(x),wmax.y()),
                                        x ? axisColor : mainAxisColor,
                                        3.0, false);

    for(int y=rmin.y(); y<rmax.y(); ++y)
        GLdraw_E2<double>::draw_segment(Point_E2d(wmin.x(),double(y)),
                                        Point_E2d(wmax.x(),double(y)),
                                        y ? axisColor : mainAxisColor,
                                        3.0, false);
}

void
RasterImage::drawOnePixel(const Point_E2i& p)
{
    const int v = pixels(p.x(),p.y());
    float gb = 0.5f * float(v-1);
    GLdraw_E2<double>::draw_point(Point_E2d(rmin.x()+p.x(), rmin.y()+p.y()),
                                  v ? GlowColor(1.0f, gb, gb) : GlowColor::blue,
                                  15.0);
}

void
RasterImage::drawPixels()
{
    for(int x=0; x<numXpixels; x++)
        for(int y=0; y<numYpixels; y++)
            drawOnePixel(Point_E2i(x,y));
}

void
RasterImage::setPixel(const Point_E2i& p, int i)
{
    pixels(-rmin.x()+p.x(),-rmin.y()+p.y()) += i;
}

void
RasterImage::scanConvert(Polygon_E2d& polygon)
{
    if(polygon.is_empty())
        return;
    Bbox_E2d box = polygon.get_Bbox();
    Point_E2d wmin = box.LL();
    Point_E2d wmax = box.UR();

    Point_E2i imin(int(wmin.x()    ), int(wmin.y()    ));
    Point_E2i imax(int(wmax.x()+1.0), int(wmax.y()+1.0));

    for(int x=imin.x(); x<=imax.x(); ++x)
        for(int y=imin.y(); y<=imax.y(); ++y)
            setPixel(Point_E2i(x,y), is_inside(polygon, Point_E2d(double(x),double(y))));
}
