/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_E3_INL_H
#define TRANSFORMATION_E3_INL_H

#include "transformation_e3.h"

template<typename T>
void
Transformation_E3<T>::setToIdentity()
{
    m00 = m11 = m22 = 1;
    m01 = m02 = m03 = 0;
    m10 = m12 = m13 = 0;
    m20 = m21 = m23 = 0;
}
template<typename T>
Transformation_E3<T>::Transformation_E3()
{
    setToIdentity();
}

template<typename T>
Transformation_E3<T>::Transformation_E3(const Identity)
{
    setToIdentity();
}

template<typename T>
Transformation_E3<T>::Transformation_E3(const Scale, const Vector_E3<T>& v)
{
    setToIdentity();
    m00 = v.x();
    m11 = v.y();
    m22 = v.z();
}

template<typename T>
Transformation_E3<T>::Transformation_E3(const Rotation,
                                        const Direction_E3<T>& axis,
                                        const T& angle)
{
    // Requires cos/sin to be defined for T.
    typedef const T CT;
    CT x = axis.x(); CT y = axis.y(); CT z = axis.z();

    CT c = cos(angle); CT s = sin(angle); CT C = CT(1)-c;
    CT xs  = x * s;  CT ys  = y * s;  CT zs = z * s;
    CT xC  = x * C;  CT yC  = y * C;  CT zC = z * C;
    CT xyC = x * yC; CT yzC = y * zC; CT zxC = z * xC;

    m00 = x*xC+c; m01 = xyC-zs; m02 = zxC+ys; m03 = 0;
    m10 = xyC+zs; m11 = y*yC+c; m12 = yzC-xs; m13 = 0;
    m20 = zxC-ys; m21 = yzC+xs; m22 = z*zC+c; m23 = 0;
}

template<typename T>
Transformation_E3<T>::Transformation_E3(const Translation, const Vector_E3<T>& v)
{
    setToIdentity();
    m03 = v.x();
    m13 = v.y();
    m23 = v.z();
}

template<typename T>
Transformation_E3<T>::Transformation_E3(const Orthogonal,
                                        const Point_E3<T>& viewer,
                                        const Point_E3<T>& coi,
                                        const Direction_E3<T>& up)
{
    Direction_E3<T> view = coi - viewer;
    Direction_E3<T> u = cross_product(view, up);
    Direction_E3<T> v = cross_product(u, view);

    m00 =     u.x(); m01 =     u.y(); m02 =     u.z(); m03 = -viewer.x();
    m10 =     v.x(); m11 =     v.y(); m12 =     v.z(); m13 = -viewer.y();
    m20 = -view.x(); m21 = -view.y(); m22 = -view.z(); m23 = -viewer.z();
}

template<typename T>
Transformation_E3<T>
Transformation_E3<T>::inverse() const
{
    typedef const T CT;
    CT det = determinant( m00, m01, m02, m10, m11, m12, m20, m21, m22 );
    if(det == T(0))
        throw std::domain_error("Attempting to invert a singular matrix.");
    CT d = CT(1) / det;

    CT n00 =  determinant( m11, m12, m21, m22);
    CT n01 = -determinant( m01, m02, m21, m22);
    CT n02 =  determinant( m01, m02, m11, m12);
    CT n03 = -determinant( m01, m02, m03, m11, m12, m13, m21, m22, m23 );

    CT n10 = -determinant( m10, m12, m20, m22);
    CT n11 =  determinant( m00, m02, m20, m22);
    CT n12 = -determinant( m00, m02, m10, m12);
    CT n13 =  determinant( m00, m02, m03, m10, m12, m13, m20, m22, m23 );

    CT n20 =  determinant( m10, m11, m20, m21);
    CT n21 = -determinant( m00, m01, m20, m21);
    CT n22 =  determinant( m00, m01, m10, m11);
    CT n23 = -determinant( m00, m01, m03, m10, m11, m13, m20, m21, m23 );

    return Transformation_E3<T>(d * n00, d * n01, d * n02, d * n03,
                                d * n10, d * n11, d * n12, d * n13,
                                d * n20, d * n21, d * n22, d * n23);
}

template<typename T>
Point_E3<T>
Transformation_E3<T>::transform(const Point_E3<T>& p) const
{
    return Point_E3<T>(m00 * p.x() + m01 * p.y() + m02 * p.z() + m03,
                       m10 * p.x() + m11 * p.y() + m12 * p.z() + m13,
                       m20 * p.x() + m21 * p.y() + m22 * p.z() + m23);
}

template<typename T>
Vector_E3<T>
Transformation_E3<T>::transform(const Vector_E3<T>& v) const
{
    return Vector_E3<T>(m00 * v.x() + m01 * v.y() + m02 * v.z(),
                        m10 * v.x() + m11 * v.y() + m12 * v.z(),
                        m20 * v.x() + m21 * v.y() + m22 * v.z());
}

template<typename T>
Direction_E3<T>
Transformation_E3<T>::transform(const Direction_E3<T>& d) const
{
    return Vector_E3<T>(m00 * d.x() + m01 * d.y() + m02 * d.z(),
                        m10 * d.x() + m11 * d.y() + m12 * d.z(),
                        m20 * d.x() + m21 * d.y() + m22 * d.z());
}

template<typename T>
Segment_E3<T>
Transformation_E3<T>::transform(const Segment_E3<T>& seg) const
{
    Point_E3<T> s = transform(seg.source());
    Point_E3<T> t = transform(seg.target());

    return Segment_E3<T>(s,t);
}

template<typename T>
Point_E3<T>
Transformation_E3<T>::operator()(const Point_E3<T>& p) const
{
    return transform(p);
}

template<typename T>
Vector_E3<T> 
Transformation_E3<T>::operator()(const Vector_E3<T>& v) const
{
    return transform(v);
}

template<typename T>
Direction_E3<T> 
Transformation_E3<T>::operator()(const Direction_E3<T>& v) const
{
    return transform(v);
}

template<typename T>
Segment_E3<T> 
Transformation_E3<T>::operator()(const Segment_E3<T>& v) const
{
    return transform(v);
}

template<typename T>
Transformation_E3<T>
Transformation_E3<T>::operator*(const Transformation_E3<T>& TR) const
{
    return Transformation_E3<T>(m00 * TR.m00 + m01 * TR.m10 + m02 * TR.m20      ,
                                m00 * TR.m01 + m01 * TR.m11 + m02 * TR.m21      ,
                                m00 * TR.m02 + m01 * TR.m12 + m02 * TR.m22      ,
                                m00 * TR.m03 + m01 * TR.m13 + m02 * TR.m23 + m03,

                                m10 * TR.m00 + m11 * TR.m10 + m12 * TR.m20      ,
                                m10 * TR.m01 + m11 * TR.m11 + m12 * TR.m21      ,
                                m10 * TR.m02 + m11 * TR.m12 + m12 * TR.m22      ,
                                m10 * TR.m03 + m11 * TR.m13 + m12 * TR.m23 + m13,

                                m20 * TR.m00 + m21 * TR.m10 + m22 * TR.m20      ,
                                m20 * TR.m01 + m21 * TR.m11 + m22 * TR.m21      ,
                                m20 * TR.m02 + m21 * TR.m12 + m22 * TR.m22      ,
                                m20 * TR.m03 + m21 * TR.m13 + m22 * TR.m23 + m23);
}

#endif // TRANSFORMATION_E3_INL_H
