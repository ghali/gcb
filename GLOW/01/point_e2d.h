/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_E2D_H
#define POINT_E2D_H

#include <iostream>

//----------------Point_E2d_Begin----------------
class Point_E2d {
private:
    double _x, _y;
public:
    Point_E2d() : _x(0), _y(0) {}
    Point_E2d(double x, double y) : _x(x), _y(y) {}
//----------------Point_E2d_End----------------

    double x() const { return _x; }
    double y() const { return _y; }

//----------------Point_E2d_equality_operator_Begin----------------
    bool operator==(const Point_E2d& p) const {
        return (this == &p) ||
            (_x == p._x) && (_y == p._y);
    }
//----------------Point_E2d_equality_operator_End----------------

    bool operator!=(const Point_E2d& p) const {
        return ! operator==(p);
    }

//----------------Point_E2d_IO_decl_Begin----------------
    friend std::istream&
    operator>>(std::istream& is, Point_E2d& p);
    friend std::ostream&
    operator<<(std::ostream& os, const Point_E2d& p);
//----------------Point_E2d_IO_decl_End----------------
};

//----------------Point_E2d_IO_impl_Begin----------------
std::istream& operator>> (std::istream& is, Point_E2d& p) {
    is >> p._x >> p._y;
    return is;
}

std::ostream& operator<< (std::ostream& os, const Point_E2d& p) {
    os << p._x << " " << p._y;
    return os;
}
//----------------Point_E2d_IO_impl_End----------------

#endif // POINT_E2D_H
