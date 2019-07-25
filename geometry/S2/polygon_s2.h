#ifndef POLYGON_S2_H
#define POLYGON_S2_H

#include <vector>
#include <algorithm>
#include <iterator>
#include "geometry/S2/point_s2.h"

template<typename NT>
struct Polygon_S2;
template<typename NT>
class Transformation_S2;
template<typename NT>
std::ostream & operator<< (std::ostream & os, const Polygon_S2<NT> & P);

template<typename NT>
struct Polygon_S2
{
    std::vector<Point_S2<NT> > vertices;
public:
    friend class Transformation_S2<NT>;

    Polygon_S2() : vertices() {}
    Polygon_S2(int n) : vertices(n) {}

    template<typename iterator>
    Polygon_S2(iterator b, iterator e) : vertices(b,e) {}

    void clear() { vertices.clear(); }
    bool is_empty() const { return !vertices.size(); }
    unsigned int size() const { return vertices.size(); }
    void push_back(const Point_S2<NT> & p) { vertices.push_back(p); }
    void pop_back() { vertices.pop_back(); }

    typedef typename std::vector<Point_S2<NT> >::const_iterator Point_const_iterator;
    Point_const_iterator begin() const { return vertices.begin(); }
    Point_const_iterator end() const   { return vertices.end(); }

    typedef typename std::vector<Point_S2<NT> >::const_reverse_iterator Point_const_reverse_iterator;
    Point_const_reverse_iterator rbegin() const { return vertices.rbegin(); }
    Point_const_reverse_iterator rend() const   { return vertices.rend(); }

    Point_S2<NT> & operator[](int i) { return vertices[i]; }
    const Point_S2<NT> & operator[](int i) const { return vertices[i]; }

    void update_last_point(const Point_S2<NT> & p)
    {
        vertices[vertices.size()-1] = p;
    }

    friend std::ostream & operator<< <>(std::ostream & os, const Polygon_S2<NT> & P);
};

template<typename NT>
std::ostream & operator<< (std::ostream & os, const Polygon_S2<NT> & P)
{
    std::ostream_iterator<Point_S2<NT> > output(os, "    ");
    std::copy(P.vertices.begin(), P.vertices.end(), output);
    return os;
}

#endif // POLYGON_S2_H
