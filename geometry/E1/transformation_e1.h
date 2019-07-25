/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_E1_H
#define TRANSFORMATION_E1_H

#include <cassert>
#include <cmath>
#include <stdexcept>
using std::cos;
using std::sin;

#include "geometry/E1/point_e1.h"
#include "geometry/E1/segment_e1.h"
#include "geometry/E1/vector_e1.h"

#include "geometry/lib/transformations.h"

extern Identity IDENTITY;
extern Scale SCALE;
extern Translation TRANSLATION;

template<typename NT>
class Transformation_E1
{
protected:
    NT m00, m01;

    // m10 = 0 , m11 = 1
    void setToIdentity();
public:    
    Transformation_E1();
    Transformation_E1(const Identity);
    Transformation_E1(const Scale, const Vector_E1<NT> & v);
    Transformation_E1(const Translation, const Vector_E1<NT> & v);

    Transformation_E1(const NT & m00, const NT & m01)
        : m00(m00), m01(m01)
    {}

    NT get_m00() { return m00; }
    NT get_m01() { return m01; }

    Transformation_E1 inverse() const;

    Point_E1<NT>  transform(const Point_E1<NT> & p) const;
    Vector_E1<NT>  transform(const Vector_E1<NT> & p) const;
    Segment_E1<NT> transform(const Segment_E1<NT> & s) const;
    Point_E1<NT>  operator()(const Point_E1<NT> & p) const;
    Vector_E1<NT>  operator()(const Vector_E1<NT> & p) const;
    Segment_E1<NT>  operator()(const Segment_E1<NT> & p) const;

    Transformation_E1<NT> operator*(const Transformation_E1<NT> & TR) const;
};

template<typename NT>
void
Transformation_E1<NT>::setToIdentity()
{
    m00 = 1;
    m01 = 0;
}
template<typename NT>
Transformation_E1<NT>::Transformation_E1()
{
    setToIdentity();
}

template<typename NT>
Transformation_E1<NT>::Transformation_E1(const Identity)
{
    setToIdentity();
}

template<typename NT>
Transformation_E1<NT>::Transformation_E1(const Scale, const Vector_E1<NT> & v)
{
    setToIdentity();
    m00 = v.x();
}

template<typename NT>
Transformation_E1<NT>::Transformation_E1(const Translation, const Vector_E1<NT> & v)
{
    setToIdentity();
    m01 = v.x();
}

template<typename NT>
Transformation_E1<NT>
Transformation_E1<NT>::inverse() const
{
    if(m00 == NT(0))
        throw std::domain_error("Attempting to invert a singular matrix.");

    NT inv = NT(1)/m00;
    return Transformation_E1<NT>(inv, - m01 * inv);
}

template<typename NT>
Point_E1<NT>
Transformation_E1<NT>::transform(const Point_E1<NT> & p) const
{
    return Point_E1<NT>(m00 * p.x() + m01);
}

template<typename NT>
Vector_E1<NT>
Transformation_E1<NT>::transform(const Vector_E1<NT> & v) const
{
    return Vector_E1<NT>(m00 * v.x());
}

template<typename NT>
Segment_E1<NT>
Transformation_E1<NT>::transform(const Segment_E1<NT> & seg) const
{
    Point_E1<NT> s = transform(seg.source());
    Point_E1<NT> t = transform(seg.target());

    return Segment_E1<NT>(s,t);
}

template<typename NT>
Point_E1<NT>
Transformation_E1<NT>::operator()(const Point_E1<NT> & p) const
{
    return transform(p);
}

template<typename NT>
Vector_E1<NT>
Transformation_E1<NT>::operator()(const Vector_E1<NT> & v) const
{
    return transform(v);
}

template<typename NT>
Segment_E1<NT>
Transformation_E1<NT>::operator()(const Segment_E1<NT> & s) const
{
    return transform(s);
}

template<typename NT>
Transformation_E1<NT>
Transformation_E1<NT>::operator*(const Transformation_E1<NT> & TR) const
{
    // Notice the order of composition:
    //      *this is applied second and TR is applied first
    return Transformation_E1<NT>(m00 * TR.m00 ,
                                 m00 * TR.m01 + m01);
}

#endif // TRANSFORMATION_E1_H
