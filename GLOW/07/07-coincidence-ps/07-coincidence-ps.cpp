/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include <string>
#include <vector>
#include <cmath>
using namespace std;

#include "geometry/E2/bbox_e2.h"
#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/E2/interpolation_e2.h"

#include "postscript/postscript.h"

typedef Point_E2<double>     Point_E2d;
typedef Vector_E2<double>   Vector_E2d;
typedef Segment_E2<double> Segment_E2d;
typedef Line_E2<double>       Line_E2d;
typedef Bbox_E2<double>       Bbox_E2d;

vector<Segment_E2d>
diagram01(double /*epsilon*/, const Point_E2d& coi, const Segment_E2d& segmentToSample)
{
    // Generate segments between points on segmentToSample and the reflection
    // of each point from coi
    vector<Segment_E2d> segments;
    for(double alpha = 0.0; alpha <= 1.0;  alpha += 0.125)
    {
        Point_E2d psrc = interpolate(segmentToSample.source(), segmentToSample.target(), alpha);
        Vector_E2d fromPsrcToCoi = coi - psrc;
        Segment_E2d extendedSegment(coi + fromPsrcToCoi, psrc);
        segments.push_back(extendedSegment);
    }

    return segments;
}

vector<Segment_E2d>
diagram02(double epsilon, const Point_E2d& coi, const Segment_E2d& segmentToSample)
{
    // Generate segments between (coi) and points on segmentToSample
    vector<Segment_E2d> segments;
    for(double alpha = 0.0; alpha <= 1.0;  alpha += 0.125)
        segments.push_back(Segment_E2d(coi, interpolate(segmentToSample.source(),
                                                        segmentToSample.target(),
                                                        alpha)));
    const Line_E2d cutLine(interpolate(segmentToSample.source(), coi, epsilon),
                           interpolate(segmentToSample.target(), coi, epsilon));

    // Cut the segments using cutLine
    vector<Segment_E2d> newSegments;
    vector<Segment_E2d>::const_iterator si = segments.begin();

    while(si != segments.end()) {

        Line_E2d sil(si->source(), si->target());
        Point_E2d intersectionPoint = intersection(cutLine, sil);

        Vector_E2d fromPointSampleToCoi = coi - si->target();

        Segment_E2d extendedSegment(coi + fromPointSampleToCoi,
                                    intersectionPoint /*not si->target()*/);

        newSegments.push_back(extendedSegment);
        ++si;
    }
    return newSegments;
}

void draw(std::string filename, vector<Segment_E2d> segments, const Point_E2d& coi, double drawEpsilon)
{
    Bbox_E2d myBbox(Point_E2d( coi.x() - drawEpsilon, coi.y() - drawEpsilon),
                    Point_E2d( coi.x() + drawEpsilon, coi.y() + drawEpsilon));

    Postscript<double> PS(filename, myBbox);

    PS.newpath();
    vector<Segment_E2d>::const_iterator si = segments.begin();
    while(si != segments.end())
    {
        Segment_E2d seg = *si;
//        if(Brute_Bbox_clipping_of_segment(myBbox, seg))
        PS.draw(seg);
        ++si;
    }
    PS.stroke();
    PS.draw_small_circle(coi);
    PS.close();
}

int main()
{
    const double epsilon = 1e-15; // distance between segmentToSample and cut Line
    const double drawEpsilon = 1e-15; // distance magnified around the coi
    const Point_E2d coi(-1,0);        // center of interest

    // points connected to coi
    const Segment_E2d segmentToSample(Point_E2d(1, -1),
                                      Point_E2d(1,1));

    cout << "epsilon: " << epsilon << endl;
    cout << "segmentToSample: " << segmentToSample << endl;

    vector<Segment_E2d> vs = diagram01(epsilon, coi, segmentToSample /*cutLine*/);
    draw("psout/diagram01.eps", vs, coi, drawEpsilon);
}
