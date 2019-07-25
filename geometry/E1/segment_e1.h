/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_E1_H
#define SEGMENT_E1_H

#include <cassert>

#include "geometry/E1/point_e1.h"

template<typename NT>
class Segment_E1;

template<typename NT>
ostream & operator<<(ostream & os, const Segment_E1<NT> & seg);

template<typename NT>
class Segment_E1
{
private:
    Point_E1<NT> src;
    Point_E1<NT> tgt;
public:
    Segment_E1() : src(), tgt() {}

    Segment_E1(const Point_E1<NT> & src, const Point_E1<NT> & tgt): src(src), tgt(tgt)
    {
        // Notice that:
        //   1- In keeping with setting the orientation of S1,
        //      segments in E1 also have an orientation (src < tgt must be satisfied)
        //   2- The assertion below does not invoke oriented_side in predicate_e1.h to
        //      avoid splitting that file into an interface and an implementation.
        assert(src.x() < tgt.x());
    }

    const Point_E1<NT> & source() const { return src; }
    const Point_E1<NT> & target() const { return tgt; }

    bool operator==(const Segment_E1<NT> & seg) const {
        return (this == &seg) ||
            ((src == seg.src) && (tgt == seg.tgt));
    }

    bool operator!=(const Segment_E1<NT> & seg) const {
        return ! operator==(seg);
    }

    friend ostream & operator<< <>(ostream & os, const Segment_E1<NT> & seg);
};

template<typename NT>
ostream & operator<<(ostream & os, const Segment_E1<NT> & seg)
{
    return os << seg.src << "--" << seg.tgt;
}

#endif // SEGMENT_E1_H
