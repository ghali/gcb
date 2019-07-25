/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "precisiondata.h"

PrecisionData::PrecisionData( int _resolution,
                              double precision,
                              const Point_E2d& p1,
                              const Point_E2d& p2,
                              const Point_E2d& p3,
                              bool _debug )
    : resolution(_resolution),
      A(resolution,resolution),
      debug(_debug)
{
    for(int x=0; x<resolution; x++)
        for(int y=0; y<resolution; y++) {
            Point_E2d p1offset(1.0 + precision * static_cast<double>(x),
                               1.0 + precision * static_cast<double>(y));
            A(x,y) = oriented_side(p1offset, p2, p3);
        }
}
