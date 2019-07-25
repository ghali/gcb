/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_E2_H
#define POINT_E2_H

#include <iostream>
using std::ostream;
using std::istream;

template<typename NT>
class Point_E2;
template<typename NT>
class Vector_E2;

template<typename NT>
ostream& operator<< (ostream& os, const Point_E2<NT>& p);

template<typename NT>
istream& operator>> (istream& is, Point_E2<NT>& p);

template<typename NT>
class Point_E2
{
private:
    NT _x, _y;
public:
    typedef NT NumberType;
    typedef NT number_type;
    typedef Point_E2<NT> value_type;

    // Notice that the initialization expressions x() and y() guarantee:
    // 1- that the default constructor for the type NT will be used
    // 2- if the type NT is a primitive type,
    //    the member variable is initialized to zero.
    Point_E2() : _x(), _y()
    {
    }

    Point_E2(const NT& x, const NT& y) : _x(x), _y(y) {}

    NT x() const { return _x; }
    NT y() const { return _y; }

    bool operator==(const Point_E2<NT>& p) const {
        return (this == &p) ||
            (_x == p._x) && (_y == p._y);
    }

    bool operator!=(const Point_E2<NT>& p) const {
        return ! operator==(p);
    }

    Point_E2<NT> operator+=(const Vector_E2<NT> & v);
    Point_E2<NT> operator-=(const Vector_E2<NT> & v);

    friend ostream& operator<< <>(ostream& os, const Point_E2<NT>& p);

    friend istream& operator>> <>(istream& is, Point_E2<NT>& p);
};

template<typename NT>
ostream& operator<< (ostream& os, const Point_E2<NT>& p)
{
    return os << p._x << " " << p._y;
}

template<typename NT>
istream& operator>> (istream& is, Point_E2<NT>& p)
{
    return is >> p._x >> p._y;
}

template<typename NT>
NT
squared_distance(const Point_E2<NT>& P, const Point_E2<NT>& Q)
{
    NT x = P.x() - Q.x();
    NT y = P.y() - Q.y();
    return x*x + y*y;
}

#endif // POINT_E2_H
