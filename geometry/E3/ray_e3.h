/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RAY_E3_H
#define RAY_E3_H

typedef<typename T>
class Ray_E3
{
private:
    Point_E3<T>        _source;
    Direction_E3<T> _direction;
public:
    Ray_E3(const Point_E3<T>& source, const Direction_E3<T>& direction)
        : _source(source), _direction(direction)
    {}

    Point_E3<T> source() const { return _source; }
    Direction_E3<T> direction() const { return _direction; }
};

#endif // RAY_E3_H
