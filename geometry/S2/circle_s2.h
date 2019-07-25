/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef CIRCLE_S2_H
#define CIRCLE_S2_H

#include "geometry/E3/direction_e3.h"
#include "geometry/S2/point_s2.h"

#include "geometry/E3/dominant_e3.h"

//----------------Circle_S2_Begin----------------
template<typename NT>
class Circle_S2
{
    NT _x, _y, _z;
public:
    Circle_S2() : _x(1), _y(0), _z(0) {}
    Circle_S2(const NT& x, const NT& y, const NT& z) : _x(x), _y(y), _z(z) {}
//----------------Circle_S2_End----------------
    Circle_S2(const Direction_E3<NT>& D) : _x(D.x()), _y(D.y()), _z(D.z()) {}
    explicit Circle_S2(const Point_S2<NT>& p) : _x(p.x()), _y(p.y()), _z(p.z()) {}

//----------------S2_Circle_from_points_Begin----------------
    Circle_S2(const Point_S2<NT>& p1, const Point_S2<NT>& p2)
    {
        cross_product(
                      p1.x(), p1.y(), p1.z(),
                      p2.x(), p2.y(), p2.z(),
                      _x, _y, _z);
    }
//----------------S2_Circle_from_points_End----------------

#if 0
    Circle_S2(const Segment_S2<NT>& seg)
    {
        cross_product(
                      seg.source().x(), seg.source().y(), seg.source().z(),
                      seg.target().x(), seg.target().y(), seg.target().z(),
                      _x, _y, _z);
    }
#endif

    NT x() const { return _x; }
    NT y() const { return _y; }
    NT z() const { return _z; }

    Direction_E3<NT> get_Direction_E3() const { return Direction_E3<NT>(_x, _y, _z); }
    Point_S2<NT> get_Point_S2() const { return Point_S2<NT>(_x, _y, _z); }

//----------------Circle_S2_base1_Begin----------------
    Point_S2<NT> base1() const {
        Dominant_E3 least_dom = least_dominant(_x, _y, _z);
        Vector_E3<NT> least = get_Vector_E3<NT>(least_dom);

        Vector_E3<NT> b1 = cross_product(least, Vector_E3<NT>(_x,_y,_z));
        return Point_S2<NT>(b1.x(), b1.y(), b1.z());
    }
//----------------Circle_S2_base1_End----------------

//----------------Circle_S2_base2_Begin----------------
    Point_S2<NT> base2() const {
        NT b2x,b2y,b2z;
        Point_S2<NT> b1 = base1();
        cross_product(_x,_y,_z, b1.x(), b1.y(), b1.z(), b2x, b2y, b2z);
        return Point_S2<NT>(b2x, b2y, b2z);
    }
//----------------Circle_S2_base2_End----------------

//----------------S2_incidence_Begin----------------
    bool contains(const Point_S2<NT>& p)
    {
        return (dot_product(_x,_y,_z, p.x(),p.y(),p.z()) == 0);
    }
//----------------S2_incidence_End----------------
};

template<typename NT>
NT
inner_product(const Circle_S2<NT>& c, const Point_S2<NT>& p)
{
    return inner_product(c.x(), c.y(), c.z(),  p.x(), p.y(), p.z());
}

#endif // CIRCLE_S2_H
