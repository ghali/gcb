/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "csg_types_e1.h"

#include <cassert>
#include <iostream>

int main()
{
    {
        // Test point containment in a 1D CSG tree

        Point_E1d N2(2);
        Point_E1d N3(3);
        Point_E1d N4(4);
        Point_E1d N5(5);
        Point_E1d N6(6);
        Point_E1d N7(7);
        Point_E1d N9(9);

        Segment_E1d S26(N2, N6);
        Segment_E1d S79(N7, N9);
        Segment_E1d S47(N4, N7);

        CSG_E1_segment * CS26 = new CSG_E1_segment( S26 );
        CSG_E1_segment * CS47 = new CSG_E1_segment( S47 );
        CSG_E1_segment * CS79 = new CSG_E1_segment( S79 );
        {
            CSG_Boolean_E1d B_26_u_79(UNION, CS26, CS79);

            Neighborhood_E1 ng5 = B_26_u_79.classify( N5 );
            assert( ng5.left() && ng5.right() );

            Neighborhood_E1 ng6 = B_26_u_79.classify( N6 );
            assert( ng6.left() && !ng6.right() );

            Neighborhood_E1 ng9 = B_26_u_79.classify( N9 );
            assert( ng9.left() && !ng9.right() );
        }
        {
            CSG_transformation_E1d * T = new CSG_transformation_E1d(Transformation_E1d(IDENTITY), CS47);
            CSG_Boolean_E1d B_26_diff_47(DIFFERENCE, CS26, T);

            Neighborhood_E1 ng6 = B_26_diff_47.classify( N6 );
            assert( !ng6.left() && !ng6.right() );

            Neighborhood_E1 ng5 = B_26_diff_47.classify( N5 );
            assert( !ng5.left() && !ng5.right() );

            Neighborhood_E1 ng4 = B_26_diff_47.classify( N4 );
            assert( ng4.left() && !ng4.right() );

            Neighborhood_E1 ng3 = B_26_diff_47.classify( N3 );
            assert( ng3.left() && ng3.right() );

            delete T;
        }
        delete CS26;
        delete CS79;
        delete CS47;
    }
}
