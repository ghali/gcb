/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PRECISIONDATA_H
#define PRECISIONDATA_H

#include <vector>
#include <iostream>
using namespace std;

#include "raster_image/array2.h"
#include "geom_types.h"
#include "geometry/E2/predicates_e2.h"

class PrecisionData
{
    friend class PrecisionWindow;
    int resolution;
    Array2<Oriented_side> A;
    bool debug;

public:

    PrecisionData( int _resolution,
                   double precision,
                   const Point_E2d& p1,
                   const Point_E2d& p2,
                   const Point_E2d& p3,
                   bool _debug );
};

#endif // PRECISIONDATA_H
