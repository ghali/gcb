/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geom_types_s1.h"

#include <cassert>
#include <iostream>
#include <map>

const Point_S1d A( 1, 1);
const Point_S1d B(-1, 1);
const Point_S1d C(-1,-1);
const Point_S1d D( 1,-1);

const Convex_polytope_S1d AB( A, B );
const Convex_polytope_S1d BC( B, C );
const Convex_polytope_S1d CD( C, D );

void test_size()
{
    // Test size of resulting tree to confirm open intervals are handled properly 
    BSP_node_S1 N;
    N.boolean_union( AB, BA1, IA1 );

    assert( N.hyperplane == B );
    assert( N.boundary_attributes == BA1 );
    assert( N.negative_child->hyperplane == A );
    assert( N.negative_child->boundary_attributes == BA1 );
    assert( N.size() == 5 );

    N.boolean_union( BC, BA2, IA2 );

    assert( N.hyperplane == B );
    assert( N.negative_child->hyperplane == A );
    assert( N.positive_child->hyperplane == C );
    //assert( N.positive_child->boundary_attributes == BA2 );
    assert( N.size() == 7 );
}

void test_boolean_union()
{
    {
        BSP_node_S1 N;
        N.boolean_union( BC, BA2, IA2 );
        assert( N.size() == 5 );
        N.boolean_union( AB, BA1, IA1 ); // neither endpoint of AB is added to the tree
        assert( N.size() == 5 );
    }
    {
        BSP_node_S1 N;
        N.boolean_union( AB, BA1, IA1 );
        N.boolean_union( CD, BA2, IA2 );
        assert( N.size() == 7 ); // target of CD is not added to the tree
        N.boolean_union( BC, BA3, IA3 );
        assert( N.size() == 7 ); // neither endpoint of BC is added to the tree
    }
}

void test_point_containment()
{
    const Point_S1d A( 2, 2);
    const Point_S1d B(-2, 2);
    const Point_S1d C(-2,-2);
    const Point_S1d D( 2,-2);

    const Convex_polytope_S1d AB( A, B );
    const Convex_polytope_S1d BC( B, C );
    const Convex_polytope_S1d CD( C, D );
    {
        BSP_node_S1 N;
        N.boolean_union( AB, BA1, IA1 );

        assert( N.hyperplane == B );
        assert( N.negative_child->hyperplane == A );

        const Point_S1d XP( 1,0);
        const Point_S1d YP( 0,1);
        const Point_S1d XN(-1,0);
        const Point_S1d YN(0,-1);

        const Point_S1d XPYP( 1, 1);
        const Point_S1d XNYP(-1, 1);
        const Point_S1d XNYN(-1,-1);
        const Point_S1d XPYN( 1,-1);

        assert( N.classify( XP   ).first == OUTSIDE_SET );
        assert( N.classify( XPYP ).first == ON_SET_BOUNDARY );
        assert( N.classify( YP   ) == std::make_pair(INSIDE_SET, IA1) );
        assert( N.classify( XNYP ).first == ON_SET_BOUNDARY );
        assert( N.classify( XN   ).first == OUTSIDE_SET );

        N.boolean_union( CD, BA2, IA2 );

        assert( N.hyperplane == B );
        assert( N.negative_child->hyperplane == A );
        assert( N.positive_child->hyperplane == C );

        assert( N.classify( XN   ).first == OUTSIDE_SET );
        assert( N.classify( C    ).first == ON_SET_BOUNDARY );
        assert( N.classify( YN   ) == std::make_pair(INSIDE_SET, IA2) );
        assert( N.classify( XPYN ).first == ON_SET_BOUNDARY );
        assert( N.classify( XP   ).first == OUTSIDE_SET );

        N.boolean_union( BC, BA3, IA3 );

        assert( N.classify( YP   ).first == INSIDE_SET );
        assert( N.classify( XNYP ).first == INSIDE_SET );
        assert( N.classify( XN   ) == std::make_pair(INSIDE_SET, IA3) );
        assert( N.classify( XNYN ).first == INSIDE_SET );
        assert( N.classify( YN   ).first == INSIDE_SET );
    }
}

void test_is_empty()
{
    Point_S1d A( 1, 1);
    Point_S1d B(-1, 1);
    Point_S1d C(-1,-1);
    Point_S1d D( 1,-1);

    Convex_polytope_S1d AB( A, B );
    Convex_polytope_S1d BC( B, C );
    Convex_polytope_S1d CD( C, D );
    Convex_polytope_S1d DA( D, A );
    {
        BSP_node_S1 N;
        assert( N.is_empty() );
        assert( !N.is_full() );

        N.boolean_union( AB, BA1, IA1 );
        assert( !N.is_empty() );
        assert( !N.is_full() );

        N.boolean_union( BC, BA2, IA2 );
        assert( !N.is_empty() );
        assert( !N.is_full() );

        N.boolean_union( CD, BA3, IA3 );
        assert( !N.is_empty() );
        assert( !N.is_full() );

        N.boolean_union( DA, BA4, IA4 );
        assert( !N.is_empty() );
        assert( N.is_full() );
    }
}

void test_get_convex_polytopes()
{
    const Point_S1d A(4, 2), B( 0, 2);
    const Point_S1d D(1, 4), E(-5, 4);
    const Convex_polytope_S1d AB(A,B), DE(D,E);


    BSP_node_S1 N;
    N.boolean_union( AB, BA1, IA1 );
    N.boolean_union( DE, BA2, IA2 );

    Convex_polytope_S1d S1(S1_FULL);
    BSP_node_S1::Interior_list L = N.get_convex_polytopes(S1);

    assert( L.size() == 2 );

    BSP_node_S1::Interior_list::const_iterator ci = L.begin();
    assert( ci->first.source() == A );
    assert( ci->first.target() == B );
    assert( ci->second == IA1 );

    ci++;
    assert( ci->first.source() == B );
    assert( ci->first.target() == E );
    assert( ci->second == IA2 );

    ci++;
    assert( ci == L.end() );
}

int main()
{
    test_size();
    test_boolean_union();
    test_point_containment();
    test_is_empty();
    test_get_convex_polytopes();
}
