/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CSG_BOOLEAN_H
#define CSG_BOOLEAN_H

#include "csg_node.h"
#include "csg_boolean_operation.h"

template<typename Point, typename Neighborhood, typename Transformation>
class CSG_Boolean : public CSG_node<Point, Neighborhood, Transformation>
{
    CSG_Boolean_operation op;
    CSG_node<Point, Neighborhood, Transformation> * node1;
    CSG_node<Point, Neighborhood, Transformation> * node2;
public:
    CSG_Boolean(const CSG_Boolean_operation& op,
                CSG_node<Point, Neighborhood, Transformation> * node1,
                CSG_node<Point, Neighborhood, Transformation> * node2)
        : op(op), node1(node1), node2(node2)
    {}

    Neighborhood classify(const Point& P)
    {
        Neighborhood n1 = node1->classify(P);

        if( n1.is_empty()
            &&
            (op == INTERSECTION || op == DIFFERENCE) )
            return n1;

        Neighborhood n2 = node2->classify(P);

        return n1.eval(op, n2);
    }
};

#endif // CSG_BOOLEAN_H
