/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CSG_NODE_H
#define CSG_NODE_H

template<typename Point, typename Neighborhood, typename Transformation>
class CSG_node
{
public:
    virtual ~CSG_node() {}
    virtual Neighborhood classify(const Point& P) = 0;
};

#endif // CSG_NODE_H
