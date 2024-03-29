/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_E2_H
#define SEGMENT_E2_H

#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"

template<typename NT>
class Segment_E2;

template<typename NT>
ostream& operator<<(ostream& os, const Segment_E2<NT>& seg);

template<typename NT>
class Segment_E2
{
public:
    typedef NT              eNT;
    typedef Point_E2<NT> ePoint;
private:
    Point_E2<NT> src;        // first or source point of line segment
    Point_E2<NT> tgt;        // second or target point of line segment
public:
    Segment_E2() : src(), tgt() {}

    Segment_E2(const Point_E2<NT>& src, const Point_E2<NT>& tgt): src(src), tgt(tgt)
    {}

    const Point_E2<NT>& source() const { return src; }
    const Point_E2<NT>& target() const { return tgt; }

    Vector_E2<NT> get_Vector_E2() const { return tgt - src; }

    NT squared_length() const { 
        return squared_distance(src, tgt);
    }

    bool operator==(const Segment_E2<NT>& L) const {
        return (this == &L) ||
            (src == L.src && tgt == L.tgt);
    }

    bool operator!=(const Segment_E2<NT>& L) const {
        return ! operator==(L);
    }

    friend ostream& operator<< <>(ostream& os, const Segment_E2<NT>& seg);
};

template<typename NT>
ostream& operator<<(ostream& os, const Segment_E2<NT>& seg)
{
    return os << seg.src << " <-> " << seg.tgt;
}

#endif // SEGMENT_E2_H
