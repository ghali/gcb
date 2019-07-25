/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DIRECTION_E2D_H
#define DIRECTION_E2D_H

#include <cmath>
#include "vector_e2d.h"

//----------------Direction_E2d_Begin----------------
class Direction_E2d {
private:
    double _x, _y;
public:
    Direction_E2d(const Vector_E2d& v)
    {
        double d = std::sqrt( v.x()*v.x() + v.y()*v.y() );
        _x = v.x() / d;
        _y = v.y() / d;
    }
//----------------Direction_E2d_End----------------
};

#endif // DIRECTION_E2D_H
