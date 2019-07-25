/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_E1_H
#define POINT_E1_H

#include <iostream>
using std::ostream;
using std::istream;

template<typename NT>
class Point_E1;

template<typename NT>
ostream & operator<< (ostream & os, const Point_E1<NT> & p);

template<typename NT>
istream & operator>> (istream & is, Point_E1<NT> & p);

template<typename NT>
class Point_E1
{
private:
    NT _x;
public:
    typedef NT NumberType;
    typedef Point_E1<NT> value_type;

    Point_E1(const NT & x=0) : _x(x) {}

    NT x() const { return _x; }

    bool operator==(const Point_E1<NT> & p) const {
        return (this == &p) ||
            (_x == p._x);
    }
    bool operator!=(const Point_E1<NT> & p) const {
        return !operator==(p);
    }

    friend ostream & operator<< <>(ostream & os, const Point_E1<NT> & p);

    friend istream & operator>> <>(istream & is, Point_E1<NT> & p);
};

template<typename NT>
ostream & operator<< (ostream & os, const Point_E1<NT> & p)
{
    return os << p._x;
}

template<typename NT>
istream & operator>> (istream & is, Point_E1<NT> & p)
{
    return is >> p._x;
}

#endif // POINT_E1_H
