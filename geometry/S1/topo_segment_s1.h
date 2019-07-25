/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TOPO_SEGMENT_S1_H
#define TOPO_SEGMENT_S1_H

#include <cassert>

#include "geometry/S1/point_s1.h"
#include "geometry/S1/segment_s1.h"
#include "geometry/S1/predicates_s1.h"

// BSP_S1_segment is a model for BSP_geometry::BSP_convex_polytope

enum S1_state { S1_EMPTY, S1_FULL };

//----------------BSP_S1_segment_Begin----------------
template<typename NT>
class Topo_segment_S1
{
    bool is_empty_var;
    bool is_full_var;

    Segment_S1<NT> segment;
    bool   source_is_closed, target_is_closed;
//----------------BSP_S1_segment_End----------------

public:
    Topo_segment_S1(S1_state s = S1_EMPTY)
        : source_is_closed(false), target_is_closed(false) // irrelevant here
    {
        if( s == S1_EMPTY ) {
            is_empty_var = true;
            is_full_var = false;
        }
        else if( s == S1_FULL ) {
            is_empty_var = false;
            is_full_var = true;
        }            
    }

    Topo_segment_S1(const Segment_S1<NT>& s)
        : is_empty_var(false),
          is_full_var(false),
          segment(s),
          source_is_closed(true), target_is_closed(true)
    {
        const Oriented_side o = oriented_side( s.source(), s.target() );
        assert( o == ON_POSITIVE_SIDE || o == ON_ORIENTED_BOUNDARY );
    }
    Topo_segment_S1( const Point_S1<NT>& L, const Point_S1<NT>& R,
                    bool s = true, bool t = true)
        : is_empty_var(false),
          is_full_var(false),
          segment(L, R),
          source_is_closed(s), target_is_closed(t)
    {
        const Oriented_side o = oriented_side( L, R );
        assert( o == ON_POSITIVE_SIDE || o == ON_ORIENTED_BOUNDARY );
    }

    bool is_empty() const { return is_empty_var; }
    void set_empty(bool e) { is_empty_var = e; }

    bool is_full() const { return is_full_var; }

    Segment_S1<NT> get_Segment_S1() const { return segment; }
    Point_S1<NT> source() const { return segment.source(); }
    Point_S1<NT> target() const { return segment.target(); }

    bool is_source_closed() const { return source_is_closed; }
    bool is_target_closed() const { return target_is_closed; }

    void set_source_closed(bool c) { source_is_closed = c; }
    void set_target_closed(bool c) { target_is_closed = c; }
};

#endif // TOPO_SEGMENT_S1_H
