/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RANDOM_S2_H
#define RANDOM_S2_H

#include "geometry/S2/point_s2.h"

// srand48(0) must be called explicitly on cygwin before drand48 is used.

template<typename NT>
void
set_to_random( Point_S2<NT>& P )
{
    NT x, y, z;
    do {
        x = NT(2.0 * double(rand())/(RAND_MAX+1.0) - 1.0);
        y = NT(2.0 * double(rand())/(RAND_MAX+1.0) - 1.0);
        z = NT(2.0 * double(rand())/(RAND_MAX+1.0) - 1.0);
    } while( x==0 && y==0 && z==0 );
    P = Point_S2<NT>(x,y,z);
}

#endif // RANDOM_S2_H
