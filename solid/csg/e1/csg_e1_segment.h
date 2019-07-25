/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CSG_E1_SEGMENT_H
#define CSG_E1_SEGMENT_H

#include <iostream>
using namespace std;

#include "csg_types_e1.h"

#include "misc/orientation.h"
#include "geometry/E1/predicates_e1.h"
#include "../csg_node.h"

class CSG_E1_segment : public CSG_node<Point_E1d, Neighborhood_E1, Transformation_E1d>
{
    Segment_E1d seg;
public:
    CSG_E1_segment(const Segment_E1d& seg)
        : seg(seg)
    {}

    virtual Neighborhood_E1 classify(const Point_E1d& P)
    {
        Oriented_side side_wrt_source = oriented_side(seg.source(), P);
        Oriented_side side_wrt_target = oriented_side(seg.target(), P);

        if(side_wrt_source == ON_NEGATIVE_SIDE || side_wrt_target == ON_POSITIVE_SIDE)
            return Neighborhood_E1(false, false);
        else if(side_wrt_source == ON_POSITIVE_SIDE && side_wrt_target == ON_NEGATIVE_SIDE)
            return Neighborhood_E1(true, true);
        else if(side_wrt_source == ON_ORIENTED_BOUNDARY)
            return Neighborhood_E1(false, true);
        else // (side_wrt_target == ON_ORIENTED_BOUNDARY)
            return Neighborhood_E1(true, false);
    }
};

#endif // CSG_E1_SEGMENT_H
