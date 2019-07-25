/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_S1_H
#define TRANSFORMATION_S1_H

#include <cmath>
#include <complex>
#include "geometry/E2/direction_e2.h"

//----------------Rotation_S1_Begin----------------
template<typename NT>
class Rotation_S1
{
    std::complex<NT> unitz;
public:
    Rotation_S1() : unitz(1,0) {}
    Rotation_S1(const Direction_E2<NT>& d)
    {
        NT m = std::sqrt(d.x()*d.x() + d.y()*d.y());
        unitz = std::complex<NT>(d.x()/m, d.y()/m);
    }
    Rotation_S1(const NT& rx, const NT& ry)
    {
        NT m = std::sqrt(rx*rx + ry*ry);
        unitz = std::complex<NT>(rx/m, ry/m);
    }

    Point_S1<NT> rotate(const Point_S1<NT>& P) const
    {
        NT x = unitz.real() * P.x() - unitz.imag() * P.y();
        NT y = unitz.imag() * P.x() + unitz.real() * P.y();
        return         Point_S1<NT>(x,y);
    }

    Segment_S1<NT> rotate(const Segment_S1<NT>& seg) const
    {
        return Segment_S1<NT>(rotate(seg.source()), rotate(seg.target()));
    }
//----------------Rotation_S1_End----------------

    Rotation_S1<NT> operator*(const Rotation_S1<NT>& R2) const
    {
        return unitz * R2.unitz;
    }
};

// template specialization for NT=double
template<>
class Rotation_S1<double>
{
    Direction_E2<double> _r;
public:
    // we add one function
    Rotation_S1(double angle)
    {
        double c = std::cos(angle);
        double s = std::sin(angle);
        _r = Direction_E2<double>( c, s);
    }
    // but need to repeat the definition of all others
    void set_to_identity()
    {
        _r = Direction_E2<double>(1,0);
    }
    Rotation_S1(const Direction_E2<double>& r)
        : _r(r) {}
    Rotation_S1(const double& rx, const double& ry)
        : _r(rx, ry) {}

    Point_S1<double> rotate(const Point_S1<double>& P) const
    {
        double x = _r.x() * P.x() - _r.y() * P.y();
        double y = _r.y() * P.x() + _r.x() * P.y();
        return         Point_S1<double>(x,y);
    }

    Segment_S1<double> rotate(const Segment_S1<double>& seg) const
    {
        return Segment_S1<double>(rotate(seg.source()), rotate(seg.target()));
    }

    Rotation_S1<double> operator*(const Rotation_S1<double>& R2) const
    {
        double realpart = _r.x() * R2._r.x() - _r.y() * R2._r.y();
        double imagpart = _r.x() * R2._r.y() + _r.y() * R2._r.x();
        return Rotation_S1<double>(realpart, imagpart);
    }
};

#endif // TRANSFORMATION_S1_H
