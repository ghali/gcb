/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef TOPO_SEGMENT_E1_H
#define TOPO_SEGMENT_E1_H

#include <cassert>

#include "geometry/E1/point_e1.h"
#include "geometry/E1/segment_e1.h"
#include "geometry/E1/predicates_e1.h"

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
class BSP_node;

// Topo_segment_E1 is a model for BSP_geometry::BSP_convex_polytope

//----------------BSP_E1_segment_Begin----------------
template<typename NT>
class Topo_segment_E1
{
    bool is_empty_var;

    Segment_E1<NT> segment;
    bool   source_is_closed, target_is_closed;
//----------------BSP_E1_segment_End----------------

public:
    Topo_segment_E1() { is_empty_var = true; }
    Topo_segment_E1(const Segment_E1<NT> & seg,
                   bool s = true, bool t = true)
        : is_empty_var(false),
          segment(seg),
          source_is_closed(s), target_is_closed(t)
    {
        // The assertion confirms that:
        //   1- Segment is regular: left != right
        //   2- Segment has left < right
        assert( oriented_side( seg.source(), seg.target() ) == ON_POSITIVE_SIDE );
    }
    Topo_segment_E1( const Point_E1<NT> & L, const Point_E1<NT> & R,
                    bool s = true, bool t = true )
        : is_empty_var(false),
          segment(L, R),
          source_is_closed(s), target_is_closed(t)
    {
        assert( oriented_side( L, R ) == ON_POSITIVE_SIDE );
    }

    bool is_empty() const { return is_empty_var; }
    void set_empty(bool e) { is_empty_var = e; }

    Segment_E1<NT> get_Segment_E1() const { return segment; }
    Point_E1<NT> source() const { return segment.source(); }
    Point_E1<NT> target() const { return segment.target(); }

    bool is_source_closed() const { return source_is_closed; }
    bool is_target_closed() const { return target_is_closed; }

    void set_source_closed(bool c) { source_is_closed = c; }
    void set_target_closed(bool c) { target_is_closed = c; }
};

#endif // TOPO_SEGMENT_E1_H
