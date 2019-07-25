/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERPOLATION_S1_H
#define INTERPOLATION_S1_H

#include <cassert>
#include <cmath>
#include "geometry/S1/point_s1.h"

//----------------S1_interpolation_Begin----------------
template<typename NT>
Point_S1<NT>
interpolate(
            const Point_S1<NT>& P0,
            const Point_S1<NT>& P1,
            const NT& t )
{
    const NT zero(0.0);
    const NT unity(1.0);

    assert(zero <= t && t <= unity);

    NT sourceAngle = atan2(NT(P0.y()), NT(P0.x()));
    NT targetAngle = atan2(NT(P1.y()), NT(P1.x()));

    if(targetAngle > sourceAngle) {
        NT angle = sourceAngle * (unity-t) + targetAngle * (t);
        return Point_S1<NT>(cos(angle), sin(angle));
    }
    else {
        NT angle =
            (NT(M_PI) + sourceAngle) * (unity-t)
            + (targetAngle + NT(M_PI)) * (t);
        return Point_S1<NT>(-cos(angle), -sin(angle));
    }
}
//----------------S1_interpolation_End----------------

#endif // INTERPOLATION_S1_H
