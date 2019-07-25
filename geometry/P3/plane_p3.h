/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef plane_P3_h
#define plane_P3_h

#include "geometry/P3/vector_p3.h"

template<typename T>
class Plane_P3;

template<typename T>
istream& operator>> (istream& is, Plane_P3<T>& p);

template<typename T>
class Plane_P3
{
    T _X, _Y, _Z, _W;

    void init_Xbcd(const Point_P3<T>& p1, const Point_P3<T>& p2, const Point_P3<T>& p3)
    {
        _X = + determinant(p1.hy(), p1.hz(), p1.hw(),
                           p2.hy(), p2.hz(), p2.hw(),
                           p3.hy(), p3.hz(), p3.hw());
        _Y = - determinant(p1.hx(), p1.hz(), p1.hw(),
                           p2.hx(), p2.hz(), p2.hw(),
                           p3.hx(), p3.hz(), p3.hw());
        _Z = + determinant(p1.hx(), p1.hy(), p1.hw(),
                           p2.hx(), p2.hy(), p2.hw(),
                           p3.hx(), p3.hy(), p3.hw());
        _W = - determinant(p1.hx(), p1.hy(), p1.hz(),
                           p2.hx(), p2.hy(), p2.hz(),
                           p3.hx(), p3.hy(), p3.hz());
    }
public:
    Plane_P3() {}
    Plane_P3(const Point_P3<T>& P1, const Point_P3<T>& P2, const Point_P3<T>& P3)
    {
        init_Xbcd(P1, P2, P3);
    }

    T X() const { return _X; }
    T Y() const { return _Y; }
    T Z() const { return _Z; }
    T W() const { return _W; }

    friend istream& operator>> <>(istream& is, Plane_P3<T>& p);
};

template<typename T>
ostream& operator<< (ostream& os, const Plane_P3<T>& p)
{
    return os << p.X() << " " << p.Y() << " " << p.Z() << " " << p.W();
}

template<typename T>
istream& operator>> (istream& is, Plane_P3<T>& p)
{
    return is >> p._X >> p._Y >> p._Z >> p._W;
}

#endif // plane_P3_h
