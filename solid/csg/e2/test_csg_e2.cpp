/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "csg_types_e2.h"

#include <cassert>
#include <iostream>
#include <map>

int main()
{
    {
        // Test point containment in a 2D CSG tree

        const Point_E2d A(0,0), B(1,0), C(0,1);
        const Triangle_E2d Tabc(A,B,C);

        const Point_E2d D(2,0), E(3,0), F(2,1);
        const Triangle_E2d Tdef(D,E,F);

        CSG_E2_triangle * T1 = new CSG_E2_triangle( Tabc );
        CSG_E2_triangle * T2 = new CSG_E2_triangle( Tdef );

        {
            CSG_Boolean_E2d B1(UNION, T1, T2);

            Neighborhood_E2 n1 = B1.classify( Point_E2d(-1,1) );
            assert( n1.is_empty() );

            Neighborhood_E2 n2 = B1.classify( Point_E2d(.2,.2) );
            assert( n2.is_full() );

            Neighborhood_E2 n3 = B1.classify( A );
            assert( n3.contains( Point_S1d( 1,1) ) == INSIDE_SET &&
                    n3.contains( Point_S1d(-1,1) ) == OUTSIDE_SET );
        }
        delete T1;
        delete T2;
    }
}
