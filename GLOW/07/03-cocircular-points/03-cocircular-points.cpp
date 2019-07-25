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
#include <vector>
using std::vector;

#include "geometry/E2/point_e2.h"
#include "geometry/E2/direction_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/E2/predicates_e2.h"

#include "misc/random_e2.h"

//----------------cocircular_points_Begin----------------
template<typename T>
int
cocircular_points(int trials)
{
    int points_are_cocircular = 0;
    int i = trials;

    while(i--) {
        vector<Vector_E2<T> > V(4);
        set_to_random(V[0]);

        do {
            set_to_random(V[1]);
        } while(V[1] == V[0]);
        do {
            set_to_random(V[2]);
        } while(V[2] == V[0] || V[2] == V[1]);
        do {
            set_to_random(V[3]);
        } while(V[3] == V[0] || V[3] == V[1] || V[3] == V[2]);

        vector<Point_E2<T> > P(4);
        for(int i=0;i<4;++i)
            P[i] = Point_E2<T>(0,0) + Direction_E2<T>(V[i]);

        if(inside_circle(P[0], P[1], P[2], P[3]) == COCIRCULAR)
            ++points_are_cocircular;
    }
    return points_are_cocircular;
}
//----------------cocircular_points_End----------------

template<typename T>
void
report(int trials, int points_are_cocircular) 
{
    std::cout << typeid(T).name()
              << ": " << points_are_cocircular << " / " << trials
              << " quadruples of points supposedly on the unit circle actually are." << std::endl;
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cerr << "Usage: cocircular_points <number>\n";
        exit(1);
    }
    int trials = atoi(argv[1]);

    report<float>(trials, cocircular_points<float>(trials));
    report<double>(trials, cocircular_points<double>(trials));
    report<long double>(trials, cocircular_points<long double>(trials));
}
