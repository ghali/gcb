/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "view_e2_types.h"

//----------------View_E2_Begin----------------
template<typename NT, typename Material>
class View_E2
{
public:

    // Types for scene
    typedef std::pair<Triangle_E2<NT>, Material >  Triangle_and_material;
    typedef std::vector<Triangle_and_material >  Scene;

    // Types for scene as BSP tree
    typedef BSP_E2< NT, Material, char >  BSP_geometry_E2;
    typedef typename Geometry_E2<NT>::Convex_polytope  Convex_polygon_d;
    typedef typename Geometry_E2<NT>::Sub_hyperplane  segment_d;
    typedef BSP_node< BSP_geometry_E2, Material, char >  BSP_node_E2;
    typedef typename BSP_node_E2::Boundary_list  Boundary_list;

    // Types for view tree
    typedef BSP_S1< NT, char, Material >  BSP_geometry_S1;
    typedef typename Geometry_S1<NT>::Convex_polytope  BSP_S1_segment_d;
    typedef typename Geometry_S1<NT>::Sub_hyperplane  Sub_hyperplane_d;
    typedef BSP_node< BSP_geometry_S1, char, Material >  BSP_node_S1;
    typedef typename BSP_node_S1::Interior_list  Interior_list;
//----------------View_E2_End----------------

private:

    BSP_node_E2 tree;
    Boundary_list front_to_back_list;

    BSP_node_S1 view_tree;
    Interior_list view_segments;

public:

//----------------get_depth_order_Begin----------------
    void
    get_depth_order(
                    const Scene & triangles, 
                    const Bbox_E2<NT> & bbox,
                    const Point_E2<NT> & observer)
    {
        typedef typename Scene::const_iterator Scene_CI;
        for( Scene_CI ti = triangles.begin(); ti != triangles.end(); ++ti )
            // auto promotion of ti->first
            tree.boolean_union( ti->first, ti->second, 0 );

        const Convex_polygon_d initial_convex_polytope(bbox);

        front_to_back_list = tree.get_boundary(
                                               initial_convex_polytope,
                                               observer );
    }
//----------------get_depth_order_End----------------

//----------------determine_view_Begin----------------
    void
    determine_view(
                   const Boundary_list & front_to_back_list,
                   const Point_E2<NT> & observer )
    {
        typedef typename Boundary_list::const_iterator Segment_CI;
        for( Segment_CI si = front_to_back_list.begin();
             si != front_to_back_list.end(); ++si )
        {
            Point_S1< NT > src( observer, si->first.source() );
            Point_S1< NT > tgt( observer, si->first.target() );

            BSP_S1_segment_d s( src, tgt );

            view_tree.boolean_union( s, 0, si->second );
        }
    }
//----------------determine_view_End----------------

public:

//----------------View_E2_constructor_Begin----------------
    View_E2(
            const Scene & triangles,
            const Bbox_E2<NT> & bbox,
            const Point_E2<NT> & observer)
    {
        get_depth_order( triangles, bbox, observer );
        determine_view( front_to_back_list, observer );

        const BSP_S1_segment_d S1(S1_FULL);
        view_segments = view_tree.get_convex_polytopes(S1);
    }
//----------------View_E2_constructor_End----------------

    std::pair<Set_membership, Material>
    classify( const Point_S1<NT>& P ) const
    {
        return view_tree.classify(P);
    }

    Interior_list get_view_segments() const
    {
        return view_segments;
    }
};
