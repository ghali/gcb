/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_E3_H
#define TRANSFORMATION_E3_H

#include <cmath>
#include <stdexcept>

#include "geometry/E3/point_e3.h"
#include "geometry/E3/segment_e3.h"
#include "geometry/E3/vector_e3.h"
#include "geometry/E3/direction_e3.h"

#include "geometry/lib/transformations.h"

extern Identity IDENTITY;
extern Scale SCALE;
extern Rotation ROTATION;
extern Translation TRANSLATION;
extern Orthogonal ORTHOGONAL;

template<typename T>
class Transformation_E3
{
    friend class SketchpadData;
protected:
    T m00, m01, m02, m03;
    T m10, m11, m12, m13;
    T m20, m21, m22, m23;

    // m30 = 0 , m31 = 0 , m32 = 0, m33 = 1
    void setToIdentity();
public:    
    Transformation_E3();
    Transformation_E3(const Identity);
    Transformation_E3(const Scale, const Vector_E3<T>& v);
    Transformation_E3(const Translation, const Vector_E3<T>& v);

    Transformation_E3(const Rotation,
                      const Direction_E3<T>& axis,
                      const T& angle);

    Transformation_E3(const Orthogonal,
                      const Point_E3<T>& viewer,
                      const Point_E3<T>& coi,
                      const Direction_E3<T>& up = Direction_E3<T>(0,1,0));

    Transformation_E3(const T& m00, const T& m01, const T& m02, const T& m03,
                      const T& m10, const T& m11, const T& m12, const T& m13,
                      const T& m20, const T& m21, const T& m22, const T& m23)
        : m00(m00), m01(m01), m02(m02), m03(m03),
          m10(m10), m11(m11), m12(m12), m13(m13),
          m20(m20), m21(m21), m22(m22), m23(m23)
    {}

    T get_m00() { return m00; }
    T get_m01() { return m01; }
    T get_m02() { return m02; }
    T get_m03() { return m03; }

    T get_m10() { return m10; }
    T get_m11() { return m11; }
    T get_m12() { return m12; }
    T get_m13() { return m13; }

    T get_m20() { return m20; }
    T get_m21() { return m21; }
    T get_m22() { return m22; }
    T get_m23() { return m23; }

    Transformation_E3 inverse() const;

    Point_E3<T>      transform(const Point_E3<T>& p) const;
    Vector_E3<T>     transform(const Vector_E3<T>& v) const;
    Direction_E3<T>  transform(const Direction_E3<T>& v) const;
    Segment_E3<T>    transform(const Segment_E3<T>& s) const;
    Point_E3<T>      operator()(const Point_E3<T>& p) const;
    Vector_E3<T>     operator()(const Vector_E3<T>& v) const;
    Direction_E3<T>  operator()(const Direction_E3<T>& v) const;
    Segment_E3<T>    operator()(const Segment_E3<T>& v) const;

    Transformation_E3<T> operator*(const Transformation_E3<T>& TR) const;
};

#include "transformation_e3_inl.h"

#endif // TRANSFORMATION_E3_H
