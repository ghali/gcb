/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_E3D_H
#define LINE_E3D_H

#include "point_E3d.h"

class Line_E3d
{
    Point_E3d source, target;
public:
    Line_E3d( const Point_E3d& _source, const Point_E3d _target )
        : source(_source), target(_target) {}
};

#endif // LINE_E3D_H
