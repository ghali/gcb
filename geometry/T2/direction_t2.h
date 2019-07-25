/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DIRECTION_T2_H
#define DIRECTION_T2_H

#include <cmath>
using std::sqrt;
#include "geometry/T2/vector_t2.h"

template<typename NT>
class Direction_T2
{
    Vector_T2<NT> V;

    void
    normalize() {
        NT d = static_cast<NT>( sqrt( V.length2() ) );
        V = Vector_T2<NT>(V.hx()/d, V.hy()/d);
    }

public:
    Direction_T2() : V() {}
    Direction_T2(const NT& x, const NT& y, const NT& w = 1) : V(x,y,w) {
        normalize();
    }
    Direction_T2(const Vector_T2<NT>& V) : V(V) {
        normalize();
    }

    NT hx() const { return V.hx(); }
    NT hy() const { return V.hy(); }
    NT hw() const { return V.hw(); }

    Vector_T2<NT> getVector_T2() const { return V; }

    Direction_T2<NT> operator+(const Direction_T2<NT>& D2)
    {
        return Direction_T2<NT>(V + D2.V);
    }

    bool operator==(const Direction_T2<NT>& d) const {
        return (V == d.V);
    }
};

template<class S>
S
dot_product(const Direction_T2<S>& d1, const Direction_T2<S>& d2)
{
    return dot_product(d1.getVector_T2(), d2.getVector_T2());
}

template<class S>
Direction_T2<S>
cross_product(const Direction_T2<S>& v1, const Direction_T2<S>& v2)
{
    return Direction_T2<S>(+ determinant(v1.hy(), v2.hy(),
                                         v1.hz(), v2.hz()),
                           - determinant(v1.hx(), v2.hx(),
                                         v1.hz(), v2.hz()),
                           v1.hw() * v2.hw());
}

#endif // DIRECTION_T2_H
