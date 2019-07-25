/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef DOMINANT_E3D_H
#define DOMINANT_E3D_H

#include "vector_e3d.h"

//----------------Dominant_E3_Enum_Begin----------------
enum Dominant_E3 { E3_POSX, E3_NEGX, E3_POSY, E3_NEGY, E3_POSZ, E3_NEGZ };
//----------------Dominant_E3_Enum_End----------------

//----------------Dominant_E3_impl_Begin----------------
Dominant_E3 dominant(double dx, double dy, double dz)
{
    const double zero = 0.0;
    double dxabs = dx >= zero ? dx : (-dx);
    double dyabs = dy >= zero ? dy : (-dy);
    double dzabs = dz >= zero ? dz : (-dz);

    if(dxabs >= dyabs && dxabs >= dzabs)
        return ((dx > zero) ? E3_POSX : E3_NEGX);
    else if(dyabs >= dzabs)
        return ((dy > zero) ? E3_POSY : E3_NEGY);
    else
        return ((dz > zero) ? E3_POSZ : E3_NEGZ);
}
//----------------Dominant_E3_impl_End----------------

#endif // DOMINANT_E3D_H
