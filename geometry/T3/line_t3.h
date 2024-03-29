/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_T3_H
#define LINE_T3_H

#include "misc/determinant.h"
#include "geometry/T3/point_t3.h"

template<typename T>
class Line_T3
{
private:
    T _p23, _p31, _p12, _p01, _p02, _p03;
public:
    Line_T3() {}

    Line_T3(const Point_T3<T>& src, const Point_T3<T>& tgt)
    {
        // 0 1 2 3
        // x y z w
        _p23 = determinant(src.z(), src.w(),
                           tgt.z(), tgt.w());
        _p31 = determinant(src.w(), src.x(),
                           tgt.w(), tgt.x());
        _p12 = determinant(src.y(), src.z(),
                           tgt.y(), tgt.z());

        _p01 = determinant(src.x(), src.y(),
                           tgt.x(), tgt.y());
        _p02 = determinant(src.x(), src.z(),
                           tgt.x(), tgt.z());
        _p03 = determinant(src.x(), src.w(),
                           tgt.x(), tgt.w());
    }

    T p23() const { return _p23; }
    T p31() const { return _p31; }
    T p12() const { return _p12; }
    T p01() const { return _p01; }
    T p02() const { return _p02; }
    T p03() const { return _p03; }
};

#endif // LINE_T3_H
