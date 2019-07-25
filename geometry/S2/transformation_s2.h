/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TRANSFORMATION_S2_H
#define TRANSFORMATION_S2_H

#include <cmath>
#include <utility>
using std::cos; using std::sin;
#include <iostream>
using namespace std;
#include "geometry/S3/quaternion.h"

#include "geometry/E3/direction_e3.h"
#include "geometry/S2/point_s2.h"

template<typename NT>
class Rotation_S2
{
    Quaternion<NT> _unitq;
public:
    Rotation_S2(const Quaternion<NT>& q)
    {
        NT n = q.norm();
        _unitq = Quaternion<NT>(q.r()/n, q.vi()/n, q.vj()/n, q.vk()/n);
    }
    Rotation_S2(const NT& angleInRadians, const Direction_E3<NT>& axis)
    {
        NT c = cos(angleInRadians/2.0);
        NT s = sin(angleInRadians/2.0);
        _unitq = Quaternion<NT>(c, s * axis.x(), s * axis.y(), s * axis.z());
    }

    Quaternion<NT> unitq() const { return _unitq; }

    Point_S2<NT>
    rotate(const Point_S2<NT>& p) const
    {
        Quaternion<NT> pq(0, p.x(), p.y(), p.z());
        Quaternion<NT> rotatedQ = _unitq * pq * _unitq.conjugate();
        // assert(rotatedQ.r() == 0);
        return Point_S2<NT>(rotatedQ.vi(), rotatedQ.vj(), rotatedQ.vk());
    }

    std::pair<double,Direction_E3<NT> >
    getAngleAndAxis()
    {
        NT two(static_cast<NT>(2));
        NT a = acos(_unitq.r());
        NT s = sin(a);

        NT angle = two * a;
        Direction_E3<NT> axis( _unitq.vi() / s, _unitq.vj() / s, _unitq.vk() / s );
        return make_pair(angle, axis);
    }
    Rotation_S2<NT> operator*(const Rotation_S2<NT>& R2) const
    {
        return Rotation_S2<NT>( _unitq * R2._unitq );
    }
};

#endif // TRANSFORMATION_S2_H
