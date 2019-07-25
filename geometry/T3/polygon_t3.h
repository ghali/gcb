/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POLYGON_T3_H
#define POLYGON_T3_H

#include <vector>
#include <algorithm>
#include <iterator>
#include "geometry/T3/point_t3.h"

template<typename NT>
class Transformation_T3;

template<typename NT>
class /*struct*/ Polygon_T3;

template<typename NT>
std::ostream & operator<< (std::ostream & os, const Polygon_T3<NT> & P);

template<typename NT>
class /*struct*/ Polygon_T3
{
    std::vector<Point_T3<NT> > vertices;
public:
    friend class Transformation_T3<NT>;

    Polygon_T3() : vertices() {}
    Polygon_T3(int n) : vertices(n) {}

    template<typename iterator>
    Polygon_T3(iterator b, iterator e) : vertices(b,e) {}

    void clear() { vertices.clear(); }
    bool is_empty() const { return !vertices.size(); }
    unsigned int size() const { return vertices.size(); }
    void push_back(const Point_T3<NT> & p) { vertices.push_back(p); }
    void pop_back() { vertices.pop_back(); }

    typedef typename std::vector<Point_T3<NT> >::const_iterator Point_const_iterator;
    Point_const_iterator begin() const { return vertices.begin(); }
    Point_const_iterator end() const   { return vertices.end(); }

    typedef typename std::vector<Point_T3<NT> >::const_reverse_iterator Point_const_reverse_iterator;
    Point_const_reverse_iterator rbegin() const { return vertices.rbegin(); }
    Point_const_reverse_iterator rend() const   { return vertices.rend(); }

    Point_T3<NT> & operator[](int i) { return vertices[i]; }
    const Point_T3<NT> & operator[](int i) const { return vertices[i]; }

    void update_last_point(const Point_T3<NT> & p)
    {
        vertices[vertices.size()-1] = p;
    }

    friend std::ostream & operator<< <>(std::ostream & os, const Polygon_T3<NT> & P);
};

template<typename NT>
std::ostream & operator<< (std::ostream & os, const Polygon_T3<NT> & P)
{
    std::copy(P.vertices.begin(), P.vertices.end(),
              std::ostream_iterator<Point_T3<NT> >(os, "    "));
    return os;
}


#endif // POLYGON_T3_H
