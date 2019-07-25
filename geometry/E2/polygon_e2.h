/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POLYGON_E2_H
#define POLYGON_E2_H

#include <vector>
#include <algorithm>
#include <iterator>
#include "geometry/E2/point_e2.h"
#include "geometry/E2/bbox_e2.h"

template<typename NT>
class Transformation_E2;

template<typename NT>
struct Polygon_E2;

template<typename NT>
std::ostream& operator<< (std::ostream& os, const Polygon_E2<NT>& P);

template<typename NT>
struct Polygon_E2
{
    std::vector<Point_E2<NT> > vertices;
public:
    friend class Transformation_E2<NT>;

    Polygon_E2() : vertices() {}
    Polygon_E2(int n) : vertices(n) {}

    template<typename iterator>
    Polygon_E2(iterator b, iterator e) : vertices(b,e) {}

    void clear() { vertices.clear(); }
    bool is_empty() const { return !vertices.size(); }
    unsigned int size() const { return vertices.size(); }
    void push_back(const Point_E2<NT>& p) { vertices.push_back(p); }
    void pop_back() { vertices.pop_back(); }

    typedef typename std::vector<Point_E2<NT> >::const_iterator Point_const_iterator;
    Point_const_iterator begin() const { return vertices.begin(); }
    Point_const_iterator end() const   { return vertices.end(); }

    typedef typename std::vector<Point_E2<NT> >::const_reverse_iterator Point_const_reverse_iterator;
    Point_const_reverse_iterator rbegin() const { return vertices.rbegin(); }
    Point_const_reverse_iterator rend() const   { return vertices.rend(); }

    Point_E2<NT> & operator[](int i) { return vertices[i]; }
    const Point_E2<NT> & operator[](int i) const { return vertices[i]; }

    void update_last_point(const Point_E2<NT>& p)
    {
        vertices[vertices.size()-1] = p;
    }

    Bbox_E2<NT> get_Bbox() const
    {
        // precondition: polygon has at least one vertex
        Bbox_E2<NT> box = vertices[0];
        for(unsigned int i=1; i<vertices.size(); ++i)
            box += vertices[i];
        return box;
    }

    friend std::ostream& operator<< <>(std::ostream& os, const Polygon_E2<NT>& P);
};

template<typename NT>
std::ostream& operator<< (std::ostream& os, const Polygon_E2<NT>& P)
{
    std::copy(P.vertices.begin(), P.vertices.end(),
              std::ostream_iterator<Point_E2<NT> >(os, "    "));
    return os;
}


#endif // POLYGON_E2_H
