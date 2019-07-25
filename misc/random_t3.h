/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef RANDOM_T3_H
#define RANDOM_T3_H

#include "geometry/T3/point_T3.h"
#include "geometry/T3/vector_T3.h"
#include "geometry/T3/transformation_T3.h"

// srand48(0) must be called explicitly on cygwin before drand48 is used.

template<typename NT>
void
set_to_random( Point_T3<NT>& P )
{
    NT x = NT(rand()/(RAND_MAX+1.0));
    NT y = NT(rand()/(RAND_MAX+1.0));
    NT z = NT(rand()/(RAND_MAX+1.0));
    NT w = static_cast<NT>(1);

    P = Point_T3<NT>(x,y,z,w);
}

template<typename NT>
void
set_to_random( Vector_T3<NT>& V )
{
    NT x = NT(rand()/(RAND_MAX+1.0));
    NT y = NT(rand()/(RAND_MAX+1.0));
    NT z = NT(rand()/(RAND_MAX+1.0));
    NT w = static_cast<NT>(1);

    V = Vector_T3<NT>(x,y,z,w);
}

template<typename NT>
void
set_to_random( Transformation_T3<NT>& T )
{
    NT m00 = NT(rand()/(RAND_MAX+1.0));
    NT m01 = NT(rand()/(RAND_MAX+1.0));
    NT m02 = NT(rand()/(RAND_MAX+1.0));
    NT m03 = NT(rand()/(RAND_MAX+1.0));

    NT m10 = NT(rand()/(RAND_MAX+1.0));
    NT m11 = NT(rand()/(RAND_MAX+1.0));
    NT m12 = NT(rand()/(RAND_MAX+1.0));
    NT m13 = NT(rand()/(RAND_MAX+1.0));

    NT m20 = NT(rand()/(RAND_MAX+1.0));
    NT m21 = NT(rand()/(RAND_MAX+1.0));
    NT m22 = NT(rand()/(RAND_MAX+1.0));
    NT m23 = NT(rand()/(RAND_MAX+1.0));

    NT m30 = NT(rand()/(RAND_MAX+1.0));
    NT m31 = NT(rand()/(RAND_MAX+1.0));
    NT m32 = NT(rand()/(RAND_MAX+1.0));
    NT m33 = NT(rand()/(RAND_MAX+1.0));

    T = Transformation_T3<NT>(m00, m01, m02, m03,
                              m10, m11, m12, m13,
                              m20, m21, m22, m23,
                              m30, m31, m32, m33);
}

#endif // RANDOM_T3_H
