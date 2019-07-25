/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "sketchpaddata.h"

SketchpadData::SketchpadData()
    : simplePolygon()
{
    const Point_E2d topRight    = Point_E2d(512, 384);
    const Point_E2d topLeft     = Point_E2d(128, 384);
    const Point_E2d bottomLeft  = Point_E2d(128,  96);
    const Point_E2d bottomRight = Point_E2d(512,  96);

    top    = Line_E2d(topRight, topLeft);
    left   = Line_E2d(topLeft, bottomLeft);
    bottom = Line_E2d(bottomLeft, bottomRight);
    right  = Line_E2d(bottomRight, topRight);

    clippingPolygon.push_back(topRight   );
    clippingPolygon.push_back(topLeft    );
    clippingPolygon.push_back(bottomLeft );
    clippingPolygon.push_back(bottomRight);
}
