/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DIRECTION_P3_H
#define DIRECTION_P3_H

#include <cmath>
using std::sqrt;
#include "geometry/P3/vector_p3.h"

template<typename T>
class Direction_P3
{
    Vector_P3<T> V;

    void
    normalize() {
        T d = static_cast<T>( sqrt( V.length2() ) );
        V = Vector_P3<T>(V.hx()/d, V.hy()/d, V.hz()/d);
    }

public:
    Direction_P3() : V() {}
    Direction_P3(const T& x, const T& y, const T& z, const T& w = 1) : V(x,y,z,w) {
        normalize();
    }
    Direction_P3(const Vector_P3<T>& V) : V(V) {
        normalize();
    }

    T hx() const { return V.hx(); }
    T hy() const { return V.hy(); }
    T hz() const { return V.hz(); }
    T hw() const { return V.hw(); }

    Vector_P3<T> getVector_P3() const { return V; }

    Direction_P3<T> operator+(const Direction_P3<T>& D2)
    {
        return Direction_P3<T>(V + D2.V);
    }

    bool operator==(const Direction_P3<T>& d) const {
        return (V == d.V);
    }
};

template<class S>
S
dot_product(const Direction_P3<S>& d1, const Direction_P3<S>& d2)
{
    return dot_product(d1.getVector_P3(), d2.getVector_P3());
}

template<class S>
Direction_P3<S>
cross_product(const Direction_P3<S>& v1, const Direction_P3<S>& v2)
{
    return Direction_P3<S>(+ determinant(v1.hy(), v2.hy(),
                                         v1.hz(), v2.hz()),
                           - determinant(v1.hx(), v2.hx(),
                                         v1.hz(), v2.hz()),
                           + determinant(v1.hx(), v2.hx(),
                                         v1.hy(), v2.hy()),
                           v1.hw() * v2.hw());
}

#endif // DIRECTION_P3_H
