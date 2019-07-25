/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef BSP_NODE_H
#define BSP_NODE_H

#include "misc/orientation.h"

#include "geometry/free/splitting/Splitter.h"

#include <list>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>
using std::endl;

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
class BSP_node;

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
ostream & operator<< (ostream & os,
                      const BSP_node<BSP_geometry,
                      Boundary_attributes,
                      Interior_attributes> & N);

//----------------BSP_node_decl_Begin----------------
template<
    typename BSP_geometry,
    typename Boundary_attributes,
    typename Interior_attributes>
class BSP_node
{
    typedef typename BSP_geometry::Geometry         Geometry;

    typedef typename BSP_geometry::Point            Point;
    typedef typename BSP_geometry::Hyperplane       Hyperplane;
    typedef typename BSP_geometry::Convex_polytope  Convex_polytope;
    typedef typename BSP_geometry::Sub_hyperplane   Sub_hyperplane;

    typedef BSP_node<BSP_geometry, Boundary_attributes, Interior_attributes> My_BSP_node;
//----------------BSP_node_decl_End----------------


    // BSP_geometry must provide the following three functions:

    // static void
    // build_subtree( BSP_node_E2 * current_node,
    //                const BSP_E2_convex_polygon<NT> & P,
    //                const Boundary_attributes & boundary_attributes,
    //                const Interior_attributes & interior_attributes,
    //                bool reverseSpace = false )

    // static void
    // BSP_geometry::split( const BSP_convex_polytope & o,
    //                      const Hyperplane p,
    //                      BSP_convex_polytope & positive_part,
    //                      BSP_convex_polytope & negative_part)

    // static void 
    // BSP_geometry::construct_sub_hyperplane(
    //         const Hyperplane & hyperplane,
    //         const BSP_convex_polytope & positive_convex_polytope,
    //         Sub_hyperplane & sub_hyperplane);

public:

//----------------BSP_node_data_members_Begin----------------
    // hyperplane and boundary_attributes are valid for interior nodes only.
    Hyperplane hyperplane;
    Boundary_attributes boundary_attributes;

    // cell_is_occupied and interior_attributes are valid for leaf nodes only.
    bool cell_is_occupied;
    Interior_attributes interior_attributes;

    BSP_node * positive_child;
    BSP_node * negative_child;
//----------------BSP_node_data_members_End----------------

public:

    BSP_node( bool _cell_is_occupied = false,
              const Interior_attributes & _interior_attributes = Interior_attributes() ) :
        cell_is_occupied(_cell_is_occupied),
        positive_child(NULL), negative_child(NULL)
    {
        interior_attributes = cell_is_occupied ? _interior_attributes : Interior_attributes();
    }

    BSP_node( Hyperplane s,
              const Boundary_attributes & _boundary_attributes = Boundary_attributes() ) :
        hyperplane(s),
        boundary_attributes(_boundary_attributes),
        positive_child(NULL), negative_child(NULL)
    {}

    BSP_node( const BSP_node & N ) :
        hyperplane(N.hyperplane),
        boundary_attributes(N.boundary_attributes),
        cell_is_occupied(N.cell_is_occupied),
        interior_attributes(N.interior_attributes)
    {
        positive_child = new My_BSP_node( N.positive_child );
        negative_child = new My_BSP_node( N.negative_child );
    }

    BSP_node( const Convex_polytope & obj,
              const Boundary_attributes & _boundary_attributes,
              const Interior_attributes & _interior_attributes ) :
        boundary_attributes( _boundary_attributes ),
        cell_is_occupied(false),
        interior_attributes( Interior_attributes() ),
        positive_child(NULL), negative_child(NULL)
    {
        this->boolean_union(obj, boundary_attributes, _interior_attributes);
    }

    virtual ~BSP_node()
    {
        if(positive_child)
            delete positive_child;
        if(negative_child)
            delete negative_child;
    }

    bool is_leaf() const { return !positive_child && !negative_child; }

    void set_interior_node( const Hyperplane & s,
                            const Boundary_attributes & a = Boundary_attributes() )
    {
        hyperplane = s;
        boundary_attributes = a;
    }

    void set_leaf_node( bool _cell_is_occupied = false,
                        const Interior_attributes & i = Interior_attributes() )
    {
        cell_is_occupied = _cell_is_occupied;
        interior_attributes = cell_is_occupied ? i : Interior_attributes();
    }

    bool is_empty() const
    {
        if( !is_leaf() ) {
            bool positive_is_empty = true;
            bool negative_is_empty = true;

            if( positive_child )
                positive_is_empty = positive_child->is_empty();

            if( negative_child )
                negative_is_empty = negative_child->is_empty();

            return positive_is_empty && negative_is_empty;
        }
        else
            return !cell_is_occupied;
    }

    bool is_full() const
    {
        if( !is_leaf() ) {
            bool positive_is_full = true;
            bool negative_is_full = true;

            if( positive_child )
                positive_is_full = positive_child->is_full();

            if( negative_child )
                negative_is_full = negative_child->is_full();

            return positive_is_full && negative_is_full;
        }
        else
            return cell_is_occupied;
    }

//---------------------------------------------------
// Boolean operations between a tree (*this node) and a BSP_convex_polytope
//----------------boolean_union_Begin----------------
    void boolean_union(
                       const Convex_polytope & polytope,
                       const Boundary_attributes & _b_attr,
                       const Interior_attributes & _i_attr )
    {
        if( !is_leaf() ) {
            Convex_polytope positive_part, negative_part;
            split<Geometry>( polytope, hyperplane, positive_part, negative_part );
            if( !positive_part.is_empty() )
                positive_child->boolean_union( positive_part, _b_attr, _i_attr );
            if( !negative_part.is_empty() )
                negative_child->boolean_union( negative_part, _b_attr, _i_attr );
        }
        else
            if( cell_is_occupied )
                ;               // do nothing
            else
                BSP_geometry::build_subtree( this, polytope, _b_attr, _i_attr );
    }
//----------------boolean_union_End----------------

//----------------boolean_intersection_Begin----------------
    void boolean_intersection(
                              const Convex_polytope & polytope,
                              const Boundary_attributes & _b_attr )
    {
        if( !is_leaf() ) {
            Convex_polytope positive_part, negative_part;
            split<Geometry>( polytope, hyperplane, positive_part, negative_part );
            if( positive_part.is_empty() ) {
                delete positive_child;
                positive_child = new BSP_node(false);
            }
            else
                positive_child->boolean_intersection( positive_part, _b_attr );
            if( negative_part.is_empty() ) {
                delete negative_child;
                negative_child = new BSP_node(false);
            }
            else
                negative_child->boolean_intersection( negative_part, _b_attr );
        }
        else
            if( cell_is_occupied )
                BSP_geometry::build_subtree( this, polytope, _b_attr, interior_attributes );
        //  else
        //      ;                do nothing
    }
//----------------boolean_intersection_End----------------

//----------------boolean_difference_Begin----------------
    void boolean_difference(
                            const Convex_polytope & polytope,
                            const Boundary_attributes & _b_attr )
    {
        if( !is_leaf() ) {
            Convex_polytope positive_part, negative_part;
            split<Geometry>( polytope, hyperplane, positive_part, negative_part );
            if( !positive_part.is_empty() )
                positive_child->boolean_difference( positive_part, _b_attr );
            if( !negative_part.is_empty() )
                negative_child->boolean_difference( negative_part, _b_attr );
        }
        else
            if( cell_is_occupied )
                BSP_geometry::build_subtree( this, polytope, _b_attr,
                                             interior_attributes, true /*reverse space*/ );
        //  else
        //      ;          do nothing (implicitly discard polytope)
    }
//----------------boolean_difference_End----------------

    // List of Sub_hyperplanes
    // E1: Point (one splitting point)
    // E2: Segment (line + two splitting lines)
    // E3: Polygon (plane + a set of splitting planes)
    // S1: Point (one splitting point)
    // S2: Segment (circle + two splitting circles)


    typedef std::list< std::pair<Sub_hyperplane, Boundary_attributes> > Boundary_list;

    Boundary_list
    get_boundary( const Convex_polytope & current_cell,
                  const Point & observer,
                  bool also_get_backfaces = false)
    {
        Boundary_list L;
        boundary( L, current_cell, observer, also_get_backfaces );
        return L;
    }

private:
//----------------boundary_Begin----------------
    void boundary(
                  Boundary_list & ftb,
                  const Convex_polytope & current_cell,
                  const Point & observer,
                  bool also_get_backfaces )
    {
        if( is_leaf() )
            return;

        const Oriented_side s = oriented_side(hyperplane, observer);

        Convex_polytope p_polytope, n_polytope;
        split<Geometry>( current_cell, hyperplane, p_polytope, n_polytope );

        if( s == ON_POSITIVE_SIDE ) {
            if( positive_child )
                positive_child->boundary(ftb, p_polytope, observer, also_get_backfaces);
            Sub_hyperplane sub_hyperplane;
            BSP_geometry::construct_sub_hyperplane(hyperplane, p_polytope, sub_hyperplane);
            ftb.push_back( std::make_pair(sub_hyperplane, boundary_attributes) );
            if( negative_child )
                negative_child->boundary(ftb, n_polytope, observer, also_get_backfaces);
        }
        else if( s == ON_NEGATIVE_SIDE ) {
            if( negative_child )
                negative_child->boundary(ftb, n_polytope, observer, also_get_backfaces);
            if( also_get_backfaces ) {
                Sub_hyperplane sub_hyperplane;
                BSP_geometry::construct_sub_hyperplane(hyperplane, n_polytope, sub_hyperplane);
                ftb.push_back( std::make_pair(sub_hyperplane, boundary_attributes) );
            }
            if( positive_child )
                positive_child->boundary(ftb, p_polytope, observer, also_get_backfaces);
        }
        else { // ON_ORIENTED_BOUNDARY
            // either order will do
            if( negative_child )
                negative_child->boundary(ftb, n_polytope, observer, also_get_backfaces);
            if( positive_child )
                positive_child->boundary(ftb, p_polytope, observer, also_get_backfaces);
        }
    }
//----------------boundary_End----------------
public:
//----------------interior_attr_Begin----------------
    typedef std::pair<Convex_polytope,Interior_attributes> PolyAttr;
    typedef std::vector<PolyAttr> Interior_list;
//----------------interior_attr_End----------------

    Interior_list
    get_convex_polytopes( const Convex_polytope & polytope ) const
    {
        Interior_list polytope_collector;
        get_polytopes(polytope, polytope_collector);
        return polytope_collector;
    }
private:
//----------------get_polytopes_Begin----------------
    void
    get_polytopes(
                  const Convex_polytope & polytope,
                  Interior_list & collector ) const
    {
        if( is_leaf() ) {
            if( cell_is_occupied )
                collector.push_back(
                                    std::make_pair( polytope, interior_attributes) );
        }
        else {
            Convex_polytope positive_side;
            Convex_polytope negative_side;
            split<Geometry>(
                            polytope, hyperplane,
                            positive_side, negative_side );
            if( negative_child && !negative_side.is_empty() )
                negative_child->get_polytopes(
                                              negative_side,
                                              collector);
            if( positive_child && !positive_side.is_empty() )
                positive_child->get_polytopes(
                                              positive_side,
                                              collector);
        }
    }
//----------------get_polytopes_End----------------
public:
    int size() const
    {
        int positive_size = 0;
        int negative_size = 0;

        if( positive_child )
            positive_size = positive_child->size();

        if( negative_child )
            negative_size = negative_child->size();

        return 1 + positive_size + negative_size;
    }

//----------------classify_Begin----------------
    typedef std::pair<
        Set_membership,
        Interior_attributes > Classification_pair;

    Classification_pair
    classify( const Point & P ) const
    {
        if( is_leaf() )
            return std::make_pair(
                                  cell_is_occupied ? INSIDE_SET : OUTSIDE_SET,
                                  interior_attributes);
        else {
            const Oriented_side os = oriented_side( hyperplane, P );
            if( os == ON_POSITIVE_SIDE )
                return positive_child->classify( P );
            else if( os == ON_NEGATIVE_SIDE )
                return negative_child->classify( P );
            else {
                const Classification_pair pos = positive_child->classify( P );
                const Classification_pair neg = negative_child->classify( P );
                if( pos == neg )
                    return pos;
                else if( pos.first == neg.first )
                    return std::make_pair( pos.first, Interior_attributes() );
                else
                    return std::make_pair( ON_SET_BOUNDARY, Interior_attributes() );
            }
        }
    }
//----------------classify_End----------------

    void print( ostream & os, std::string prefix = "" ) const
    {
        if(is_leaf())
            os << prefix << "Leaf Flag: " << cell_is_occupied << endl;
        else {
            os << prefix << "Hyperplane: " << hyperplane << endl;
            prefix += "    ";
            os << prefix << "Positive Child: ";
            positive_child->print( os, prefix );
            os << prefix << "Negative Child: ";
            negative_child->print( os, prefix );
        }
    }

    friend ostream & operator<< <>(ostream & os, const My_BSP_node & N);

    void boolean_union( const BSP_node & N )
    {
        // ...
        assert(false);
    }

    BSP_node * get_negative_child() const { return negative_child; }
    BSP_node * get_positive_child() const { return positive_child; }
    bool is_cell_occupied() const { return cell_is_occupied; } // precondition: node is leaf
};

template<typename BSP_geometry,
         typename Boundary_attributes,
         typename Interior_attributes>
ostream & operator<< (ostream & os, const BSP_node<BSP_geometry, Boundary_attributes, Interior_attributes> & N)
{
    N.print(os);
    return os;
}

#endif // BSP_NODE_H
