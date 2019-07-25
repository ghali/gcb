/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CSG_TRANSFORMATION_H
#define CSG_TRANSFORMATION_H

#include "csg_node.h"

template<typename Point, typename Neighborhood, typename Transformation>
class CSG_transformation : public CSG_node<Point, Neighborhood, Transformation>
{
    Transformation T;
    Transformation inverseT;

    CSG_node<Point, Neighborhood, Transformation> * child;
public:
    CSG_transformation(const Transformation& T,
                       CSG_node<Point, Neighborhood, Transformation> * child)
        : T(T), child(child)
    {
        inverseT = T.inverse();
    }

    virtual Neighborhood classify(const Point& P)
    {
        Point inverseP = inverseT.transform(P);
        return child->classify(inverseP);
    }
};

#endif // CSG_TRANSFORMATION_H
