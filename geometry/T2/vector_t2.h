/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_T2_H
#define VECTOR_T2_H

#include <iostream>
#include <cmath>

#include "misc/determinant.h"

template<typename NT>
class Vector_T2;

template<typename NT>
ostream& operator<< (ostream& os, const Vector_T2<NT>& v);

template<typename NT>
istream& operator>> (istream& is, Vector_T2<NT>& v);

template<typename NT>
class Vector_T2
{
    NT _x, _y, _w;
public:
    Vector_T2() : _x(0),_y(0),_w(1)  {}

    Vector_T2(const NT& x, const NT& y, const NT& w = 1) :_x(x),_y(y),_w(w) {}

    NT length2() const {
        return (_x*_x + _y*_y) / (_w * _w);
    }

    NT hx() const { return _x; }
    NT hy() const { return _y; }
    NT hw() const { return _w; }

    bool operator==(const Vector_T2<NT>& v) const {
        return (this == &v) ||
            are_dependent( _x, _y, _w, v._x, v._y, v._w )
            && inner_product(_x, _y, _w, v._x, v._y, v._w) > 0;
    }

    bool operator!=(const Vector_T2<NT>& v) const {
        return ! operator==(v);
    }

    friend ostream& operator<< <>(ostream& os, const Vector_T2<NT>& p);

    friend istream& operator>> <>(istream& is, Vector_T2<NT>& p);
};

template<typename NT>
Vector_T2<NT>
operator*(const NT& d, const Vector_T2<NT>& v)
{
    return Vector_T2<NT>(d * v.hx(), d * v.hy(), v.hw());
}

template<typename NT>
Vector_T2<NT>
operator*(const Vector_T2<NT>& v, const NT & d)
{
    return Vector_T2<NT>(v.hx() * d, v.hy() * d, v.hw());
}

template<typename NT>
Vector_T2<NT>
operator+(const Vector_T2<NT>& v1, const Vector_T2<NT>& v2)
{
    return Vector_T2<NT>( v1.hx() * v2.hw() + v2.hx() * v1.hw(),
                          v1.hy() * v2.hw() + v2.hy() * v1.hw(),
                          v1.hw() * v2.hw() );
}

template<typename NT>
Point_T2<NT>
operator+(const Point_T2<NT>& p, const Vector_T2<NT>&  v)
{
    return Point_T2<NT>( p.hx() * v.hw() + v.hx() * p.hw(),
                         p.hy() * v.hw() + v.hy() * p.hw(),
                         p.hw() * v.hw() );
}

template<typename NT>
Point_T2<NT>
operator-(const Point_T2<NT>& p, const Vector_T2<NT>&  v)
{
    return Point_T2<NT>( p.hx() * v.hw() - v.hx() * p.hw(),
                         p.hy() * v.hw() - v.hy() * p.hw(),
                         p.hw() * v.hw() );
}

template<typename NT>
Vector_T2<NT>
operator-(const Point_T2<NT>& p1, const Point_T2<NT>& p2)
{
    return Vector_T2<NT>( p1.hx() * p2.hw() - p2.hx() * p1.hw(),
                          p1.hy() * p2.hw() - p2.hy() * p1.hw(),
                          p1.hw() * p2.hw() );
}

template<typename NT>
ostream& operator<< (ostream& os, const Vector_T2<NT>& v)
{
    return os << v._x << " " << v._y << " " << v._w;
}

template<typename NT>
istream& operator>> (istream& is, Vector_T2<NT>& v)
{
    return is >> v._x >> v._y >> v._w;
}

template<typename NT>
NT
dot_product(const Vector_T2<NT>& v1, const Vector_T2<NT>& v2)
{
    NT num = v1.hx() * v2.hx() + v1.hy() * v2.hy();
    NT denom = v1.hw() * v2.hw();
    return num / denom;
}

#endif // VECTOR_T2_H
