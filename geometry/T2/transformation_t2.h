/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_T2_H
#define TRANSFORMATION_T2_H

#include <cmath>
#include <cassert>

#include "geometry/T2/point_t2.h"
#include "geometry/T2/segment_t2.h"
#include "geometry/T2/vector_t2.h"
#include "geometry/T2/direction_t2.h"

#include "geometry/E2/point_e2.h"
#include "geometry/E2/direction_e2.h"

#include "geometry/lib/transformations.h"

extern Identity IDENTITY;
extern Scale SCALE;
extern Rotation ROTATION;
extern Translation TRANSLATION;
extern Orthogonal ORTHOGONAL;
extern Perspective PERSPECTIVE;

template<typename T>
class Transformation_T2;

template<typename T>
ostream& operator<<(ostream& os, const Transformation_T2<T>& T);

template<typename T>
class Transformation_T2
{
    friend class SketchpadData;
protected:
    T m00, m01, m02;
    T m10, m11, m12;
    T m20, m21, m22;
    void set_to_identity();
public:    
    Transformation_T2();
    Transformation_T2(const Identity);
    Transformation_T2(const Scale, const Vector_T2<T>& v);
    Transformation_T2(const Translation, const Vector_T2<T>& v);

    Transformation_T2(const Rotation,
                      const Direction_T2<T>& axis,
                      const T& angle);

    Transformation_T2(const Perspective,
                      const T& fov,
                      const T& near,
                      const T& far);

    // glFrustum
    void set_frustum(const T& left, const T& right,
                     const T& near, const T& far);

    // gluPerspective
    void set_perspective(const T& fov, const T& near, const T& far);

    Transformation_T2(const T& m00, const T& m01, const T& m02,
                      const T& m10, const T& m11, const T& m12,
                      const T& m20, const T& m21, const T& m22)
        : m00(m00), m01(m01), m02(m02),
          m10(m10), m11(m11), m12(m12),
          m20(m20), m21(m21), m22(m22)
    {}

    Point_T2<T>  transform(const Point_T2<T>& p) const;
    Vector_T2<T>  transform(const Vector_T2<T>& v) const;
    Segment_T2<T> transform(const Segment_T2<T>& s) const;

    Point_T2<T>  operator()(const Point_T2<T>& p) const;
    Vector_T2<T>  operator()(const Vector_T2<T>& v) const;

    Transformation_T2<T> operator*(const Transformation_T2<T>& TR) const;

    friend ostream& operator<< <>(ostream& os, const Transformation_T2<T>& PT);
};

template<typename T>
void
Transformation_T2<T>::set_to_identity()
{
    m00=1; m01=0; m02=0;
    m10=0; m11=1; m12=0;
    m20=0; m21=0; m22=1;
}
template<typename T>
Transformation_T2<T>::Transformation_T2()
{
    set_to_identity();
}

template<typename T>
Transformation_T2<T>::Transformation_T2(const Identity)
{
    set_to_identity();
}

template<typename T>
Transformation_T2<T>::Transformation_T2(const Scale, const Vector_T2<T>& v)
{
    set_to_identity();
    m00 = v.x();
    m11 = v.y();
    m22 = v.w();
}

template<typename T>
Transformation_T2<T>::Transformation_T2(const Rotation,
                                        const Direction_T2<T>& axis,
                                        const T& angle)
{
    // ...
    assert(false);
}

template<typename T>
Transformation_T2<T>::Transformation_T2(const Translation, const Vector_T2<T>& v)
{
    // ...
    assert(false);
}

// TBC:

// template<typename T>
// Transformation_T2<T>::Transformation_T2(const Orthogonal,
//                                         const Point_T2<T>& viewer,
//                                         const Point_T2<T>& coi)
// {
//     Direction_T2<T> view = coi - viewer;
//     Direction_T2<T> u = cross_product(view, up);
//     Direction_T2<T> v = cross_product(u, view);
//     
//     m00 =     u.hx(); m01 =     u.hy(); m02 =     u.hz(); m03 = -viewer.hx();
//     m10 =     v.hx(); m11 =     v.hy(); m12 =     v.hz(); m13 = -viewer.hy();
//     m20 = -view.hx(); m21 = -view.hy(); m22 = -view.hz(); m23 = -viewer.hz();
//     
//     m30 = m31 = m32 = 0; m33 = 1;
// }
// 
// template<typename T>
// Transformation_T2<T>::Transformation_T2(const Orthogonal,
//                                         const Point_E2<T>& viewer,
//                                         const Point_E2<T>& coi)
// {
//     Direction_E2<T> view = coi - viewer;
//     Direction_E2<T> u = cross_product(view, up);
//     Direction_E2<T> v = cross_product(u, view);
//     
//     m00 =     u.x(); m01 =     u.y(); m02 =     u.z(); m03 = -viewer.x();
//     m10 =     v.x(); m11 =     v.y(); m12 =     v.z(); m13 = -viewer.y();
//     m20 = -view.x(); m21 = -view.y(); m22 = -view.z(); m23 = -viewer.z();
//     
//     m30 = m31 = m32 = 0; m33 = 1;
// }

// template<typename T>
// Transformation_T2<T>::Transformation_T2(const Perspective,
//                                         const T& fov,
//                                         const T& near,
//                                         const T& far)
// {
//     // ...
//     assert(false);
// }
// 
// // glFrustum
// template<typename T>
// void
// Transformation_T2<T>::set_frustum(const T& left, const T& right,
//                                   const T& near, const T& far)
// {
//     // ...
//     assert(false);
// }
// 
// // gluPerspective
// template<typename T>
// void
// Transformation_T2<T>::set_perspective(const T& fov, const T& aspect, const T& near, const T& far)
// {
//     // ...
//     assert(false);
// }

template<typename T>
Point_T2<T>
Transformation_T2<T>::transform(const Point_T2<T>& p) const
{
    return Point_T2<T>(m00 * p.hx() + m01 * p.hy() + m02 * p.hw(),
                       m10 * p.hx() + m11 * p.hy() + m12 * p.hw(),
                       m20 * p.hx() + m21 * p.hy() + m22 * p.hw());
}

template<typename T>
Vector_T2<T>
Transformation_T2<T>::transform(const Vector_T2<T>& p) const
{
    return Vector_T2<T>(m00 * p.hx() + m01 * p.hy() + m02 * p.hw(),
                        m10 * p.hx() + m11 * p.hy() + m12 * p.hw(),
                        m20 * p.hx() + m21 * p.hy() + m22 * p.hw());
}

template<typename T>
Segment_T2<T>
Transformation_T2<T>::transform(const Segment_T2<T>& seg) const
{
    Point_T2<T> s = transform(seg.source());
    Point_T2<T> t = transform(seg.target());

    return Segment_T2<T>(s,t);
}

template<typename T>
Point_T2<T>
Transformation_T2<T>::operator()(const Point_T2<T>& p) const
{
    return transform(p);
}

template<typename T>
Vector_T2<T>
Transformation_T2<T>::operator()(const Vector_T2<T>& v) const
{
    return transform(v);
}

template<typename T>
Transformation_T2<T>
Transformation_T2<T>::operator*(const Transformation_T2<T>& TR) const
{
    return Transformation_T2<T>(m00 * TR.m00 + m01 * TR.m10 + m02 * TR.m20,
                                m00 * TR.m01 + m01 * TR.m11 + m02 * TR.m21,
                                m00 * TR.m02 + m01 * TR.m12 + m02 * TR.m22,
                                m00 * TR.m03 + m01 * TR.m13 + m02 * TR.m23,

                                m10 * TR.m00 + m11 * TR.m10 + m12 * TR.m20,
                                m10 * TR.m01 + m11 * TR.m11 + m12 * TR.m21,
                                m10 * TR.m02 + m11 * TR.m12 + m12 * TR.m22,
                                m10 * TR.m03 + m11 * TR.m13 + m12 * TR.m23,

                                m20 * TR.m00 + m21 * TR.m10 + m22 * TR.m20,
                                m20 * TR.m01 + m21 * TR.m11 + m22 * TR.m21,
                                m20 * TR.m02 + m21 * TR.m12 + m22 * TR.m22,
                                m20 * TR.m03 + m21 * TR.m13 + m22 * TR.m23);
}

template<typename NT>
ostream& operator<<(ostream& os, const Transformation_T2<NT>& PT)
{
    return os << PT.m00 << "  " << PT.m01 << "  " << PT.m02 << std::endl
              << PT.m10 << "  " << PT.m11 << "  " << PT.m12 << std::endl
              << PT.m20 << "  " << PT.m21 << "  " << PT.m22 << std::endl;
}

#endif // TRANSFORMATION_T2_H
