/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef BSP_E2_H
#define BSP_E2_H

#include "geometry/E2/geometry_e2.h"
// #include "geometry/E2/convex_polygon_e2.h"
#include "geometry/E2/predicates_e2.h"
#include "geometry/E2/intersection_e2.h"

#include "geometry/free/splitting/2D/splitting_2.h"

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
class BSP_node;

//----------------BSP_E2_decl_Begin----------------
template<
    typename NT,
    typename Boundary_attributes,
    typename Interior_attributes>
class BSP_E2 : public Geometry_E2<NT>
{
public:

    typedef Geometry_E2<NT>                            Geometry;

    typedef typename Geometry_E2<NT>::Point            Point;
    typedef typename Geometry_E2<NT>::Hyperplane       Hyperplane;
    typedef typename Geometry_E2<NT>::Convex_polytope  Convex_polytope;
    typedef typename Geometry_E2<NT>::Sub_hyperplane   Sub_hyperplane;

    typedef BSP_E2<NT, Boundary_attributes, Interior_attributes> BSP_geometry;
    typedef BSP_node<BSP_geometry, Boundary_attributes, Interior_attributes>   BSP_node_E2;
//----------------BSP_E2_decl_End----------------
public:

    // A triangle is represented using the following subtree.             !  
    //                                                                    !  
    //                    o (splittingLine = LP[0])          node 1       !  
    //                 - / \ +                                            !  
    //                  /   \                                             !  
    //                 o     F (splittingLine = LP[1])       nodes 2, 3   !  
    //              - / \ +                                               !  
    //               /   \                                                !  
    //              o     F (splittingLine = LP[2])          nodes 4, 5   !  
    //           - / \ +                                                  !  
    //            /   \                                                   !  
    //           T     F                                     nodes 6, 7   !  
    //                                                                    !  
    //  o : interior node                                                 !  

//----------------build_subtree_Begin----------------
    static void
    build_subtree(
                  BSP_node_E2 * current_node,
                  const Convex_polytope& P,
                  const Boundary_attributes& _boundary_attributes,
                  const Interior_attributes& _interior_attributes,
                  bool reverseSpace = false )
    {
        std::vector<Segment_E2<NT> > bounding_lines = P.get_free_bounding_lines();

        if( bounding_lines.size() > 0 ) {
            typedef typename std::vector<Segment_E2<NT> >::iterator ExtSegIt;
            ExtSegIt lineIt = bounding_lines.begin();
            current_node->set_interior_node( *lineIt, _boundary_attributes );
            BSP_node_E2* current = current_node;
            if( bounding_lines.size() == 1 ) {
                current->positive_child = new BSP_node_E2( reverseSpace );
                if( reverseSpace )
                    current->positive_child->interior_attributes = _interior_attributes;
                current->negative_child = new BSP_node_E2( !reverseSpace );
                if( !reverseSpace )
                    current->negative_child->interior_attributes = _interior_attributes;
            }
            else {
                do {
                    ++lineIt;
                    current->positive_child = new BSP_node_E2( reverseSpace );
                    if( reverseSpace )
                        current->positive_child->interior_attributes = _interior_attributes;
                    current->negative_child = new BSP_node_E2(false);
                    if(lineIt != bounding_lines.end())
                        current->negative_child->set_interior_node( *lineIt, _boundary_attributes );
                    else
                        current->negative_child->set_leaf_node( !reverseSpace, _interior_attributes );
                    current = current->negative_child;
                } while( lineIt != bounding_lines.end() );
            }
        }
    }
//----------------build_subtree_End----------------


    //----------------------------------------------------------------

    static void 
    construct_sub_hyperplane( const Hyperplane& hyperplane,
                              const Convex_polytope& convex_polytope,
                              Sub_hyperplane& sub_hyperplane)
    {
        sub_hyperplane = Sub_hyperplane_E2<NT>( hyperplane, convex_polytope );
    }
};

#endif // BSP_E2_H
