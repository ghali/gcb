/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_P3_H
#define VECTOR_P3_H

#include <iostream>
#include <cmath>

#include "misc/determinant.h"

template<typename T>
class Vector_P3;

template<typename T>
ostream& operator<< (ostream& os, const Vector_P3<T>& v);

template<typename T>
istream& operator>> (istream& is, Vector_P3<T>& v);

template<typename T>
class Vector_P3
{
    T _x, _y, _z, _w;
public:
    Vector_P3() : _x(0),_y(0),_z(0),_w(1)  {}

    Vector_P3(const T& x, const T& y, const T& z, const T& w = 1) :_x(x),_y(y),_z(z),_w(w) {}

    T length2() const {
        return (_x*_x + _y*_y + _z*_z) / (_w * _w);
    }

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

    bool operator==(const Vector_P3<T>& v) const {
        return (this == &v) ||
            are_dependent(_x, _y, _z, _w, v._x, v._y, v._z, v._w);
    }

    bool operator!=(const Vector_P3<T>& v) const {
        return ! operator==(v);
    }

    friend ostream& operator<< <>(ostream& os, const Vector_P3<T>& p);

    friend istream& operator>> <>(istream& is, Vector_P3<T>& p);
};

template<typename T>
Vector_P3<T>
operator*(const T& d, const Vector_P3<T>& v)
{
    return Vector_P3<T>(d * v.hx(), d * v.hy(), d * v.hz(), v.hw());
}

template<typename T>
Vector_P3<T>
operator*(const Vector_P3<T>& v, const T & d)
{
    return Vector_P3<T>(v.hx() * d, v.hy() * d, v.hz() * d, v.hw());
}

template<typename T>
Vector_P3<T>
operator+(const Vector_P3<T>& v1, const Vector_P3<T>& v2)
{
    return Vector_P3<T>(v1.hx() * v2.hw() + v2.hx() * v1.hw(),
                        v1.hy() * v2.hw() + v2.hy() * v1.hw(),
                        v1.hz() * v2.hw() + v2.hz() * v1.hw(),
                        v1.hw() * v2.hw());
}

template<typename T>
Point_P3<T>
operator+(const Point_P3<T>& p, const Vector_P3<T>&  v)
{
    return Point_P3<T>(p.hx() * v.hw() + v.hx() * p.hw(),
                       p.hy() * v.hw() + v.hy() * p.hw(),
                       p.hz() * v.hw() + v.hz() * p.hw(),
                       p.hw() * v.hw());
}

template<typename T>
Point_P3<T>
operator-(const Point_P3<T>& p, const Vector_P3<T>&  v)
{
    return Point_P3<T>(p.hx() * v.hw() - v.hx() * p.hw(),
                       p.hy() * v.hw() - v.hy() * p.hw(),
                       p.hz() * v.hw() - v.hz() * p.hw(),
                       p.hw() * v.hw());
}

template<typename T>
Vector_P3<T>
operator-(const Point_P3<T>& p1, const Point_P3<T>& p2)
{
    return Vector_P3<T>(p1.hx() * p2.hw() - p2.hx() * p1.hw(),
                        p1.hy() * p2.hw() - p2.hy() * p1.hw(),
                        p1.hz() * p2.hw() - p2.hz() * p1.hw(),
                        p1.hw() * p2.hw());
}

template<typename T>
ostream& operator<< (ostream& os, const Vector_P3<T>& v)
{
    return os << v._x << " " << v._y << " " << v._z << " " << v._w;
}

template<typename T>
istream& operator>> (istream& is, Vector_P3<T>& v)
{
    return is >> v._x >> v._y >> v._z >> v._w;
}

#endif // VECTOR_P3_H
