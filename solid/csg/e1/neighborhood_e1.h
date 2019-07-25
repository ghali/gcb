/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef NEIGHBORHOOD_E1_H
#define NEIGHBORHOOD_E1_H

#include "../csg_boolean_operation.h"

class Neighborhood_E1
{
    bool left_neighborhood;
    bool right_neighborhood;
public:
    Neighborhood_E1(bool left_neighborhood, bool right_neighborhood)
        : left_neighborhood(left_neighborhood), right_neighborhood(right_neighborhood)
    {}

    bool left()  const { return left_neighborhood;  }
    bool right() const { return right_neighborhood; }

    bool is_empty() const { return !left() && !right(); }

    Neighborhood_E1 eval(const CSG_Boolean_operation& op,
                         const Neighborhood_E1& n2)
    {
        switch(op) {
        case UNION:
            return Neighborhood_E1(left_neighborhood  || n2.left_neighborhood,
                                   right_neighborhood || n2.right_neighborhood);
            break;
        case INTERSECTION:
            return Neighborhood_E1(left_neighborhood  && n2.left_neighborhood,
                                   right_neighborhood && n2.right_neighborhood);
            break;
        default: // case DIFFERENCE:
            return Neighborhood_E1(left_neighborhood  && !n2.left_neighborhood,
                                   right_neighborhood && !n2.right_neighborhood);
            break;
        }
    }
};

#endif // NEIGHBORHOOD_E1_H
