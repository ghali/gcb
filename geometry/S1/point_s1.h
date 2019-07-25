/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_S1_H
#define POINT_S1_H

#include <iostream>

#include "geometry/E2/point_e2.h"
#include "geometry/E2/direction_e2.h"

template<typename NT>
class Point_S1;

template<typename NT>
ostream& operator<< (ostream& os, const Point_S1<NT>& p);

//----------------Point_S1_Begin----------------
template<typename NT>
class Point_S1
{
    NT _x, _y;
public:
    Point_S1() : _x(1), _y(0) {}
    Point_S1(const NT& x, const NT& y) : _x(x), _y(y) {}
    Point_S1(const Point_E2<NT>& source, const Point_E2<NT>& target)
        : _x(target.x() - source.x()), _y(target.y() - source.y()) {}
//----------------Point_S1_End----------------
    typedef NT NumberType;
    typedef Point_S1<NT> value_type;

    Direction_E2<NT> get_Direction_E2() const {
        return Direction_E2<NT>(_x,_y);
    }

    const NT x() const { return _x; }
    const NT y() const { return _y; }

//----------------Point_S1_antipode_Begin----------------
    const Point_S1<NT> antipode() const { return Point_S1(-_x, -_y); }
//----------------Point_S1_antipode_End----------------

    Point_S1 operator-() const { return antipode(); }

//----------------Point_S1_Equality_Begin----------------
    bool operator==(const Point_S1<NT>& p) const {
        return (this == &p) ||
            determinant(_x, _y, p._x, p._y) == 0 &&
            inner_product(_x, _y, p._x, p._y) > 0;
    }
//----------------Point_S1_Equality_End----------------

    bool operator!=(const Point_S1<NT>& p) const {
        return !operator==(p);
    }

    friend ostream& operator<< <>(ostream& os, const Point_S1<NT>& p);
};

template<typename NT>
double
angle(const Point_S1<NT>& p)
{
    return atan2(double(p.y()), double(p.x()));
}

template<typename NT>
std::ostream&
operator<<(std::ostream& os, const Point_S1<NT>& p) {
    return os << p._x << " , " << p._y;
}

#endif // POINT_S1_H
