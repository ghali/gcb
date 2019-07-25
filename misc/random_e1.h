/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */
#ifndef RANDOM_E1_H
#define RANDOM_E1_H

#include "geometry/E1/point_e1.h"

// srand48(0) must be called explicitly on cygwin before drand48 is used.

template<typename NT>
void
set_to_random( Point_E1<NT>& P )
{
    NT x = NT(rand()/(RAND_MAX+1.0));
    P = Point_E1<NT>(x);
}

#endif // RANDOM_E1_H
