/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RANDOM_P3_H
#define RANDOM_P3_H

#include "geometry/P3/transformation_P3.h"

// srand48(0) must be called explicitly on cygwin before drand48 is used.

template<typename NT>
void
set_to_random( Transformation_P3<NT>& T )
{
    NT m00 = static_cast<NT>(drand48());
    NT m01 = static_cast<NT>(drand48());
    NT m02 = static_cast<NT>(drand48());
    NT m03 = static_cast<NT>(drand48());

    NT m10 = static_cast<NT>(drand48());
    NT m11 = static_cast<NT>(drand48());
    NT m12 = static_cast<NT>(drand48());
    NT m13 = static_cast<NT>(drand48());

    NT m20 = static_cast<NT>(drand48());
    NT m21 = static_cast<NT>(drand48());
    NT m22 = static_cast<NT>(drand48());
    NT m23 = static_cast<NT>(drand48());

    NT m30 = static_cast<NT>(drand48());
    NT m31 = static_cast<NT>(drand48());
    NT m32 = static_cast<NT>(drand48());
    NT m33 = static_cast<NT>(drand48());

    T = Transformation_P3(m00, m01, m02, m03,
                          m10, m11, m12, m13,
                          m20, m21, m22, m23,
                          m30, m31, m32, m33);
}

#endif // RANDOM_P3_H
