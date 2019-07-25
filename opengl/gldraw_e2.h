/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef GLDRAW_E2_H
#define GLDRAW_E2_H

#include <vector>

#include "glow.h"
#include "glowAux.h"
using namespace glow;

#include "misc/conversions.h"
#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/polygon_e2.h"

template<typename NT>
struct GLdraw_E2
{
    typedef Point_E2<int>        Point_E2i;
    typedef Point_E2<double>     Point_E2d;

    static void draw_point(const Point_E2<NT>& p,
                           const GlowColor& pointColor = GlowColor::yellow,
                           float pointSize = 7.0)
    {
        glPointSize(pointSize);
        pointColor.Apply();
        glBegin(GL_POINTS); {
            glVertex2f( to_float(p.x()), to_float(p.y()) );
        } glEnd();
    }

    static void draw_segment(const Point_E2<NT>& source, const Point_E2<NT>& target,
                             const GlowColor& segmentColor = GlowColor::cyan,
                             float lineWidth = 3.0,
                             bool drawEndpoints = true,
                             const GlowColor& pointColor = GlowColor::yellow,
                             float pointSize = 7.0)
    {
        glLineWidth(lineWidth);

        segmentColor.Apply();
        glBegin(GL_LINES); {
            glVertex2f( to_float(source.x()), to_float(source.y()) );
            glVertex2f( to_float(target.x()), to_float(target.y()) );
        } glEnd();

        if(drawEndpoints) {
            draw_point(source, pointColor, pointSize);
            draw_point(target, pointColor, pointSize);
        }
    }

    static void draw(const Segment_E2<NT>& s,
                     const GlowColor& segmentColor = GlowColor::cyan,
                     float lineWidth = 3.0,
                     bool drawEndpoints = true,
                     const GlowColor& pointColor = GlowColor::yellow,
                     float pointSize = 7.0)
    {
        draw_segment(s.source(), s.target(),
                     segmentColor, lineWidth, drawEndpoints,
                     pointColor, pointSize);
    }

    static void draw_polygon(const Polygon_E2<NT>& polygon,
                             const GlowColor& segmentColor = GlowColor::cyan,
                             const GlowColor& pointColor = GlowColor::yellow,
                             float lineWidth = 3.0,
                             float pointSize = 7.0,
                             bool filled = false,
                             bool drawEndpoints = true)
    {
        glLineWidth(lineWidth);
        segmentColor.Apply();
        glBegin(filled ? GL_POLYGON : GL_LINE_LOOP); {
            for(unsigned int i = 0; i != polygon.size(); ++i)
                glVertex2f( to_float(polygon[i].x()), to_float(polygon[i].y()) );
        } glEnd();

        glPointSize(pointSize);
        pointColor.Apply();
        if(drawEndpoints) {
            for(unsigned int i = 0; i != polygon.size(); ++i) {
                glBegin(GL_POINTS); {
                    glVertex2f( to_float(polygon[i].x()), to_float(polygon[i].y()) );
                } glEnd();
            }
        }
    }

    static void draw_polylines(const Polygon_E2<NT>& polygon,
                               bool two_colors = false,
                               const GlowColor& segmentColor = GlowColor::cyan,
                               const GlowColor& pointColor1 = GlowColor::yellow,
                               float lineWidth = 3.0,
                               float pointSize = 7.0,
                               bool drawEndpoints = true,
                               int mod_for_first = 3,
                               const GlowColor& pointColor2 = GlowColor::red)
    {
        glLineWidth(lineWidth);
        segmentColor.Apply();
        glBegin(GL_LINE_STRIP); {
            for(unsigned int i = 0; i != polygon.size(); ++i)
                glVertex2f( to_float(polygon[i].x()), to_float(polygon[i].y()) );
        } glEnd();

        glPointSize(pointSize);
        if(!two_colors)
            pointColor1.Apply();
        if(drawEndpoints) {
            for(unsigned int i = 0; i != polygon.size(); ++i) {
                glBegin(GL_POINTS); {
                    if(two_colors)
                        if(i%mod_for_first == 0)
                            pointColor1.Apply();
                        else
                            pointColor2.Apply();
                    glVertex2f( to_float(polygon[i].x()), to_float(polygon[i].y()) );
                } glEnd();
            }
        }
    }

    static void clear_screen()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void set_color(float r, float g, float b)
    {
        glColor3f(r,g,b);
    }

    static void setup_projection(const Point_E2<NT>& wmin, const Point_E2<NT>& wmax)
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(to_double(wmin.x()), to_double(wmax.x()),
                   to_double(wmin.y()), to_double(wmax.y()));

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0);
        glPointSize(7.0);
    }

    static Point_E2<NT> unproject(const Point_E2i& pin)
    {
        GLint viewport[4];
        GLdouble mvmatrix[16], projmatrix[16];
        GLint realy;            //  OpenGL y coordinate position
        GLdouble wx, wy, wz;    // returned world x, y, z coords

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

        // viewport[3] is the height of the window in pixels.
        realy = viewport[3] - (GLint) pin.y() - 1;

        gluUnProject((GLdouble) pin.x(), (GLdouble) realy,
                     0.0,         // Ortho2D means any z-value will do
                     mvmatrix, projmatrix, viewport, &wx, &wy, &wz); 

        return Point_E2<NT>(wx, wy);
    }
};

#endif // GLDRAW_E2_H
