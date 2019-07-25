/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_P2_H
#define POINT_P2_H

#include <iostream>
using std::ostream;
using std::istream;

#include "misc/determinant.h"

template<typename T>
class Point_P2;

template<typename T>
ostream& operator<< (ostream& os, const Point_P2<T>& p);

template<typename T>
istream& operator>> (istream& is, Point_P2<T>& p);

template<typename T>
class Point_P2
{
private:
    T _x;
    T _y;
    T _w;
public:
    Point_P2() : _x(), _y(), _w(1)
    {
    }

    Point_P2(const T& x, const T& y, const T& w = 1) : _x(x), _y(y), _w(w) {}

    T hx() const { return _x; }
    T hy() const { return _y; }
    T hw() const { return _w; }

    void setToRandom() {
        _x = static_cast<T>(drand48());
        _y = static_cast<T>(drand48());
        _w = static_cast<T>(1);
    }

    bool operator==(const Point_P2<T>& p) const {
        return (this == &p) ||
            are_dependent(_x, _y, _w, p._x, p._y, p._w);
    }

    bool operator!=(const Point_P2<T>& p) const {
        return ! operator==(p);
    }

    friend ostream& operator<< <>(ostream& os, const Point_P2<T>& p);

    friend istream& operator>> <>(istream& is, Point_P2<T>& p);
};

template<typename T>
ostream& operator<< (ostream& os, const Point_P2<T>& p)
{
    return os << p._x << " " << p._y << " " << p._w;
}

template<typename T>
istream& operator>> (istream& is, Point_P2<T>& p)
{
    return is >> p._x >> p._y >> p._w;
}

#endif // POINT_P2_H
