/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "geometry/E2/point_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/E2/predicates_e2.h"
#include "geometry/E2/interpolation_e2.h"

#include "misc/random_e2.h"

//----------------find_intersecting_medians_Begin----------------
template<typename T>
int
find_intersecting_medians(int trials)
{
    int non_degenerate_triangles = 0;
    int medians_meet_at_one_point = 0;

    while(trials) {

        Point_E2<T> P0, P1, P2;
        set_to_random(P0);
        set_to_random(P1);
        set_to_random(P2);

        if( oriented_side(P0, P1, P2) != ON_ORIENTED_BOUNDARY ) {

            non_degenerate_triangles++;

            T half( 0.5 );
            Point_E2<T> median01 = interpolate(P0 , P1, half);
            Point_E2<T> median12 = interpolate(P1 , P2, half);
            Point_E2<T> median20 = interpolate(P2 , P0, half);

            Line_E2<T> L0( P0, median12 );
            Line_E2<T> L1( P1, median20 );
            Line_E2<T> L2( P2, median01 );

            Point_E2<T> P01 = intersection(L0, L1);
            Point_E2<T> P12 = intersection(L1, L2);

            if( P01 == P12 )
                ++medians_meet_at_one_point;

            --trials;
        }
    }
    return medians_meet_at_one_point;
}
//----------------find_intersecting_medians_End----------------

template<typename T>
void
report(int trials, int medians_meet_at_one_point)
{
    std::cout << typeid(T).name()
              << ": " << medians_meet_at_one_point << " / " << trials
              << " of nondegenerate triangles have coincident medians." << std::endl;
}
