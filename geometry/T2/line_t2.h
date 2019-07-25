/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_T2_H
#define LINE_T2_H

#include "geometry/P2/point_p2.h"
#include "misc/determinant.h"

template<typename T>
class Line_T2;

template<typename T>
ostream& operator<<(ostream& os, const Line_T2<T>& seg);

template<typename T>
class Line_T2
{
private:
    T _a, _b, _c;               // ax+by+cw=0
    Point_T2<T> src;
    Point_T2<T> tgt;

    void init_abc()
    {
        _a = + determinant(src.hy(), src.hw(), tgt.hy(), tgt.hw());
        _b = - determinant(src.hx(), src.hw(), tgt.hx(), tgt.hw());
        _c = + determinant(src.hx(), src.hy(), tgt.hx(), tgt.hy());
    }
public:
    Line_T2() : _a(), _b(), _c(), src(), tgt() {}
    Line_T2(const Point_T2<T>& src, const Point_T2<T>& tgt): src(src), tgt(tgt)
    {
        init_abc();
    }

    const Point_T2<T>& source() const { return src; }
    const Point_T2<T>& target() const { return tgt; }

    T a() const { return _a; }
    T b() const { return _b; }
    T c() const { return _c; }

    bool isIncident(const Point_T2<T>& p) const
    {
        return (_a * p.hx() + _b * p.hy() + _c * p.hw()) == 0;
    }

    friend ostream& operator<< <>(ostream& os, const Line_T2<T>& seg);
};

template<typename T>
ostream& operator<<(ostream& os, const Line_T2<T>& seg)
{
    return os << seg._a << " " << seg._b << " " << seg._c << "  "
              << seg.src << " -- " << seg.tgt;
}

#endif // LINE_T2_H
