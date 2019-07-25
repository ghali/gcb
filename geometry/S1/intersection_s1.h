/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERSECTION_S1_H
#define INTERSECTION_S1_H

#include <bits/stl_pair.h>

#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"

//----------------S1_intersection_Begin----------------
template<typename NT>
std::pair<bool,Segment_S1<NT> >
intersection(
             const Segment_S1<NT>& seg1,
             const Segment_S1<NT>& seg2)
{
    if(seg1.contains(seg2.source()) && seg1.contains(seg2.target()))
        return std::make_pair(true, seg2);
    else if(seg2.contains(seg1.source()) && seg2.contains(seg1.target()))
        return std::make_pair(true, seg1);
    else if(seg1.contains(seg2.source()) && seg2.contains(seg1.target()))
        return std::make_pair(
            true, Segment_S1<NT>(seg2.source(), seg1.target()));
    else if(seg2.contains(seg1.source()) && seg1.contains(seg2.target()))
        return std::make_pair(
            true, Segment_S1<NT>(seg1.source(), seg2.target()));
    else
        return std::make_pair(false, Segment_S1<NT>());
}
//----------------S1_intersection_End----------------

#endif // INTERSECTION_S1_H
