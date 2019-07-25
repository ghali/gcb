/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef INTERSECTION_T2_H
#define INTERSECTION_T2_H

#include <cassert>

#include "misc/determinant.h"
#include "geometry/T2/point_t2.h"
#include "geometry/T2/line_t2.h"
#include "geometry/T2/segment_t2.h"
#include "geometry/T2/bbox_t2.h"
#include "geometry/T2/predicates_t2.h"

template<typename NT>
class Point_T2;

template<typename NT>
class Segment_T2;

template<typename NT>
class Line_T2;

template<typename NT>
Point_T2<NT>
intersection(const Line_T2<NT>& l1, const Line_T2<NT>& l2)
{
    NT detx = + determinant(l1.b(), l1.c(), l2.b(), l2.c());
    NT dety = - determinant(l1.a(), l1.c(), l2.a(), l2.c());
    NT detw = + determinant(l1.a(), l1.b(), l2.a(), l2.b());

    return Point_T2<NT>(detx, dety, detw);
}

template<class NT>
bool
positive_half_space_clip(const Line_T2<NT> & splittingLine,
                         Segment_T2<NT> & mySegment)
{
    int sourceSide = oriented_side( splittingLine, mySegment.source() );
    int targetSide = oriented_side( splittingLine, mySegment.target() );

    if(sourceSide != ON_NEGATIVE_SIDE      && targetSide != ON_NEGATIVE_SIDE)
        return true; // no clipping needed: segment is entirely inside

    else if((sourceSide == ON_POSITIVE_SIDE    && targetSide == ON_NEGATIVE_SIDE) ||
            (sourceSide == ON_NEGATIVE_SIDE    && targetSide == ON_POSITIVE_SIDE))
    {
        Point_T2<NT> intersectionPoint = intersection(splittingLine, mySegment.getLine_T2());

        if(sourceSide == ON_POSITIVE_SIDE)
            mySegment = Segment_T2<NT>(mySegment.source(), intersectionPoint);
        else if(targetSide == ON_POSITIVE_SIDE)
            mySegment = Segment_T2<NT>(intersectionPoint, mySegment.target());

        return true;
    }
    else
        return false; // mySegment is ON_NEGATIVE_SIDE, possibly ON_ORIENTED_BOUNDARY
}

template<typename NT>
bool
Brute_Bbox_clipping_of_segment(const Bbox_T2<NT>& B, Segment_T2<NT>& seg)
{
    const Line_T2<NT> E = B.getEastLine();
    const Line_T2<NT> N = B.getNorthLine();
    const Line_T2<NT> W = B.getWestLine();
    const Line_T2<NT> S = B.getSouthLine();

    return ( positive_half_space_clip(E, seg)
             && positive_half_space_clip(N, seg)
             && positive_half_space_clip(W, seg)
             && positive_half_space_clip(S, seg));
}

#endif // INTERSECTION_T2_H
