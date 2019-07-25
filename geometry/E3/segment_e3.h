/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_E3_H
#define SEGMENT_E3_H

#include "geometry/E3/point_e3.h"
#include "geometry/E3/line_e3.h"

template<typename NT>
class Segment_E3;
template<typename NT>
class Segment_T3;

template<typename NT>
ostream& operator<<(ostream& os, const Segment_E3<NT>& seg);

template<typename NT>
class Segment_E3
{
private:
    Point_E3<NT> src;         // first or source point of line segment
    Point_E3<NT> tgt;         // second or target point of line segment
public:
    typedef NT NumberType;
    typedef Segment_T3<NT> T3_equivalent;

    Segment_E3() : src(), tgt() {}
    
    Segment_E3(const Point_E3<NT>& src, const Point_E3<NT>& tgt): src(src), tgt(tgt)
    {}

    const Point_E3<NT>& source() const { return src; }
    const Point_E3<NT>& target() const { return tgt; }

    Line_E3<NT> getLine_E3() const { return Line_E3<NT>(src, tgt); }

    bool operator==(const Segment_E3<NT>& L) const {
        return (this == &L) ||
            (src == L.src && tgt == L.tgt);
    }

    bool operator!=(const Segment_E3<NT>& L) const {
        return ! operator==(L);
    }

    friend ostream& operator<< <>(ostream& os, const Segment_E3<NT>& seg);
};

template<typename NT>
ostream& operator<<(ostream& os, const Segment_E3<NT>& seg)
{
    return os << seg.src << "--" << seg.tgt;
}

#endif // SEGMENT_E3_H
