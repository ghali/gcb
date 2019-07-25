/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "01-intersecting-medians.h"

int main(int argc, char** argv)
{
    if(argc != 2) {
        std::cerr << "Usage: intersecting-medians <number>\n";
        exit(1);
    }
    srand48(0);
    int trials = atoi(argv[1]);
    // report<int>(trials, find_intersecting_medians<int>(trials));
    report<float>(trials, find_intersecting_medians<float>(trials));
    report<double>(trials, find_intersecting_medians<double>(trials));
    report<long double>(trials, find_intersecting_medians<long double>(trials));
}
