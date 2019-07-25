/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef POSTSCRIPT_H
#define POSTSCRIPT_H

#include <algorithm>
#include <iterator>

#include <fstream>
#include <list>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using std::endl;

#include "misc/conversions.h" // to_double

// E2
#include "geometry/E2/point_e2.h"
#include "geometry/E2/vector_e2.h"
#include "geometry/E2/circle_e2.h"
#include "geometry/E2/line_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/triangle_e2.h"
#include "geometry/E2/bbox_e2.h"
#include "geometry/E2/interpolation_e2.h"
#include "geometry/E2/transformation_e2.h"

#include "geometry/S1/segment_s1.h"

typedef Point_E2<double>  PS_Point_E2d;
typedef Bbox_E2<double>    PS_Bbox_E2d;

template<class T>
class Postscript;

// Even though the class Postscript computes and outputs in 'double'
// type, we make it parameterized to spare clients having to do type
// conversions.
template<class T>
class Postscript
{
    // Letter: 8.5"x11"
    // A4:     297mmx210mm

private:
    static const double Xoffset;
    static const double Yoffset;
    static const double PS_WIDTH;
    static const double PS_HEIGHT;

    std::string   filename;
    std::ofstream  outfile;

    bool freeze_ps_world;

    Bbox_E2<T>    viewport_world; // from
    PS_Bbox_E2d viewport_world_d; // from (in double)
    PS_Bbox_E2d  viewport_window; // to

    PS_Bbox_E2d  ps_world;      // from
    PS_Bbox_E2d ps_actual;      // to

    Transformation_E2<double> world_to_ps_transform; // combination of the 2 viewport mappings

    T world_to_ps_scale(const T& distance);

    double nodeDiameter;
    double graylevelfill;
    double graylevelstroke;

    double line_width;

    short line_cap;
    short line_join;

    void write_ps_header();

public:
    Postscript() {}
    Postscript(const std::string& filename,
               const Bbox_E2<T>& _viewport_world);

    virtual ~Postscript();

    void set_viewport(const PS_Bbox_E2d & in_viewport_world, const PS_Bbox_E2d & in_viewport_window);

    PS_Point_E2d PS_to_double(const Point_E2<T>& p);

    void moveto(const Point_E2<T>& p);
    void moveto_d(const Point_E2<double>& p);
    void lineto(const Point_E2<T>& p);
    void lineto_d(const Point_E2<double>& p);

    void draw(const Bbox_E2<T>& B);
    void draw_square(const Bbox_E2<T>& B);
    void draw_bounding_box();

    void draw(const Point_E2<T>& P);

private:
    void draw_circle_or_disk(const Point_E2<T>& p, const T& radius);
public:
    void draw_circle(const Point_E2<T>& p, const T& radius);
    void draw_disk(const Point_E2<T>& p, const T& radius);

    void draw_small_circle(const Point_E2<T>& p, double dfraction=150.0);
    void draw_small_disk(const Point_E2<T>& p, double dfraction=150.0);

    void draw_small_disks(const std::vector<Point_E2<T> >& P, double dfraction=150.0);

    void draw(const Circle_E2<T>& c);

private:
    void draw_box_or_square(const Point_E2<T>& p, const T& radius);
public:
    void draw_box(const Point_E2<T>& p, const T& radius);
    void draw_square(const Point_E2<T>& p, const T& radius);

    void draw(const Segment_S1<T>& S,
              const Point_E2<T>& P,              
              const T& radius);

    void draw(const Segment_E2<T>& seg);
    void draw(const Triangle_E2<T>& T, bool fill_triangle=false);

    void draw_polygon(const std::vector<Point_E2<T> > P, bool fill_polygon=false);

    void draw_arrow(const Segment_E2<T>& s,
                    const T & stem_shortening = 0.98,
                    const T & arrow_ratio = 25.0,
                    const T & arrow_angle = 3.0);

    void draw_axes(const T & stem_shortening_x = 0.98,
                   const T & stem_shortening_y = 0.98,
                   const T & arrow_ratio = 25.0,
                   const T & arrow_angle = 3.0);
    void draw_axes(const PS_Bbox_E2d & box,
                   const T & stem_shortening_x = 0.98,
                   const T & stem_shortening_y = 0.98,
                   const T & arrow_ratio = 25.0,
                   const T & arrow_angle = 3.0);

    void draw(const std::string& s, const Point_E2<T>& p, const T& radius);

    void draw_grid(const Bbox_E2<T> & V);
    void draw_grid();

    void set_gray_fill(double graylevel) {
        graylevelfill = graylevel;
        outfile << graylevelfill << " G" << endl;
    }
    void set_gray_stroke(double graylevel) {
        graylevelstroke = graylevel;
        outfile << graylevelstroke << " G" << endl;
    }
    void set_gray(double graylevel) // 0.0: black; 1.0: white
    {
        outfile << graylevel << " G" << endl;
    }

    void set_line_width(double lw) {
        line_width = lw;
        outfile << line_width << " W\n\n";
    }
    void set_line_dashed() {
        outfile << "[2] 0 setdash\n";
    }
    void set_line_undashed() {
        outfile << "[] 0 setdash\n";
    }

    void set_line_cap(int lc) {
        line_cap = lc;
        outfile << line_cap << " LC\n\n";
    }
    void set_line_join(int lj) {
        line_join = lj;
        outfile << line_join << " LJ\n\n";
    }

    short get_line_width() const {
        return line_width;
    }
    short get_line_cap() const {
        return line_cap;
    }
    short get_line_join() const {
        return line_join;
    }

    void newpath() { outfile << "N\n"; }
    void closepath() { outfile << "C\n"; }
    void stroke() { outfile << "S\n"; }
    void fill() { outfile << "F\n"; }
    void translate(const Vector_E2<T>& v) {
        outfile << v.x() << " " << v.y() << " translate\n";
    }

    void close() {
        outfile << "showpage\n";
        outfile.close();
    }

};

template<typename T>
const double
Postscript<T>::Xoffset = 72;    // leave 1" on either

template<typename T>
const double
Postscript<T>::Yoffset = 72;    // letter-sized or A4 paper

template<typename T>
const double
Postscript<T>::PS_WIDTH = 454;  // width = (210 - 25 - 25) / 25.4 * 72 ~= 454

template<typename T>
const double
Postscript<T>::PS_HEIGHT = 648; // height = 9 * 72 = 648


template<class T>
Postscript<T>::Postscript(const std::string& filename,
                          const Bbox_E2<T>& _viewport_world)
    : filename(filename), 
      viewport_world(_viewport_world),
      graylevelfill(0.5), graylevelstroke(0.0),
      line_cap(1), line_join(1)
{
    outfile.open(filename.c_str());
    if( !outfile ) {
        std::cerr<<"error: cannot open file "<<filename<<" for postscript output\n";
        exit(1);
    }

    PS_Point_E2d LL = PS_Point_E2d(to_double(viewport_world.LL().x()), to_double(viewport_world.LL().y()));
    PS_Point_E2d UR = PS_Point_E2d(to_double(viewport_world.UR().x()), to_double(viewport_world.UR().y()));
    viewport_world_d = PS_Bbox_E2d(LL,UR);

    // Only the initial _viewport_world will subsequently be used if set_viewport is called:
    freeze_ps_world = false;
    ps_world = viewport_window = PS_Bbox_E2d(PS_Point_E2d(0,0), PS_Point_E2d(1,1));

    write_ps_header();

    // Transformation_E2<double> T1 = interpolate(viewport_world_d, viewport_window);
    // Transformation_E2<double> T2 = interpolate(ps_world, ps_actual);
    // world_to_ps_transform = T2 * T1;

    // Briefly, while no viewports are defined yet:
    world_to_ps_transform = interpolate(viewport_world_d, ps_actual);
}

template<class T>
Postscript<T>::~Postscript() {
    close();
    outfile.close();
}

// It is the caller's responsibility to ensure that the two Bboxes have the same aspect ratio.
// Subsequent frame of reference for this viewport will be the first argument: in_viewport_world.
template<class T>
void
Postscript<T>::set_viewport(const PS_Bbox_E2d & in_viewport_world, const PS_Bbox_E2d & in_viewport_window)
{
    if( !freeze_ps_world ) {
        ps_world = viewport_world_d;
        freeze_ps_world = true;
    }

    viewport_world_d = in_viewport_world;
    viewport_window = in_viewport_window;

    Transformation_E2<double> T1 = interpolate(viewport_world_d, viewport_window);
    Transformation_E2<double> T2 = interpolate(ps_world, ps_actual);
    world_to_ps_transform = T2 * T1;
}

template<class T>
void
Postscript<T>::write_ps_header()
{
    double boxWidth  = viewport_world_d.width();
    double boxHeight = viewport_world_d.height();

    if(boxWidth / boxHeight > PS_WIDTH / PS_HEIGHT)
        ps_actual = PS_Bbox_E2d(PS_Point_E2d(Xoffset,Yoffset),
                                PS_Point_E2d(Xoffset+PS_WIDTH,
                                             Yoffset+boxHeight/boxWidth * PS_WIDTH));
    else
        ps_actual = PS_Bbox_E2d(PS_Point_E2d(Xoffset,Yoffset),
                                PS_Point_E2d(Xoffset+boxWidth/boxHeight * PS_HEIGHT,
                                             Yoffset+PS_HEIGHT));

    outfile << "%!PS-Adobe-2.0\n"
            << "%%Creator: Postscript\n"
            << "%%Title: " << filename << endl
            << "%%BoundingBox: "
            << ps_actual.LL().x() << " " << ps_actual.LL().y() << " "
            << ps_actual.UR().x() << " " << ps_actual.UR().y() << endl
            << "%%EndComments\n\n";

    outfile << "% Macro definitions:\n"
            << "/N {newpath} def \n"
            << "/M {moveto} def\n"
            << "/L {lineto} def\n"
            << "/C {closepath} def\n"
            << "/S {stroke} def\n"
            << "/F {fill} def\n"
            << "/W {setlinewidth} def\n"
            << "/G {setgray} def\n"
            << "/LC {setlinecap} def\n"
            << "/LJ {setlinejoin} def\n"
            << "% Other setup\n"
            << line_cap  << " setlinecap\n"  // 0: butt caps,    1: round caps,  2: line caps
            << line_join << " setlinejoin\n" // 0: mitter joins, 1: round joins, 2: bevel joins
            << "/Times-Bold findfont\n"
            << "15 scalefont\n"
            << "setfont\n"
            << "%%EndProlog\n\n"
            << std::setprecision(6);

    // set_line_width(0.01);

    nodeDiameter = PS_WIDTH/180.0;
    outfile.flush();
}

template<class T>
void
Postscript<T>::draw_bounding_box()
{
    outfile << graylevelstroke << " G" << endl;

    newpath();
    moveto_d(viewport_world_d.LL());
    lineto_d(PS_Point_E2d(viewport_world_d.UR().x(), viewport_world_d.LL().y()));
    lineto_d(viewport_world_d.UR());
    lineto_d(PS_Point_E2d(viewport_world_d.LL().x(), viewport_world_d.UR().y()));
    closepath();
    stroke();
}

template<class T>
void
Postscript<T>::draw_small_circle(const Point_E2<T>& p, double dfraction)
{
    double worldpsBoxWidth  = viewport_world_d.width();
    draw_circle( p, worldpsBoxWidth / dfraction );
}

template<class T>
void
Postscript<T>::draw_small_disk(const Point_E2<T>& p, double dfraction)
{
    double worldpsBoxWidth  = viewport_world_d.width();
    draw_disk( p, worldpsBoxWidth / dfraction );
}

template<class T>
void
Postscript<T>::draw_small_disks(const std::vector<Point_E2<T> >& P, double dfraction)
{
    typedef typename std::vector<Point_E2<T> >::const_iterator PI;
    for(PI pi=P.begin(); pi!=P.end(); ++pi)
        draw_small_disk(*pi, dfraction);
}

template<class T>
void
Postscript<T>::draw(const Point_E2<T>& p)
{
    draw_small_disk(p);
}

template<class T>
void
Postscript<T>::draw(const Circle_E2<T>& c)
{
    draw_circle(c.center(), c.radius());
}

template<class T>
void
Postscript<T>::draw_circle_or_disk(const Point_E2<T>& p, const T& radius)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(p));
    T rd = world_to_ps_scale(radius);
    outfile << pd.x() << " " << pd.y() << " M" << endl;
    outfile << "N " << pd.x() << " " << pd.y() << " " << rd
            << "  0 360 arc" << endl;
}

template<class T>
void
Postscript<T>::draw_circle(const Point_E2<T>& p, const T& radius)
{
    draw_circle_or_disk(p, radius);
    stroke();
}

template<class T>
void
Postscript<T>::draw_disk(const Point_E2<T>& p, const T& radius)
{
    draw_circle_or_disk(p, radius);
    fill();
}

template<class T>
void
Postscript<T>::draw_box_or_square(const Point_E2<T>& p, const T& radius)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(p));
    T rd = world_to_ps_scale(radius);
    T rd10 = rd/5.0;

    outfile << rd10/2.0 << " W\n";

    PS_Point_E2d LLbegin(pd.x() - 0.8 * rd , pd.y() - rd);

    PS_Point_E2d LL(pd.x() - rd , pd.y() - rd);
    PS_Point_E2d LR(pd.x() + rd , pd.y() - rd);
    PS_Point_E2d UR(pd.x() + rd , pd.y() + rd);
    PS_Point_E2d UL(pd.x() - rd , pd.y() + rd);

    newpath();
    outfile << LLbegin.x() << " " << LLbegin.y() << " M" << endl;
    outfile << LR.x() << " " << LR.y() << " " << UR.x() << " " << UR.y() << " " << rd10 << " arct" << endl;
    outfile << UR.x() << " " << UR.y() << " " << UL.x() << " " << UL.y() << " " << rd10 << " arct" << endl;
    outfile << UL.x() << " " << UL.y() << " " << LL.x() << " " << LL.y() << " " << rd10 << " arct" << endl;
    outfile << LL.x() << " " << LL.y() << " " << LR.x() << " " << LR.y() << " " << rd10 << " arct" << endl;
}

template<class T>
void
Postscript<T>::draw_box(const Point_E2<T>& p, const T& radius)
{
    draw_box_or_square(p, radius);
    stroke();
}

template<class T>
void
Postscript<T>::draw_square(const Point_E2<T>& p, const T& radius)
{
    draw_box_or_square(p, radius);
    fill();
}

template<class T>
void
Postscript<T>::draw(const Segment_S1<T>& S,
                    const Point_E2<T>& P,
                    const T& radius)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(P));
    T rd = world_to_ps_scale(radius);
    double source_angle = 180.0 / M_PI * angle(S.source());
    double target_angle = 180.0 / M_PI * angle(S.target());

    outfile << pd.x() << " " << pd.y() << " "
            << rd << "  "
            << source_angle << " " << target_angle
            << " arc S" << endl;
}

template<class T>
void
Postscript<T>::draw(const Segment_E2<T>& seg)
{
    newpath();
    moveto(seg.source());
    lineto(seg.target());
    stroke();
}

template<class T>
void
Postscript<T>::draw(const Triangle_E2<T>& triangle, bool fill_triangle)
{
    newpath();
    moveto(triangle.P0());
    lineto(triangle.P1());
    lineto(triangle.P2());
    closepath();
    if(fill_triangle)
        fill();
    else
        stroke();
}

template<class T>
void
Postscript<T>::draw_polygon(const std::vector<Point_E2<T> > P, bool fill_polygon)
{
    newpath();
    typedef typename std::vector<Point_E2<T> >::const_iterator PI;
    PI p = P.begin();
    moveto(*p++);
    while(p != P.end())
        lineto(*p++);
    closepath();
    if(fill_polygon)
        fill();
    else
        stroke();
}

//    double W = viewport_world_d.width();
//    double H = viewport_world_d.height();
//    double actual_stem_shortening = (W>H) ? H*(1.0-stem_shortening) : W*(1.0-stem_shortening);

template<class T>
void
Postscript<T>::draw_arrow(const Segment_E2<T>& s,
                          const T & stem_shortening,
                          const T & arrow_ratio,
                          const T & arrow_angle)
{
    Vector_E2<T> stem = s.target() - s.source();
    stem = stem * T(stem_shortening);
    Segment_E2<T> stem_seg(s.source(), s.source() + stem);
    draw(stem_seg);

    Vector_E2<T> v1 = s.source() - s.target();
    v1 = v1 / T(arrow_ratio);
    Vector_E2<T> v2 = v1;    

    v1 = v1 + Vector_E2<T>( v1.y(), -v1.x()) / T(arrow_angle);
    v2 = v2 + Vector_E2<T>(-v2.y(),  v2.x()) / T(arrow_angle);

    Triangle_E2<T> tri(s.target(),
                       Point_E2<T>(s.target() + v1),
                       Point_E2<T>(s.target() + v2));
    draw(tri, true);

//    or, for another arrow style:
//    draw(Segment_E2<T>(s.target(), Point_E2<T>(s.target() + v1)));
//    draw(Segment_E2<T>(s.target(), Point_E2<T>(s.target() + v2)));
}

template<class T>
void
Postscript<T>::draw_axes(const T & stem_shortening_x,
                         const T & stem_shortening_y,
                         const T & arrow_ratio,
                         const T & arrow_angle)
{
    draw_axes(viewport_world_d,
              stem_shortening_x,
              stem_shortening_y,
              arrow_ratio,
              arrow_angle);
}
template<class T>
void
Postscript<T>::draw_axes(const PS_Bbox_E2d & box,
                         const T & stem_shortening_x,
                         const T & stem_shortening_y,
                         const T & arrow_ratio,
                         const T & arrow_angle)
{
    double aspect_ratio = viewport_world_d.width() / viewport_world_d.height();
    T arrow_ratio_x = arrow_ratio;
    T arrow_ratio_y = arrow_ratio;
    if(aspect_ratio > 1.0)
        arrow_ratio_x *= aspect_ratio;
    else
        arrow_ratio_y /= aspect_ratio;        

    Point_E2<T> left(box.LL().x(), 0);
    Point_E2<T> right(box.UR().x(), 0);
    draw_arrow( Segment_E2<T>(left, right), stem_shortening_x, arrow_ratio_x, arrow_angle );

    Point_E2<T> bottom(0, box.LL().y());
    Point_E2<T> top(0, box.UR().y());
    draw_arrow( Segment_E2<T>(bottom, top), stem_shortening_y, arrow_ratio_y, arrow_angle );
}

template<class T>
void
Postscript<T>::draw(const std::string& s, const Point_E2<T>& p, const T& radius)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(p));
    T rd = world_to_ps_scale(radius);
    outfile << pd.x() + rd * 1.25 << " " << pd.y() << " M" << endl;
    outfile << "(" << s << ") show" << endl;
}

template<class T>
void
Postscript<T>::draw_grid(const Bbox_E2<T> & V)
// draw the integer grid; no other options implemented
{
    for(int x = int(V.LL().x())-1;
        x <= int(V.UR().x())+1; ++x)
    {
        Point_E2<T> bottom(x, V.LL().y());
        Point_E2<T> top(x, V.UR().y());
        draw( Segment_E2<T>(bottom, top) );
    }                                                        

    for(int y = int(V.LL().y())-1;
        y <= int(V.UR().y())+1; ++y)
    {
        Point_E2<T> left(V.LL().x(), y);
        Point_E2<T> right(V.UR().x(), y);
        draw( Segment_E2<T>(left, right) );
    }
}

template<class T>
void
Postscript<T>::draw_grid()
{
    draw_grid(viewport_world_d);
}

template<class T>
void
Postscript<T>::draw(const Bbox_E2<T>& B)
{
    newpath();
    moveto(B.LL());
    lineto(Point_E2<T>(B.UR().x(), B.LL().y()));
    lineto(B.UR());
    lineto(Point_E2<T>(B.LL().x(), B.UR().y()));
    closepath();
    stroke();
}

template<class T>
void
Postscript<T>::draw_square(const Bbox_E2<T>& B)
{
    newpath();
    moveto(B.LL());
    lineto(Point_E2<T>(B.UR().x(), B.LL().y()));
    lineto(B.UR());
    lineto(Point_E2<T>(B.LL().x(), B.UR().y()));
    closepath();
    fill();
}

template<class T>
PS_Point_E2d
Postscript<T>::PS_to_double(const Point_E2<T>& p)
{
    return PS_Point_E2d(to_double(p.x()), to_double(p.y()));
}

template<class T>
void
Postscript<T>::moveto(const Point_E2<T>& p)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(p));
    outfile << pd.x() << " " << pd.y() << " M" << endl;
}

template<class T>
void
Postscript<T>::moveto_d(const PS_Point_E2d& p)
{
    PS_Point_E2d pd = world_to_ps_transform(p);
    outfile << pd.x() << " " << pd.y() << " M" << endl;
}

template<class T>
void
Postscript<T>::lineto(const Point_E2<T>& p)
{
    PS_Point_E2d pd = world_to_ps_transform(PS_to_double(p));
    outfile << pd.x() << " " << pd.y() << " L" << endl;
}

template<class T>
void
Postscript<T>::lineto_d(const PS_Point_E2d& p)
{
    PS_Point_E2d pd = world_to_ps_transform(p);
    outfile << pd.x() << " " << pd.y() << " L" << endl;
}

template<typename T>
T
Postscript<T>::world_to_ps_scale(const T& distance)
{
    const double viewport_world_width  = viewport_world_d.width();
    const double viewport_window_width = viewport_window.width();
    const double ps_world_width        = ps_world.width();
    const double ps_actual_width       = ps_actual.width();

    const double x = to_double(distance)
        * (ps_actual_width / ps_world_width)
        * (viewport_window_width / viewport_world_width);

    return x;
}

#endif // POSTSCRIPT_H
