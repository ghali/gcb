/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef PREDICATES_E3_H
#define PREDICATES_E3_H

#include "geometry/E3/segment_e3.h"
#include "geometry/E3/plane_e3.h"
#include "geometry/E3/dominant_e3.h"

#include "misc/orientation.h"
#include "misc/determinant.h"

//----------------------------------------------------------------
template<typename NT>
Oriented_side
oriented_side(const Plane_E3<NT>& T,
              const Point_E3<NT>& P)
{
    Point_E3<NT> O(0,0,0);
    NT s = dot_product(T.get_vector_e3(), (P-O)) + T.get_d();

    return enum_Oriented_side(s);
}

//----------------------------------------------------------------
template<typename T>
Dominant_E3
dominant(const Vector_E3<T>& V)
{
    return dominant(V.x(), V.y(), V.z());
}
//----------------------------------------------------------------
template<typename T>
Dominant_E3
dominant(const Segment_E3<T>& segment)
{
    T dx = segment.target().x() - segment.source().x();
    T dy = segment.target().y() - segment.source().y();
    T dz = segment.target().z() - segment.source().z();

    return dominant(dx, dy, dz);
}

template<typename T>
Dominant_E3
least_dominant(const Vector_E3<T>& v)
{
    return least_dominant(v.x(), v.y(), v.z());
}

template<typename NT>
bool
are_linearly_dependent(const Vector_E3<NT>& v1,
                       const Vector_E3<NT>& v2)
{
    return are_dependent(v1.x(), v1.y(), v1.z(),
                         v2.x(), v2.y(), v2.z());
}

#endif // PREDICATES_E3_H
