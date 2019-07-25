/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_E1_H
#define VECTOR_E1_H

#include "geometry/E1/point_e1.h"

template<typename T>
class Vector_E1;

template<typename T>
ostream & operator<< (ostream & os, const Vector_E1<T> & v);

template<typename T>
istream & operator>> (istream & is, Vector_E1<T> & v);

template<typename T>
class Vector_E1
{
private:
    T _x;
public:
    Vector_E1() : _x() {}
    Vector_E1(const T & x) : _x(x) {}

    T x() const { return _x; }

    void setToRandom() {
        _x = static_cast<T>(drand48());
    }

    bool operator==(const Vector_E1<T> & v) const {
        return (this == &v) ||
            (_x == v.x());
    }

    bool operator!=(const Vector_E1<T> & v) const {
        return ! operator==(v);
    }

    friend ostream & operator<< <>(ostream & os, const Vector_E1<T> & p);

    friend istream & operator>> <>(istream & is, Vector_E1<T> & p);
};

template<typename T>
Vector_E1<T>
operator*(const T & d, const Vector_E1<T> & v)
{
    return Vector_E1<T>(d * v.x());
}

template<typename T>
Vector_E1<T>
operator*(const Vector_E1<T> & v, const T  & d)
{
    return Vector_E1<T>(v.x() * d);
}

template<typename T>
Vector_E1<T>
operator+(const Vector_E1<T> & v1, const Vector_E1<T> & v2)
{
    return Vector_E1<T>(v1.x() + v2.x());
}

template<typename T>
Point_E1<T>
operator+(const Point_E1<T> & p, const Vector_E1<T> &  v)
{
    return Point_E1<T>(p.x()+v.x());
}

template<typename T>
Point_E1<T>
operator-(const Point_E1<T> & p, const Vector_E1<T> &  v)
{
    return Point_E1<T>(p.x()-v.x());
}

template<typename T>
Vector_E1<T>
operator-(const Point_E1<T> & p1, const Point_E1<T> & p2)
{
    return Vector_E1<T>(p1.x()-p2.x());
}

template<typename T>
ostream & operator<< (ostream & os, const Vector_E1<T> & v)
{
    return os << v._x;
}

template<typename T>
istream & operator>> (istream & is, Vector_E1<T> & v)
{
    return is >> v._x;
}

#endif // VECTOR_E1_H
