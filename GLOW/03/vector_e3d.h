/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef VECTOR_E3D_H
#define VECTOR_E3D_H

class Vector_E3d
{
    double _x, _y, _z;
public:
    Vector_E3d(double x=0, double y=0, double z=0) : _x(x), _y(y), _z(z) {}

    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }

    double operator*(const Vector_E3d& v) const {
        return _x * v.x() + _y * v.y() + _z * v.z();
    }
};

double dot_product(const Vector_E3d& v1, const Vector_E3d& v2)
{
    return v1 * v2;
}

Vector_E3d cross_product(const Vector_E3d& v1, const Vector_E3d& v2)
{
    return Vector_E3d(
                      + v1.y() * v2.z() - v1.z() * v2.y(),
                      - v1.x() * v2.z() + v1.z() * v2.x(),
                      + v1.x() * v2.y() - v1.y() * v2.x());
}

Vector_E3d operator-(const Point_E3d& P1, const Point_E3d& P2)
{
    return Vector_E3d(P1.x() - P2.x(), P1.y() - P2.y(), P1.z() - P2.z());
}

#endif // VECTOR_E3D_H
