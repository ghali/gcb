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
#include "geom_types.h"
#include "opengl/gldraw_e2.h"

class SketchpadData
{
    Polygon_E2d simplePolygon;
    Polygon_E2d clippingPolygon;

    Line_E2d top, left, bottom, right;
public:
    SketchpadData();

    void clear() { simplePolygon.clear(); }
    void insertPoint( Point_E2d p) { simplePolygon.push_back(p); }
    void updateLastPoint( Point_E2d p) { simplePolygon.update_last_point(p); }

    void drawPolygon() const
    {
        GLdraw_E2<MyDouble>::draw_polygon(simplePolygon);
    }

    void drawClippingPolygon() const
    {
        GLdraw_E2<MyDouble>::draw_polygon(clippingPolygon, GlowColor::red, GlowColor::red);
    }
};

#endif // SKETCHPADDATA_H
