/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERPOLATION_E1_H
#define INTERPOLATION_E1_H

#include "geometry/E1/point_e1.h"

template<typename NT>
Point_E1<NT>
interpolate(const Point_E1<NT> & P0, const Point_E1<NT> & P1, const NT & t)
{
    return Point_E1<NT>(P0 + (P1-P0) * t);
}

template<typename NT>
Transformation_E1<NT>
interpolate(const Segment_E1<NT> & from, const Segment_E1<NT> & to)
{
    Point_E1<NT> ORIGIN(0);
    Transformation_E1<NT> translate_to_origin(TRANSLATION, Vector_E1<NT>(ORIGIN - from.source()));
    Transformation_E1<NT> scale(SCALE, Vector_E1<NT>( (to.target().x() - to.source().x()) /
                                                      (from.target().x() - from.source().x()) ));
    Transformation_E1<NT> translate_from_origin(TRANSLATION, Vector_E1<NT>(to.source() - ORIGIN));

    Transformation_E1<NT> T = translate_from_origin * scale * translate_to_origin;

    return T;
}

#endif // INTERPOLATION_E1_H
