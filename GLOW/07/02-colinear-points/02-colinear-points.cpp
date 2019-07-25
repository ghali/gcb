/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <iostream>

#include "geometry/E2/point_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/E2/predicates_e2.h"

#include "misc/random_e2.h"

//----------------colinear_points_Begin----------------
template<typename NT>
int
colinear_points(int trials)
{
    int points_are_colinear = 0;
    int i = trials;

    while(i--) {
        Line_E2<NT> L;
        set_to_random<NT>(L);

        Line_E2<NT> L0, L1, L2;
        do { set_to_random<NT>(L0); } while(L.is_parallel(L0));
        do { set_to_random<NT>(L1); } while(L.is_parallel(L1));
        do { set_to_random<NT>(L2); } while(L.is_parallel(L2));

        Point_E2<NT> P0 = intersection(L, L0);
        Point_E2<NT> P1 = intersection(L, L1);
        Point_E2<NT> P2 = intersection(L, L2);

        if(oriented_side(P0,P1,P2) == ON_ORIENTED_BOUNDARY)
            ++points_are_colinear;
    }

    return points_are_colinear;
}
//----------------colinear_points_End----------------

template<typename NT>
void
report(int trials, int points_are_colinear) 
{
    std::cout << typeid(NT).name()
              << ": " << points_are_colinear << " / " << trials
              << " of triples of points supposedly colinear actually are." << std::endl;
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cerr << "Usage: colinear_points <number>\n";
        exit(1);
    }
    int trials = atoi(argv[1]);

    report<float>(trials,  colinear_points<float>(trials));
    report<double>(trials, colinear_points<double>(trials));
    report<long double>(trials, colinear_points<long double>(trials));
}
