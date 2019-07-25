/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_P1_H
#define POINT_P1_H

#include <iostream>

#include "misc/determinant.h"

//----------------Point_P1_Begin----------------
template<typename NT>
class Point_P1
{
    NT _x, _w;
public:
    Point_P1(const NT& x = 0, const NT& w = 1) : _x(x), _w(w) {}

    const NT hx() const { return _x; }
    const NT hw() const { return _w; }

    bool operator==(const Point_P1<NT>& p) const {
        return (this == &p) ||
            determinant(_x, _w, p._x, p._w) == 0;
    }
};
//----------------Point_P1_End----------------

template<typename NT>
std::ostream&
operator<<(std::ostream& os, const Point_P1<NT>& p) {
    return os << p.x() << " " << p.w();
}

#endif // POINT_P1_H
