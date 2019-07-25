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
#include <iomanip>
#include <string>
using namespace std;

#include "glow.h"
using namespace glow;

#include "geom_types.h"
#include "precisiondata.h"
#include "precisionwindow.h"

int main(int argc, char **argv)
{
    bool debug = false;

    if ( argc > 1 && strcmp( "-d", argv[1]) == 0)
        debug = true;

    Glow::Init(argc, argv);

    int resolution = 512;

    // Set the following four values to "trip" the
    // floating point computation the most
    double increment = 1e-17/3.0;
    double p1xy =  1.00000000007;
    double p2xy = 10.00000000003;
    double p3xy = 20 + 1/7e10;

    cout << setprecision(999)
         << "increment: " << increment << endl
         << "p1: " << p1xy << endl
         << "p2: " << p2xy << endl
         << "p3: " << p3xy << endl;

    Point_E2d p1(p1xy, p1xy);
    Point_E2d p2(p2xy, p2xy);
    Point_E2d p3(p3xy, p3xy);

    PrecisionData* myPrecisionData = new PrecisionData( resolution, increment,
                                                        p1, p2, p3,
                                                        debug );
    new PrecisionWindow( myPrecisionData, debug );

    Glow::MainLoop();

    delete myPrecisionData;
}
