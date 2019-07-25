/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERSECTION_E1_H
#define INTERSECTION_E1_H

#include <cassert>

#include "misc/determinant.h"
#include "geometry/E1/point_e1.h"
#include "geometry/E1/line_e1.h"
#include "geometry/E1/segment_e1.h"
#include "geometry/E1/bbox_e1.h"
#include "geometry/E1/predicates_e1.h"

template<typename NT>
class Point_E1;

template<typename NT>
class Segment_E1;

template<typename NT>

intersection(const Segment_E1<NT> & s1, const Point_E1<NT> & s2)
{
    // ...
}

template<typename NT>
Point_E1<NT>
intersection(const Segment_E1<NT> & s1, const Segment_E1<NT> & s2)
{
    // ...    
}

#endif // INTERSECTION_E1_H
