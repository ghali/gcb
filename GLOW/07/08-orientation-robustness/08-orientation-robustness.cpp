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
using namespace std;
#include <cassert>
#include <sstream>
#include <vector>
using std::string;
using std::vector;

#include "geometry/E2/bbox_e2.h"
#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/predicates_e2.h"

#include "postscript/postscript.h"

typedef Point_E2<float>         Point_E2f;
typedef Bbox_E2<float>           Bbox_E2f;
typedef Postscript<float>    Postscript_f;

int oneBitOfSeparationInt[] = {
    0x3F800000,
    0x3F800001,
    0x3F800002,
    0x3F800003,
    0x3F800004,
    0x3F800005,
    0x3F800006,
    0x3F800007,
    0x3F800008,
    0x3F800009,
    0x3F80000a,
    0x3F80000b,
    0x3F80000c,
    0x3F80000d,
    0x3F80000e,
    0x3F80000f
};

void float_orientation_robustness(const std::string& filename,
                                  float Px, float Py,
                                  float Qx, float Qy)
{
    std::ostringstream ostrfilename;
    ostrfilename.setf(std::ios::showpos);
    ostrfilename << filename << Px << Qx << ".eps";

    Postscript_f PS(ostrfilename.str(), Bbox_E2f(Point_E2f(0,0), Point_E2f(160, 160)));
    vector<float> oneBitOfSeparationFloat;
    int i=0;
    while(i<16)
        oneBitOfSeparationFloat.push_back( *reinterpret_cast<float*>( &(oneBitOfSeparationInt[i++]) ) );

    for(int x=0; x<16; ++x)
        for(int y=0; y<16; ++y) {
            Oriented_side o = oriented_side(
                                            Point_E2f(Px, Py),
                                            Point_E2f(Qx, Qy),
                                            Point_E2f(oneBitOfSeparationFloat[x],
                                                      oneBitOfSeparationFloat[y]));
            double gray=0.5;
            switch (o) {
            case ON_POSITIVE_SIDE: gray = 0.8; break;
            case ON_NEGATIVE_SIDE: gray = 0.5; break;
            case ON_ORIENTED_BOUNDARY: gray = 0.1; break;
            }
            PS.set_gray(gray);
            PS.draw_square(Bbox_E2f( Point_E2f(x*10+0.5,y*10+0.5), Point_E2f(x*10+9.5,y*10+9.5) ));
        }
}

int main()
{
//----------------main_Begin----------------
    for(float P = -10; P<= -1; P += 1.0)
        for(float Q = P+1; Q <= 0; Q += 1.0)
            float_orientation_robustness(
                "psout/orientation-robustness", P, P, Q, Q);
//----------------main_End----------------
}
