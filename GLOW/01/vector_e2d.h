/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_E2D_H
#define VECTOR_E2D_H

#include "point_e2d.h"

//----------------Vector_E2d_Begin----------------
class Vector_E2d {
private:
    double _x, _y;
public:
    Vector_E2d( ) : _x(0), _y(0) {}
    Vector_E2d( double x, double y ) : _x(x), _y(y) {}
//----------------Vector_E2d_End----------------

    double x() const { return _x; }
    double y() const { return _y; }

    bool operator==(const Vector_E2d& v) const {
        return (this == &v) ||
            (_x == v._x) && (_y == v._y);
    }

    bool operator!=(const Vector_E2d& v) const {
        return ! operator==(v);
    }
};

//----------------Add_Point_Vector_E2d_Begin----------------
Point_E2d operator+(const Point_E2d& p, const Vector_E2d&  v)
{
    return Point_E2d(p.x()+v.x(), p.y()+v.y());
}

Vector_E2d operator-(const Point_E2d& p1, const Point_E2d& p2)
{
    return Vector_E2d(p1.x()-p2.x(), p1.y()-p2.y());
}
//----------------Add_Point_Vector_E2d_End----------------

//----------------Add_Vector_Vector_E2d_Begin----------------
Vector_E2d operator+(const Vector_E2d& v1, const Vector_E2d& v2)
{
    return Vector_E2d(v1.x() + v2.x(), v1.y() + v2.y());
}
//----------------Add_Vector_Vector_E2d_End----------------

//----------------Mul_Scalar_Vector_E2d_Begin----------------
Vector_E2d operator*(double d, const Vector_E2d& v)
{
    return Vector_E2d(d * v.x(), d * v.y());
}

Vector_E2d operator/(const Vector_E2d& v, double d)
{
    return Vector_E2d(v.x() / d, v.y() / d);
}
//----------------Mul_Scalar_Vector_E2d_End----------------

Vector_E2d operator*(const Vector_E2d& v, double d)
{
    return Vector_E2d(v.x() * d, v.y() * d);
}

Vector_E2d operator-(const Vector_E2d& v1, const Vector_E2d& v2)
{
    return Vector_E2d(v1.x() - v2.x(), v1.y() - v2.y());
}

Point_E2d operator-(const Point_E2d& p, const Vector_E2d&  v)
{
    return Point_E2d(p.x()-v.x(), p.y()-v.y());
}

#endif // VECTOR_E2D_H
