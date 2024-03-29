/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_E3_H
#define LINE_E3_H

#include <iostream>
using std::ostream;

#include "geometry/E3/point_e3.h"
#include "misc/determinant.h"

template<typename T>
class Line_E3;

template<typename T>
ostream& operator<<(ostream& os, const Line_E3<T>& seg);

template<typename T>
class Line_E3
{
private:
    Point_E3<T> src;
    Point_E3<T> tgt;

public:
    Line_E3() : src(), tgt() {}
    Line_E3(const Point_E3<T>& src, const Point_E3<T>& tgt): src(src), tgt(tgt) {}

    const Point_E3<T>& source() const { return src; }
    const Point_E3<T>& target() const { return tgt; }

    friend ostream& operator<< <>(ostream& os, const Line_E3<T>& seg);
};

template<typename T>
ostream& operator<<(ostream& os, const Line_E3<T>& seg)
{
    return os << seg.src << " -- " << seg.tgt;
}

#endif // LINE_E3_H
