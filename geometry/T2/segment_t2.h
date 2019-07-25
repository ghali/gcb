/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef SEGMENT_T2_H
#define SEGMENT_T2_H

#include "geometry/T2/point_t2.h"

template<typename T>
class Segment_T2;

template<typename T>
ostream& operator<<(ostream& os, const Segment_T2<T>& seg);

template<typename T>
class Segment_T2
{
private:
    Point_T2<T> src;         // first or source point of line segment
    Point_T2<T> tgt;         // second or target point of line segment
public:
    Segment_T2() : src(), tgt() {}

    Segment_T2(const Point_T2<T>& src, const Point_T2<T>& tgt): src(src), tgt(tgt)
    {}

    const Point_T2<T>& source() const { return src; }
    const Point_T2<T>& target() const { return tgt; }

    bool operator==(const Segment_T2<T>& seg) const
    {
        return src == seg.src && tgt == seg.tgt;
    }

    bool operator!=(const Segment_T2<T>& seg) const
    {
        return !operator==(seg);
    }

    friend ostream& operator<< <>(ostream& os, const Segment_T2<T>& seg);
};

template<typename T>
ostream& operator<<(ostream& os, const Segment_T2<T>& seg)
{
    return os << seg.src << "--" << seg.tgt;
}

#endif // SEGMENT_T2_H
