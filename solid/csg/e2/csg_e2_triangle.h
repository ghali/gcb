/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CSG_E2_TRIANGLE_H
#define CSG_E2_TRIANGLE_H

#include "csg_types_e2.h"

#include "misc/orientation.h"
#include "geometry/E2/predicates_e2.h"
#include "../csg_node.h"

class CSG_E2_triangle : public CSG_node<Point_E2d, Neighborhood_E2, Transformation_E2d>
{
    Triangle_E2d tri;
public:
    CSG_E2_triangle(const Triangle_E2d& tri)
        : tri(tri)
    {}

    virtual Neighborhood_E2 classify(const Point_E2d& P)
    {
        // ...
        assert(false);
    }
};

#endif // CSG_E2_TRIANGLE_H
