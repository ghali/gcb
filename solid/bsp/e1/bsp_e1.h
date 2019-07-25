/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef BSP_E1_H
#define BSP_E1_H

#include "geometry/E1/geometry_e1.h"

#include "geometry/free/splitting/1D/splitting_e1.h"

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
class BSP_node;

template<typename NT,
         typename Boundary_attributes,
         typename Interior_attributes>
class BSP_E1 : public Geometry_E1<NT>
{
public:

    typedef Geometry_E1<NT>                            Geometry;

    typedef typename Geometry_E1<NT>::Point            Point;
    typedef typename Geometry_E1<NT>::Hyperplane       Hyperplane;
    typedef typename Geometry_E1<NT>::Convex_polytope  Convex_polytope;


    typedef Point_E1<NT>          Sub_hyperplane;

    typedef BSP_E1<NT, Boundary_attributes, Interior_attributes> BSP_geometry;
    typedef BSP_node<BSP_geometry, Boundary_attributes, Interior_attributes>   BSP_node_E1;

public:
    static void build_subtree( BSP_node_E1 * current_node,
                               const Convex_polytope& I,
                               const Boundary_attributes& _boundary_attributes,
                               const Interior_attributes& _interior_attributes,
                               bool reverse_space = false )
    // assume operation is union and reverse_space is false on first reading
    {
        if( I.is_source_closed() )
            if( I.is_target_closed() ) {
                // We choose the subtree to be rooted at the target (left-heavy)
                // Suggested drawing: negative_child on the left
                current_node->set_interior_node( I.target(), _boundary_attributes );

                current_node->negative_child = new BSP_node_E1( I.source(), _boundary_attributes );

                current_node->positive_child = new BSP_node_E1( reverse_space, _interior_attributes );
                current_node->negative_child->positive_child = new BSP_node_E1( !reverse_space, _interior_attributes );
                current_node->negative_child->negative_child = new BSP_node_E1(  reverse_space, _interior_attributes );
            }
            else {
                current_node->set_interior_node( I.source(), _boundary_attributes );
                current_node->positive_child = new BSP_node_E1( !reverse_space, _interior_attributes ); // right - P > 0
                current_node->negative_child = new BSP_node_E1(  reverse_space, _interior_attributes );
            }
        else
            if( I.is_target_closed() ) {
                current_node->set_interior_node( I.target(), _boundary_attributes );
                current_node->positive_child = new BSP_node_E1(  reverse_space, _interior_attributes ); // left - P > 0
                current_node->negative_child = new BSP_node_E1( !reverse_space, _interior_attributes );
            }
            else
                current_node->set_leaf_node( !reverse_space, _interior_attributes );
    }
};

#endif // BSP_E1_H
