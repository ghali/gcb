/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry_types.h"
#include "splitting_e1.h"
#include "splitting_s1.h"

#include <cassert>

void test_splitting_E1()
{

    const Point_E1d P1(1), P2(2), P3(3), P4(4), P5(5);
    const Point_E1d P6(6), P7(7), P8(8), P9(9);

    const Convex_polytope_E1d S24( P2, P4 );
    const Convex_polytope_E1d S46( P4, P6 );
    const Convex_polytope_E1d S68( P6, P8 );

    const Convex_polytope_E1d S26( P2, P6 );
    const Convex_polytope_E1d S48( P4, P8 );

    const Convex_polytope_E1d S28( P2, P8 );

    {    
        Convex_polytope_E1d positive_part, negative_part;
        const Hyperplane_E1d P6_splitter(P6);

        split<Geometry_E1d>( S48, P6_splitter, positive_part, negative_part );

        assert( negative_part.get_Segment_E1() == S46.get_Segment_E1() );
        assert( negative_part.is_source_closed() );
        assert( !negative_part.is_target_closed() );

        assert( positive_part.get_Segment_E1() == S68.get_Segment_E1() );
        assert( !positive_part.is_source_closed() );
        assert( positive_part.is_target_closed() );
    }
}

void test_splitting_S1()
{
    const Point_S1d A( 1, 1);
    const Point_S1d B(-1, 1);
    const Point_S1d C(-1,-1);
    const Point_S1d D( 1,-1);

    const Convex_polytope_S1d AB( A, B );
    const Convex_polytope_S1d BC( B, C );
    const Convex_polytope_S1d CD( C, D );

    {
        {
            Convex_polytope_S1d positive_part, negative_part;
            const Hyperplane_S1d N(0,1);
            split<Geometry_S1d>(AB, N, positive_part, negative_part);
            assert(negative_part.source() == A);
            assert(negative_part.target() == N);
            assert(positive_part.source() == N);
            assert(positive_part.target() == B);
        }
        {
            Convex_polytope_S1d positive_part, negative_part;
            Convex_polytope_S1d S1(S1_FULL);
            split<Geometry_S1d>(S1, A, positive_part, negative_part);
            assert(negative_part.source() == A.antipode());
            assert(negative_part.target() == A);
            assert(positive_part.source() == A);
            assert(positive_part.target() == A.antipode());
        }
    }
}

int main()
{
    test_splitting_E1();
    test_splitting_S1();
}
