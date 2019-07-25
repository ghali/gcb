/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <cassert>
#include <cmath>
#include "geometry/E3/vector_e3.h"

template<typename NT>
void
normalize( const Vector_E3<NT>& v, Vector_E3<double>& vn )
{
    double dx = double(v.x());
    double dy = double(v.y());
    double dz = double(v.z());
    assert( dx != 0 || dy != 0 || dz != 0 );
    double dd = dx*dx + dy*dy + dz*dz;
    double d = std::sqrt(dd);

    vn = Vector_E3<double>(dx/d, dy/d, dz/d);
}

template<typename NT>
void
normalize( const Vector_E3<NT>& v, Vector_E3<float>& vn )
{
    float dx = float(v.x());
    float dy = float(v.y());
    float dz = float(v.z());
    assert( dx != 0 || dy != 0 || dz != 0 );
    float dd = dx*dx + dy*dy + dz*dz;
    float d = std::sqrt(dd);

    vn = Vector_E3<float>(dx/d, dy/d, dz/d);
}
