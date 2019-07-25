/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_P3_H
#define TRANSFORMATION_P3_H

#include <cassert>
#include <cmath>

#include "geometry/P3/point_p3.h"
#include "geometry/P3/plane_p3.h"
#include "geometry/P3/direction_p3.h"
#include "geometry/P3/vector_p3.h"

#include "geometry/E3/point_e3.h"
#include "geometry/E3/direction_e3.h"

#include "geometry/lib/transformations.h"

extern Identity IDENTITY;
extern Scale SCALE;
extern Rotation ROTATION;
extern Translation TRANSLATION;
extern Orthogonal ORTHOGONAL;
extern Perspective PERSPECTIVE;

template<typename T>
class Transformation_P3;

template<typename T>
ostream& operator<<(ostream& os, const Transformation_P3<T>& T);

template<typename T>
class Transformation_P3
{
    friend class SketchpadData;
protected:
    T m00, m01, m02, m03;
    T m10, m11, m12, m13;
    T m20, m21, m22, m23;
    T m30, m31, m32, m33;
    void set_to_identity();
public:    
    Transformation_P3();
    Transformation_P3(const Identity);
    Transformation_P3(const Scale, const Vector_P3<T>& v);
    Transformation_P3(const Translation, const Vector_P3<T>& v);

    Transformation_P3(const Rotation,
                      const Direction_P3<T>& axis,
                      const T& angle);

    Transformation_P3(const Orthogonal,
                      const Point_E3<T>& viewer,
                      const Point_E3<T>& coi,
                      const Direction_E3<T>& up = Direction_E3<T>(0.0,1.0,0.0));

    Transformation_P3(const Perspective,
                      const T& fov,
                      const T& near,
                      const T& far);

    // duplicate glFrustum
    void set_frustum(const T& left, const T& right,
                     const T& bottom, const T& top,
                     const T& near, const T& far);

    // duplicate gluPerspective
    void set_perspective(const T& fov, const T& aspect, const T& near, const T& far);

    Transformation_P3(const T& m00, const T& m01, const T& m02, const T& m03,
                      const T& m10, const T& m11, const T& m12, const T& m13,
                      const T& m20, const T& m21, const T& m22, const T& m23,
                      const T& m30, const T& m31, const T& m32, const T& m33)
        : m00(m00), m01(m01), m02(m02), m03(m03),
          m10(m10), m11(m11), m12(m12), m13(m13),
          m20(m20), m21(m21), m22(m22), m23(m23),
          m30(m30), m31(m31), m32(m32), m33(m33)
    {}

    Point_P3<T>  transform(const Point_P3<T>& p) const;
    Vector_P3<T>  transform(const Vector_P3<T>& v) const;

    Plane_P3<T> transform(const Plane_P3<T>& pl) const;

    Point_P3<T>  operator()(const Point_P3<T>& p) const;
    Vector_P3<T>  operator()(const Vector_P3<T>& v) const;

    Plane_P3<T>  operator()(const Plane_P3<T>& v) const;

    Transformation_P3<T> operator*(const Transformation_P3<T>& TR) const;

    friend ostream& operator<< <>(ostream& os, const Transformation_P3<T>& PT);
};

template<typename T>
void
Transformation_P3<T>::set_to_identity()
{
    m00 = m11 = m22 = m33 = 1;
    m01 = m02 = m03 = 0;
    m10 = m12 = m13 = 0;
    m20 = m21 = m23 = 0;
    m30 = m31 = m32 = 0;
}
template<typename T>
Transformation_P3<T>::Transformation_P3()
{
    set_to_identity();
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Identity)
{
    set_to_identity();
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Scale, const Vector_P3<T>& v)
{
    set_to_identity();
    m00 = v.x();
    m11 = v.y();
    m22 = v.z();
    m33 = v.w();
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Rotation,
                                        const Direction_P3<T>& axis,
                                        const T& angle)
{
    // ...
    assert(false);
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Translation, const Vector_P3<T>& v)
{
    // ...
    assert(false);
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Orthogonal,
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

    m30 = m31 = m32 = 0; m33 = 1;
}

template<typename T>
Transformation_P3<T>::Transformation_P3(const Perspective,
                                        const T& fov,
                                        const T& near,
                                        const T& far)
{
    set_to_identity();    
}

// glFrustum
template<typename T>
void
Transformation_P3<T>::set_frustum(const T& left, const T& right,
                                  const T& bottom, const T& top,
                                  const T& near, const T& far)
{
    m00 = 2*near/(right-left); m01 =                   0;
    ;;;;; m02 = (right+left)/(right-left); m03 =                      0;
    m10 =                   0; m11 = 2*near/(top-bottom);
    ;;;;; m12 = (top+bottom)/(top-bottom); m13 =                      0;
    m20 =                   0; m21 =                   0;
    ;;;;; m22 =    -(far+near)/(far-near); m23 = -2*far*near/(far-near);
    m30 =                   0; m31 =                   0;
    ;;;;; m32 =                        -1; m33 =                      0;
}

// gluPerspective
template<typename T>
void
Transformation_P3<T>::set_perspective(
                                      const T& fov, const T& aspect, 
                                      const T& near, const T& far)
{
    T top = near * std::tan((M_PI / 180.0) * fov / 2.0);
    T bottom = -top;
    T right = top * aspect;
    T left = -right;
    set_frustum(left, right, bottom, top, near, far);
}

template<typename T>
Point_P3<T>
Transformation_P3<T>::transform(const Point_P3<T>& p) const
{
    return Point_P3<T>(m00 * p.hx() + m01 * p.hy() + m02 * p.hz() + m03 * p.hw(),
                       m10 * p.hx() + m11 * p.hy() + m12 * p.hz() + m13 * p.hw(),
                       m20 * p.hx() + m21 * p.hy() + m22 * p.hz() + m23 * p.hw(),
                       m30 * p.hx() + m31 * p.hy() + m32 * p.hz() + m33 * p.hw());
}

template<typename T>
Vector_P3<T>
Transformation_P3<T>::transform(const Vector_P3<T>& p) const
{
    return Vector_P3<T>(m00 * p.hx() + m01 * p.hy() + m02 * p.hz() + m03 * p.hw(),
                        m10 * p.hx() + m11 * p.hy() + m12 * p.hz() + m13 * p.hw(),
                        m20 * p.hx() + m21 * p.hy() + m22 * p.hz() + m23 * p.hw(),
                        m30 * p.hx() + m31 * p.hy() + m32 * p.hz() + m33 * p.hw());
}

template<typename T>
Plane_P3<T>
Transformation_P3<T>::transform(const Plane_P3<T>& pl) const
{
    assert(false);              // continue here
    return Plane_P3<T>();
}

template<typename T>
Point_P3<T>
Transformation_P3<T>::operator()(const Point_P3<T>& p) const
{
    return transform(p);
}

template<typename T>
Vector_P3<T>
Transformation_P3<T>::operator()(const Vector_P3<T>& v) const
{
    return transform(v);
}

template<typename T>
Plane_P3<T>
Transformation_P3<T>::operator()(const Plane_P3<T>& pl) const
{
    return transform(pl);
}

template<typename T>
Transformation_P3<T>
Transformation_P3<T>::operator*(const Transformation_P3<T>& TR) const
{
    return Transformation_P3<T>(m00 * TR.m00 + m01 * TR.m10 + m02 * TR.m20 + m03 * TR.m30,
                                m00 * TR.m01 + m01 * TR.m11 + m02 * TR.m21 + m03 * TR.m31,
                                m00 * TR.m02 + m01 * TR.m12 + m02 * TR.m22 + m03 * TR.m32,
                                m00 * TR.m03 + m01 * TR.m13 + m02 * TR.m23 + m03 * TR.m33,

                                m10 * TR.m00 + m11 * TR.m10 + m12 * TR.m20 + m13 * TR.m30,
                                m10 * TR.m01 + m11 * TR.m11 + m12 * TR.m21 + m13 * TR.m31,
                                m10 * TR.m02 + m11 * TR.m12 + m12 * TR.m22 + m13 * TR.m32,
                                m10 * TR.m03 + m11 * TR.m13 + m12 * TR.m23 + m13 * TR.m33,

                                m20 * TR.m00 + m21 * TR.m10 + m22 * TR.m20 + m23 * TR.m30,
                                m20 * TR.m01 + m21 * TR.m11 + m22 * TR.m21 + m23 * TR.m31,
                                m20 * TR.m02 + m21 * TR.m12 + m22 * TR.m22 + m23 * TR.m32,
                                m20 * TR.m03 + m21 * TR.m13 + m22 * TR.m23 + m23 * TR.m33,

                                m30 * TR.m00 + m31 * TR.m10 + m32 * TR.m20 + m33 * TR.m30,
                                m30 * TR.m01 + m31 * TR.m11 + m32 * TR.m21 + m33 * TR.m31,
                                m30 * TR.m02 + m31 * TR.m12 + m32 * TR.m22 + m33 * TR.m32,
                                m30 * TR.m03 + m31 * TR.m13 + m32 * TR.m23 + m33 * TR.m33);
}

template<typename NT>
ostream& operator<<(ostream& os, const Transformation_P3<NT>& PT)
{
    return os << PT.m00 << "  " << PT.m01 << "  " << PT.m02 << "  " << PT.m03 << std::endl
              << PT.m10 << "  " << PT.m11 << "  " << PT.m12 << "  " << PT.m13 << std::endl
              << PT.m20 << "  " << PT.m21 << "  " << PT.m22 << "  " << PT.m23 << std::endl
              << PT.m30 << "  " << PT.m31 << "  " << PT.m32 << "  " << PT.m33 << std::endl;
}

#endif // TRANSFORMATION_P3_H
