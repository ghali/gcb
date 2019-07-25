/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POINT_E3D_H
#define POINT_E3D_H

class Point_E3d
{
    double _x, _y, _z;
public:
    Point_E3d( double x=0, double y=0, double z=0 ) : _x(x), _y(y), _z(z) {}

    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }
};

#endif // POINT_E3D_H
