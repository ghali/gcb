/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geom_types_e1.h"

#include <cassert>
#include <iostream>
#include <map>

const Point_E1d P1(1), P2(2), P3(3), P4(4), P5(5);
const Point_E1d P6(6), P7(7), P8(8), P9(9);

const Convex_polytope_E1d S24( P2, P4 );
const Convex_polytope_E1d S46( P4, P6 );
const Convex_polytope_E1d S68( P6, P8 );

const Convex_polytope_E1d S26( P2, P6 );
const Convex_polytope_E1d S48( P4, P8 );

const Convex_polytope_E1d S28( P2, P8 );

void test_size()
{
    {
        // Test size of resulting tree to confirm open intervals are handled properly 
        BSP_node_E1 N;
        N.boolean_union( S24, BA1, IA1 );

        assert( N.hyperplane == P4 );
        assert( N.boundary_attributes == BA1 );
        assert( N.negative_child->hyperplane == P2 );
        assert( N.negative_child->boundary_attributes == BA1 );
        assert( N.size() == 5 );

        N.boolean_union( S46, BA2, IA2 );

        assert( N.hyperplane == P4 );
        assert( N.negative_child->hyperplane == P2 );
        assert( N.positive_child->hyperplane == P6 );
        assert( N.positive_child->boundary_attributes == BA2 );
        assert( N.size() == 7 ); // confirm P4 is not duplicated
    }
    {
        BSP_node_E1 N;
        N.boolean_union( S46, BA2, IA2 );
        assert( N.size() == 5 );
        N.boolean_union( S24, BA1, IA1 );
        assert( N.size() == 7 ); // confirm P4 is not duplicated
    }
    {
        BSP_node_E1 N;
        N.boolean_union( S24, BA1, IA1 );
        N.boolean_union( S68, BA2, IA2 );
        assert( N.size() == 9 );
        N.boolean_union( S46, BA3, IA3 );
        assert( N.size() == 9 ); // confirm neither P4 nor P6 is duplicated
    }
}

void test_point_containment()
{
    BSP_node_E1 N;
    N.boolean_union( S24, BA1, IA1 );

    assert( N.classify( P1 ).first == OUTSIDE_SET     );
    assert( N.classify( P2            ).first == ON_SET_BOUNDARY );

    BSP_node_E1::Classification_pair C3 = N.classify( P3 );
    assert( C3.first == INSIDE_SET      );
    assert( C3.second == IA1 );

    assert( N.classify( P4 ).first == ON_SET_BOUNDARY );
    assert( N.classify( P5 ).first == OUTSIDE_SET     );

    N.boolean_union( S68, BA2, IA2 );

    assert( N.classify( P5 ).first == OUTSIDE_SET     );
    assert( N.classify( P8 ).first == ON_SET_BOUNDARY );
    assert( N.classify( P7 ) == std::make_pair( INSIDE_SET, IA2 ) );
    assert( N.classify( P8 ).first == ON_SET_BOUNDARY );
    assert( N.classify( P9 ).first == OUTSIDE_SET     );

    N.boolean_union( S46, BA3, IA3 );

    assert( N.classify( P4 ).first == INSIDE_SET );
    assert( N.classify( P5 ) == std::make_pair( INSIDE_SET, IA3 ) );
    assert( N.classify( P6 ).first == INSIDE_SET );
    assert( N.classify( P7 ).first == INSIDE_SET );
}

void test_boolean_intersection()
{
    BSP_node_E1 N;
    N.boolean_union( S24, BA1, IA1 );
    N.boolean_intersection( S46, BA2 );

    assert( N.is_empty() );
}

void test_boolean_difference()
{
    {
        BSP_node_E1 N;
        N.boolean_union( S24, BA1, IA1 );
        N.boolean_difference( S46, BA2 );

        assert( N.classify( P2 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P4 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P6 ).first == OUTSIDE_SET     );
    }
    {
        BSP_node_E1 N;
        N.boolean_union( S26, BA1, IA1 );
        N.boolean_difference( S48, BA2 );

        assert( N.classify( P2 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P4 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P6 ).first == OUTSIDE_SET     );
        assert( N.classify( P8 ).first == OUTSIDE_SET     );
    }
    {
        BSP_node_E1 N;
        N.boolean_union( S28, BA1, IA1 );
        N.boolean_difference( S46, BA2 );

        assert( N.classify( P2 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P4 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P6 ).first == ON_SET_BOUNDARY );
        assert( N.classify( P8 ).first == ON_SET_BOUNDARY );

        assert( N.classify( P3 ) == std::make_pair( INSIDE_SET, IA1 ) );
        assert( N.classify( P7 ) == std::make_pair( INSIDE_SET, IA1 ) );
    }

    {
        BSP_node_E1 N;
        N.boolean_union( S26, BA1, IA1 );
        N.boolean_difference( S48, BA2 );

        assert( N.hyperplane == P6 );
        assert( N.negative_child->hyperplane == P2 );
        assert( N.negative_child->boundary_attributes == BA1 );
        assert( N.negative_child->positive_child->hyperplane == P4 );
        assert( N.negative_child->positive_child->boundary_attributes == BA2 );

        assert( N.negative_child->positive_child->negative_child->cell_is_occupied );
        assert( N.negative_child->positive_child->negative_child->interior_attributes == IA1 );
        assert( !N.negative_child->positive_child->positive_child->cell_is_occupied );
    }
}

int main()
{
    test_size();
    test_point_containment();
    test_boolean_intersection();
    test_boolean_difference();
}
