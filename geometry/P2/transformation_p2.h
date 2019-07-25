/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_P2_H
#define TRANSFORMATION_P2_H

#include <cassert>
#include <cmath>
#include "geometry/P2/point_p2.h"
#include "geometry/P2/line_p2.h"

#include "geometry/lib/transformations.h"

extern Identity IDENTITY;
extern Scale SCALE;
extern Rotation ROTATION;
extern Translation TRANSLATION;
extern Orthogonal ORTHOGONAL;
extern Perspective PERSPECTIVE;

template<typename T>
class Transformation_P2;

template<typename T>
ostream& operator<<(ostream& os, const Transformation_P2<T>& T);

template<typename T>
class Transformation_P2
{
    friend class SketchpadData;
protected:
    T m00, m01, m02;
    T m10, m11, m12;
    T m20, m21, m22;
    void setToIdentity();
public:    
    Transformation_P2();
    Transformation_P2(const Identity);
    Transformation_P2(const Scale, const T& xs, const T& ys, const T& ws);
    Transformation_P2(const Translation, const T& xs, const T& ys, const T& ws);

    Transformation_P2(const Rotation,
                      const Direction_P2<T>& axis,
                      const T& angle);

    Transformation_P2(const Orthogonal,
                      const Point_P2<T>& viewer,
                      const Point_P2<T>& coi,
                      const Direction_P2<T>& up = Direction_P2<T>(0.0,1.0,0.0));

    Transformation_P2(const Perspective,
                      const T& fov,
                      const T& near,
                      const T& far);

    // glFrustum
    void set_frustum(const T& left, const T& right,
                     const T& bottom, const T& top,
                     const T& near, const T& far);

    // gluPerspective
    void set_perspective(const T& fov, const T& aspect, const T& near, const T& far);

    Transformation_P2(const T& m00, const T& m01, const T& m02,
                      const T& m10, const T& m11, const T& m12,
                      const T& m20, const T& m21, const T& m22)
        : m00(m00), m01(m01), m02(m02),
          m10(m10), m11(m11), m12(m12),
          m20(m20), m21(m21), m22(m22)
    {}

    Point_P2<T>  transform(const Point_P2<T>& p) const;

    Line_P2<T> transform(const Line_P2<T>& pl) const;

    Point_P2<T>  operator()(const Point_P2<T>& p) const;

    Line_P2<T>  operator()(const Line_P2<T>& v) const;

    Transformation_P2<T> operator*(const Transformation_P2<T>& TR) const;

    friend ostream& operator<< <>(ostream& os, const Transformation_P2<T>& PT);
};

template<typename T>
void
Transformation_P2<T>::setToIdentity()
{
    m00 = m11 = m22 = 1;
    m01 = m02  = 0;
    m10 = m12  = 0;
    m20 = m21  = 0;
}
template<typename T>
Transformation_P2<T>::Transformation_P2()
{
    setToIdentity();
}

template<typename T>
Transformation_P2<T>::Transformation_P2(const Identity)
{
    setToIdentity();
}

template<typename T>
Transformation_P2<T>::Transformation_P2(const Scale, const T& xs, const T& ys, const T& ws)
{
    setToIdentity();
    m00 = xs;
    m11 = ys;
    m22 = ws;
}

template<typename T>
Transformation_P2<T>::Transformation_P2(const Rotation,
                                        const Direction_P2<T>& axis,
                                        const T& angle)
{
    // ...
    assert(false);
}

template<typename T>
Transformation_P2<T>::Transformation_P2(const Translation, const T& xs, const T& ys, const T& ws)
{
    // ...    
    assert(false);
}

template<typename T>
Point_P2<T>
Transformation_P2<T>::transform(const Point_P2<T>& p) const
{
    return Point_P2<T>(m00 * p.hx() + m01 * p.hy() + m02 * p.hw(),
                       m10 * p.hx() + m11 * p.hy() + m12 * p.hw(),
                       m20 * p.hx() + m21 * p.hy() + m22 * p.hw());
}

template<typename T>
Line_P2<T>
Transformation_P2<T>::transform(const Line_P2<T>& pl) const
{
    // ...
    assert(false);
}

template<typename T>
Point_P2<T>
Transformation_P2<T>::operator()(const Point_P2<T>& p) const
{
    return transform(p);
}

template<typename T>
Line_P2<T>
Transformation_P2<T>::operator()(const Line_P2<T>& pl) const
{
    return transform(pl);
}

template<typename T>
Transformation_P2<T>
Transformation_P2<T>::operator*(const Transformation_P2<T>& TR) const
{
    return Transformation_P2<T>(m00 * TR.m00 + m01 * TR.m10 + m02 * TR.m20,
                                m00 * TR.m01 + m01 * TR.m11 + m02 * TR.m21,
                                m00 * TR.m02 + m01 * TR.m12 + m02 * TR.m22,

                                m10 * TR.m00 + m11 * TR.m10 + m12 * TR.m20,
                                m10 * TR.m01 + m11 * TR.m11 + m12 * TR.m21,
                                m10 * TR.m02 + m11 * TR.m12 + m12 * TR.m22,

                                m20 * TR.m00 + m21 * TR.m10 + m22 * TR.m20,
                                m20 * TR.m01 + m21 * TR.m11 + m22 * TR.m21,
                                m20 * TR.m02 + m21 * TR.m12 + m22 * TR.m22);
}

template<typename NT>
ostream& operator<<(ostream& os, const Transformation_P2<NT>& PT)
{
    return os << PT.m00 << "  " << PT.m01 << "  " << PT.m02 << std::endl
              << PT.m10 << "  " << PT.m11 << "  " << PT.m12 << std::endl
              << PT.m20 << "  " << PT.m21 << "  " << PT.m22 << std::endl;
}

#endif // TRANSFORMATION_P2_H
