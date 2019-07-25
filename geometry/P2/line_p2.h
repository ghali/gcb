/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef LINE_P2_H
#define LINE_P2_H

#include "geometry/P2/point_p2.h"
#include "misc/determinant.h"

template<typename NT>
class Line_P2;

template<typename NT>
ostream& operator<<(ostream& os, const Line_P2<NT>& seg);

//----------------Line_P2_Begin----------------
template<typename NT>
class Line_P2
{
private:
    NT _X, _Y, _W;              // Xx+Yy+Ww=0
public:
    Line_P2() : _X(1), _Y(0), _W(0) {}
    Line_P2(const Point_P2<NT>& source, const Point_P2<NT>& target)
    {
        _X = + determinant(source.hy(), source.hw(),  target.hy(), target.hw());
        _Y = - determinant(source.hx(), source.hw(),  target.hx(), target.hw());
        _W = + determinant(source.hx(), source.hy(),  target.hx(), target.hy());
    }

    bool is_incident(const Point_P2<NT>& p) const
    {
        return inner_product(_X, _Y, _W,  p.hx(), p.hy(), p.hw()) == 0;
    }
//----------------Line_P2_End----------------

    Line_P2(const NT & X, const NT & Y, const NT & W)
        : _X(X), _Y(Y), _W(W)
    {}

    bool operator==(const Line_P2<NT>& L) const {
        return (this == &L) ||
            are_dependent(_X, _Y, _W, L._X, L._Y, L._W);
    }

    NT X() const { return _X; }
    NT Y() const { return _Y; }
    NT W() const { return _W; }

    friend ostream& operator<< <>(ostream& os, const Line_P2<NT>& seg);
};

template<typename NT>
ostream& operator<<(ostream& os, const Line_P2<NT>& L)
{
    return os << L._X << " " << L._Y << " " << L._W << "  ";
}

#endif // LINE_P2_H
