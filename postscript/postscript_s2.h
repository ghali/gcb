/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POSTSCRIPT_S2_H
#define POSTSCRIPT_S2_H

#include "geometry/E2/point_e2.h"
#include "geometry/E2/bbox_e2.h"
#include "geometry/E3/point_e3.h"
#include "geometry/E3/projection_e3.h"

#include "geometry/E3/normalize_e3.h"
#include "geometry/E3/transformation_e3.h"

#include "geometry/S2/point_s2.h"
#include "geometry/S2/segment_s2.h"
#include "geometry/S2/triangle_s2.h"
#include "geometry/S2/circle_s2.h"
#include "geometry/S2/interpolation_s2.h"

#include "postscript/postscript.h"

template<typename NT>
class Postscript_S2 : public Postscript<NT>
{
    Transformation_E3<NT> T;
    Project_on_xy<NT> myProjection;

    Point_S2<NT> viewer_S2;
public:
    Postscript_S2(const std::string& psfilename,
                  const Point_E3<NT>& viewer,
                  const Point_E3<NT>& coi,
                  const Bbox_E2<NT>& bbox,
                  const double line_width = 3.0)
        : Postscript<NT>(psfilename, bbox),
          viewer_S2(viewer.x(), viewer.y(), viewer.z())
    {
        T = Transformation_E3<NT>(ORTHOGONAL, viewer, coi);
        myProjection = Project_on_xy<NT>();

        Postscript<NT>::set_line_width(line_width);
        Postscript<NT>::set_line_cap(1);
        Postscript<NT>::set_line_join(1);
    }

    virtual ~Postscript_S2() {
        Postscript<NT>::set_line_width(3.0);
        draw( Circle_S2<NT>(viewer_S2), false );
    }

    void draw_stem( const Point_S2<NT>& point,
                    double back_intensity = 0.7 )
    {
        Point_E2<NT> pe2 = my_projection(point, T, myProjection);

        Postscript<NT>::set_gray( back_intensity );
        Point_E2<NT> center = my_projection_of_center(T, myProjection);
        Postscript<NT>::draw( Segment_E2<NT>( center, pe2 ) );
    }

    void draw( const Point_S2<NT>& point,
               double radius = 0.05,
               bool stem = false,
               bool distinct_back_faces = true,
               double back_intensity = 0.7,
               bool filled_marker = true,
               bool arrow = false)
    {
        double black = distinct_back_faces ? 0.0 : back_intensity;
        double gray = distinct_back_faces ? back_intensity : black;

        NT ip = inner_product( point, viewer_S2 );
        bool point_is_front_facing = (ip > 0.0);

        Point_E2<NT> pe2 = my_projection(point, T, myProjection);

        if( !arrow ) {

            if(stem) {
                Postscript<NT>::set_gray( gray );
                Point_E2<NT> center = my_projection_of_center(T, myProjection);
                Postscript<NT>::draw( Segment_E2<NT>( center, pe2 ) );
            }

            Postscript<NT>::set_gray( point_is_front_facing ? black : gray );
            if( filled_marker )
                draw_disk( pe2, radius );
            else
                draw_circle( pe2, radius );
        }
        else {
            Postscript<NT>::set_gray( gray );
            Point_E2<NT> center = my_projection_of_center(T, myProjection);
            Postscript<NT>::draw_arrow( Segment_E2<NT>( center, pe2 ),
                                        0.92, 5.0, 3.0 );
        }
    }

    void moveto( const Point_S2<NT>& point )
    {
        Point_E2<NT> pe2 = my_projection(point, T, myProjection);
        Postscript<NT>::moveto(pe2);
    }
    void lineto( const Point_S2<NT>& point )
    {
        Point_E2<NT> pe2 = my_projection(point, T, myProjection);
        Postscript<NT>::lineto(pe2);
    }
    void draw_small_disk(const Point_S2<NT>& point )
    {
        Point_E2<NT> pe2 = my_projection(point, T, myProjection);
        Postscript<NT>::draw_small_disk(pe2);
    }

    void
    draw_small_disks(const std::vector<Point_S2<NT> >& P)
    {
        typedef typename std::vector<Point_S2<NT> >::const_iterator PI;
        for(PI pi=P.begin(); pi!=P.end(); ++pi)
            draw_small_disk(*pi);
    }

    void draw_small_circle(const Point_S2<NT>& point )
    {
        Point_E2<NT> pe2 = my_projection(point, T, myProjection);
        Postscript<NT>::draw_small_circle(pe2);
    }

    void draw( const Segment_S2<NT>& segment,
               bool distinct_back_faces = true,
               double back_intensity = 0.7,
               bool stroke = true ) // false ==> used as subroutine to draw_polygon
    {
        double black = distinct_back_faces ? 0.0 : back_intensity;
        double gray = distinct_back_faces ? back_intensity : black;

        NT lip = inner_product( segment.source(), viewer_S2 );
        bool last_front_facing = (lip > 0.0);

        Postscript<NT>::set_gray( last_front_facing ? black : gray );
        if(stroke)
            Postscript<NT>::newpath();
        if(stroke)
            Postscript<NT>::moveto( my_projection(segment.source(), T, myProjection) );
        else
            Postscript<NT>::lineto( my_projection(segment.source(), T, myProjection) );

        const NT increment = 0.075;

        for(NT u = 0.0; u < 1.0; u += increment )
        {
            Point_S2<NT> ps2 = slerp(segment.source(), segment.target(), u);
            NT ip = inner_product( ps2, viewer_S2 );
            bool front_facing = (ip > 0.0);
            Point_E2<NT> pe2 = my_projection(ps2, T, myProjection);

            if(front_facing != last_front_facing) {
                Postscript<NT>::lineto( pe2 );
                if(stroke)
                    Postscript<NT>::stroke();
                Postscript<NT>::set_gray( front_facing ? black : gray );
                if(stroke)
                    Postscript<NT>::moveto( pe2 );
                else
                    Postscript<NT>::lineto( pe2 );
            }
            else
                Postscript<NT>::lineto( pe2 );

            last_front_facing = front_facing;
        }
        if(stroke)
            Postscript<NT>::stroke();
    }

    void draw_polygon(const std::vector<Point_S2<NT> > P,
                      bool fill_polygon,
                      double gray_fill = 0.7)
    {
        Postscript<NT>::newpath();
        typedef typename std::vector<Point_S2<NT> >::const_iterator PI;
        PI last_p = P.end(); --last_p;
        PI p = P.begin();
        moveto(*last_p);
        do {
            draw(Segment_S2<NT>(*last_p, *p), false, gray_fill, false);
            cout << *last_p << "    " << *p << endl;
            last_p = p;
            ++p;
        } while(p != P.end());

        Postscript<NT>::closepath();
        if(fill_polygon)
            Postscript<NT>::fill();
        else
            Postscript<NT>::stroke();
    }

    void draw( const Circle_S2<NT>& circle,
               bool distinct_back_faces = true,
               double back_intensity = 0.7 )
    {
        const double DIVISIONS = 60.0;

        double black = distinct_back_faces ? 0.0 : back_intensity;
        double gray = distinct_back_faces ? back_intensity : black;

        Point_S2<NT> base1 = circle.base1();
        Point_S2<NT> base2 = circle.base2();

        NT lip = inner_product( base1, viewer_S2 );
        bool last_front_facing = (lip > 0.0);

        Postscript<NT>::set_gray( last_front_facing ? black : gray );
        Postscript<NT>::newpath();
        Postscript<NT>::moveto( my_projection(base1, T, myProjection) );

        for(double theta = 0.0; theta <= 2*M_PI + M_PI/2*DIVISIONS; theta += M_PI/DIVISIONS)
        {
            Point_S2<NT> ps2 = base1 * NT(cos(theta)) + base2 * NT(sin(theta));

            NT ip = inner_product( ps2, viewer_S2 );

            bool front_facing = (ip > 0.0);
            Point_E2<NT> pe2 = my_projection(ps2, T, myProjection);

            if(front_facing != last_front_facing && distinct_back_faces) {
                Postscript<NT>::lineto( pe2 );
                Postscript<NT>::stroke();
                Postscript<NT>::set_gray( front_facing ? black : gray );
                Postscript<NT>::moveto( pe2 );
            }
            else
                Postscript<NT>::lineto( pe2 );

            last_front_facing = front_facing;
        }
        Postscript<NT>::stroke();
    }

    void draw( const Triangle_S2<NT>& T,
               bool draw_stems = true,
               bool draw_circles = true,
               bool draw_antipode_stems = true,
               const double circle_line_width = 2.5,
               const double segment_line_width = 3.5 )
    {
        const Point_S2<NT> P0 = T.P0();
        const Point_S2<NT> P1 = T.P1();
        const Point_S2<NT> P2 = T.P2();

        if( draw_antipode_stems ) {
            draw_stem( P0.antipode() );
            draw_stem( P1.antipode() );
            draw_stem( P2.antipode() );
        }

        if( draw_stems ) {
            draw_stem( P0 );
            draw_stem( P1 );
            draw_stem( P2 );
        }

        if( draw_circles ) {
            Postscript<NT>::set_line_width( circle_line_width );
            draw( Circle_S2<NT>(P0, P1) );
            draw( Circle_S2<NT>(P1, P2) );
            draw( Circle_S2<NT>(P2, P0) );
        }

        Postscript<NT>::set_line_width( segment_line_width );
        draw( Segment_S2<NT>(P1, P0) );
        draw( Segment_S2<NT>(P1, P2) );
        draw( Segment_S2<NT>(P2, P0) );

        draw( P0 );
        draw( P1 );
        draw( P2 );
    }

    void set_line_width(double lw) {
        Postscript<NT>::set_line_width(lw);
    }

    short get_line_width() const {
        return Postscript<NT>::get_line_width();
    }

private:
    Point_E2<NT>
    my_projection(const Point_S2<NT>& p,
                  const Transformation_E3<NT>& T,
                  const Project_on_xy<NT>& myProjection)
    {
        Vector_E3<NT> ve3(p.x(), p.y(), p.z());
        Vector_E3<NT> ve3nf;
        normalize(ve3, ve3nf);

        Point_E3<NT> pe3 = Point_E3<NT>(0,0,0) + ve3nf;
        Point_E3<NT> pt = T(pe3);
        Point_E2<NT> p2d = myProjection( pt );

        return p2d;
    }
    Point_E2<NT>
    my_projection_of_center(const Transformation_E3<NT>& T,
                            const Project_on_xy<NT>& myProjection)
    {
        Point_E3<NT> pe3(0,0,0);
        Point_E3<NT> pt = T(pe3);
        Point_E2<NT> p2d = myProjection( pt );

        return p2d;
    }
};

#endif // POSTSCRIPT_S2_H
