/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_P3_H
#define LINE_P3_H

#include "misc/determinant.h"
#include "geometry/P3/point_p3.h"

template<typename T>
class Line_P3
{
private:
    T _pxy, _pxz, _pxw;
    T _pyz, _pyw, _pzw;
public:
    Line_P3() {}

    Line_P3(const Point_P3<T>& src, const Point_P3<T>& tgt)
    {
        _pxy = determinant(src.hx(), src.hy(),
                           tgt.hx(), tgt.hy());
        _pxz = determinant(src.hx(), src.hz(),
                           tgt.hx(), tgt.hz());
        _pxw = determinant(src.hx(), src.hw(),
                           tgt.hx(), tgt.hw());

        _pyz = determinant(src.hy(), src.hz(),
                           tgt.hy(), tgt.hz());
        _pyw = determinant(src.hy(), src.hw(),
                           tgt.hy(), tgt.hw());
        _pzw = determinant(src.hz(), src.hw(),
                           tgt.hz(), tgt.hw());
    }

    T pxy() const { return _pxy; }
    T pxz() const { return _pxz; }
    T pxw() const { return _pxw; }

    T pyz() const { return _pyz; }
    T pyw() const { return _pyw; }
    T pzw() const { return _pzw; }
};

#endif // LINE_P3_H
