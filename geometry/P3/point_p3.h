/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_P3_H
#define POINT_P3_H

#include <iostream>
using std::ostream;
using std::istream;

#include "misc/determinant.h"
#include "geometry/E3/point_e3.h"

template<typename T>
class Point_P3;

template<typename T>
ostream& operator<< (ostream& os, const Point_P3<T>& p);

template<typename T>
istream& operator>> (istream& is, Point_P3<T>& p);

template<typename T>
class Point_P3
{
private:
    T _x, _y, _z, _w;
public:
    Point_P3() : _x(), _y(), _z(), _w(1)
    {}

    Point_P3(const T& x, const T& y, const T& z, const T& w = 1)
        : _x(x), _y(y), _z(z), _w(w) {}

    Point_P3(const Point_E3<T>& P)
        : _x(P.x()), _y(P.y()), _z(P.z()), _w(1) {}

    T hx() const { return _x; }
    T hy() const { return _y; }
    T hz() const { return _z; }
    T hw() const { return _w; }

    void setToRandom() {
        _x = static_cast<T>(drand48());
        _y = static_cast<T>(drand48());
        _z = static_cast<T>(drand48());
        _w = static_cast<T>(1);
    }

    bool operator==(const Point_P3<T>& p) const {
        return (this == &p) ||
            are_dependent(_x, _y, _z, _w, p._x, p._y, p._z, p._w);
    }

    bool operator!=(const Point_P3<T>& p) const {
        return ! operator==(p);
    }

    friend ostream& operator<< <>(ostream& os, const Point_P3<T>& p);

    friend istream& operator>> <>(istream& is, Point_P3<T>& p);
};

template<typename T>
ostream& operator<< (ostream& os, const Point_P3<T>& p)
{
    return os << p._x << " " << p._y << " " << p._z << " " << p._w;
}

template<typename T>
istream& operator>> (istream& is, Point_P3<T>& p)
{
    return is >> p._x >> p._y >> p._z >> p._w;
}

#endif // POINT_P3_H
