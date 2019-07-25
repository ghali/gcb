/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RAY_E2_H
#define RAY_E2_H

typedef<typename NT>
class Ray_E2
{
private:
    Point_E2<NT>        _source;
    Direction_E2<NT> _direction;
public:
    Ray_E2(const Point_E2<NT>& source, const Direction_E2<NT>& direction)
        : _source(source), _direction(direction)
    {}

    Point_E2<NT> source() const { return _source; }
    Direction_E2<NT> direction() const { return _direction; }
};

#endif // RAY_E2_H
