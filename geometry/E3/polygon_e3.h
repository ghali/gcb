/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POLYGON_E3_H
#define POLYGON_E3_H

#include <vector>
#include "geometry/E3/point_e3.h"
#include "geometry/E3/bbox_e3.h"

template<typename NT>
class Polygon_T3;
template<typename NT>
class Transformation_E3;

template<typename NT>
struct Polygon_E3
{
    std::vector<Point_E3<NT> > vertices;
public:
    typedef NT NumberType;
    typedef Polygon_T3<NT> T3_equivalent;

    friend class Transformation_E3<NT>;

    Polygon_E3() : vertices() {}
    Polygon_E3(int n) : vertices(n) {}
    template<typename iterator>
    Polygon_E3(iterator b, iterator e) : vertices(b,e) {}
    Polygon_E3(const Point_E3<NT> P0,
               const Point_E3<NT> P1,
               const Point_E3<NT> P2,
               const Point_E3<NT> P3)
    {
        vertices.push_back(P0);
        vertices.push_back(P1);
        vertices.push_back(P2);
        vertices.push_back(P3);
    }

    void clear() { vertices.clear(); }
    bool isEmpty() const { return !vertices.size(); }
    unsigned int size() const { return vertices.size(); }
    void push_back(const Point_E3<NT>& p) { vertices.push_back(p); }
    void pop_back() { vertices.pop_back(); }

    typedef typename std::vector<Point_E3<NT> >::const_iterator Point_const_iterator;
    Point_const_iterator begin() const { return vertices.begin(); }
    Point_const_iterator end() const   { return vertices.end(); }

    typedef typename std::vector<Point_E3<NT> >::const_reverse_iterator Point_const_reverse_iterator;
    Point_const_reverse_iterator rbegin() const { return vertices.rbegin(); }
    Point_const_reverse_iterator rend() const   { return vertices.rend(); }

    Point_E3<NT>& operator[](int i) { return vertices[i]; }
    const Point_E3<NT>& operator[](int i) const { return vertices[i]; }

    void update_last_point(const Point_E3<NT>& p)
    {
        vertices[vertices.size()-1] = p;
    }

    Bbox_E3<NT> get_Bbox() const
    {
        // precondition: polygon has at least one vertex
        Bbox_E3<NT> box = vertices[0];
        for(unsigned int i=1; i<vertices.size(); ++i)
            box += vertices[i];
        return box;
    }
};

#endif // POLYGON_E3_H
