/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef COINCIDENCEDATA_H
#define COINCIDENCEDATA_H

#include <iomanip>

#include "geometry/E2/bbox_e2.h"
#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/E2/interpolation_e2.h"
#include "geometry/E2/transformation_e2.h"

#include "postscript/postscript.h"

typedef Point_E2<double>     Point_E2d;
typedef Line_E2<double>       Line_E2d;
typedef Vector_E2<double>   Vector_E2d;
typedef Segment_E2<double> Segment_E2d;
typedef Bbox_E2<double>       Bbox_E2d;
typedef Transformation_E2<double> Transformation_E2d;

typedef Postscript<double> Postscript_E2d;

Identity IDENTITY;
Scale SCALE;
Rotation ROTATION;
Translation TRANSLATION;

#include <vector>
using namespace std;

// points connected to coi are on segmentToSample
const Segment_E2d initSegmentToSample = Segment_E2d(Point_E2d(1,-1), Point_E2d(1,1));

// center of interest (not passing by initSegmentToSample)
const Point_E2d initCoi = Point_E2d(-1,0);

class CoincidenceData
{
    double epsilon;
    Point_E2d coi;    
    Segment_E2d segmentToSample;
    vector<Segment_E2d> newSegments;

    GLUquadricObj * qobj;

    Bbox_E2d myBbox;

public:
    CoincidenceData()
    {
        qobj = gluNewQuadric();

        setUpValues();
    }

    ~CoincidenceData()
    {
        gluDeleteQuadric(qobj);
    }

    void setSegmentToSample(const double rotation)
    {
        // set segmentToSample by rotating initSegmentToSample around coi
        segmentToSample = initSegmentToSample;

        Transformation_E2d T1(TRANSLATION, Point_E2d(0,0) - coi);
        Transformation_E2d R(ROTATION, M_PI * rotation/180.0);
        Transformation_E2d T2(TRANSLATION, coi - Point_E2d(0,0));

        Transformation_E2d F = T2 * R * T1;

        segmentToSample = F.transform(initSegmentToSample);
    }

    void setUpValues(double epsilon = 1e-8, // distance between segmentToSample and cut Line
                     const double rotation = 0
                     )
    {
        coi = initCoi;
        setSegmentToSample(rotation);

        // Generate segments between (coi) and points on segmentToSample
        vector<Segment_E2d> segments;
        for(double alpha = 0.0; alpha <= 1.0;  alpha += 0.125)
            segments.push_back(Segment_E2d(coi, interpolate(segmentToSample.source(),
                                                            segmentToSample.target(),
                                                            alpha)));
        const Line_E2d cutLine(interpolate(segmentToSample.source(), coi, epsilon),
                               interpolate(segmentToSample.target(), coi, epsilon));

        // Cut the segments using cutLine
        newSegments.clear();
        vector<Segment_E2d>::const_iterator si = segments.begin();

        while(si != segments.end()) {

            Point_E2d intersectionPoint = intersection(cutLine, Line_E2d(si->source(), si->target()));
            Vector_E2d fromPointSampleToCoi = coi - si->target();
            Segment_E2d extendedSegment(coi + fromPointSampleToCoi,
                                        intersectionPoint /*not si->target()*/);

            newSegments.push_back(extendedSegment);
            ++si;
        }

        segments.clear();
        segments = newSegments;
    }

    void setBbox(const Bbox_E2d& b)
    {
        myBbox = b;
    }

    void draw()
    {
        vector<Segment_E2d>::const_iterator si = newSegments.begin();
        while(si != newSegments.end()) {
            glBegin(GL_LINES); {
                glVertex2f(si->source().x(), si->source().y());
                glVertex2f(si->target().x(), si->target().y());
            }; glEnd();
            ++si;
        }

        gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
        gluQuadricNormals(qobj, GLU_NONE);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); {
            glTranslated(initCoi.x(), initCoi.y(), 0.0);
            gluDisk(qobj, 0.0, myBbox.width()/50.0, 60, 1); // draw circle at coi
        } glPopMatrix();
    }

    void outputToPostScript()
    {
        Postscript_E2d PS("file.eps", myBbox);

        vector<Segment_E2d>::const_iterator si = newSegments.begin();
        while(si != newSegments.end())
        {
            Segment_E2d seg = *si;
            if(Brute_Bbox_clipping_of_segment(myBbox, seg))
                PS.draw(seg);

            ++si;
        }

        PS.draw_small_circle(initCoi);

        PS.close();
    }
};

#endif // COINCIDENCEDATA_H
