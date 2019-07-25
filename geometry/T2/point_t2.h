/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_T2_H
#define POINT_T2_H

#include <iostream>
using std::ostream;
using std::istream;

#include "misc/determinant.h"

template<typename NT>
class Point_T2;

template<typename NT>
ostream& operator<< (ostream& os, const Point_T2<NT>& p);

template<typename NT>
istream& operator>> (istream& is, Point_T2<NT>& p);

template<typename NT>
class Point_T2
{
private:
    NT _x, _y, _w;
public:
    typedef NT NumberType;
    typedef Point_T2<NT> value_type;

    Point_T2() : _x(), _y(), _w(1)
    {
    }

    Point_T2(const NT& x, const NT& y, const NT& w = 1) : _x(x), _y(y), _w(w) {}

    NT hx() const { return _x; }
    NT hy() const { return _y; }
    NT hw() const { return _w; }

    bool operator==(const Point_T2<NT>& p) const {
        return (this == &p) ||
            are_dependent( _x, _y, _w, p._x, p._y, p._w )
            && inner_product(_x, _y, _w, p._x, p._y, p._w) > 0;
    }

    bool operator!=(const Point_T2<NT>& p) const {
        return ! operator==(p);
    }

    friend ostream& operator<< <>(ostream& os, const Point_T2<NT>& p);

    friend istream& operator>> <>(istream& is, Point_T2<NT>& p);
};

template<typename NT>
ostream& operator<< (ostream& os, const Point_T2<NT>& p)
{
    return os << p._x << " " << p._y << " " << p._w;
}

template<typename NT>
istream& operator>> (istream& is, Point_T2<NT>& p)
{
    return is >> p._x >> p._y >> p._w;
}

#endif // POINT_T2_H
