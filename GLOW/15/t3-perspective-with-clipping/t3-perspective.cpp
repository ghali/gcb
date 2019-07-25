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
#include <cassert>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "misc/conversions.h"
#include "geometry_types.h"
#include "geometry/T3/intersection_t3.h"
#include "geometry/T3/predicates_t3.h"

//----------------Planes_T3d_Begin----------------
const Plane_T3d Xmax = Plane_T3d(-1,  0,  0, 1);
const Plane_T3d Xmin = Plane_T3d( 1,  0,  0, 1);
const Plane_T3d Ymax = Plane_T3d( 0, -1,  0, 1);
const Plane_T3d Ymin = Plane_T3d( 0,  1,  0, 1);
const Plane_T3d Zmax = Plane_T3d( 0,  0, -1, 1);
const Plane_T3d Zmin = Plane_T3d( 0,  0,  1, 1);
//----------------Planes_T3d_End----------------

//----------------T3_pipeline_with_clipping_1_Begin----------------
class T3_pipeline_with_clipping
{
    const Transformation_T3d T;
    const Perspective_divide_d my_perspective_divide;
    const Project_on_xy_d my_projection;
public:
    T3_pipeline_with_clipping( const Transformation_T3d& _T )
        : T(_T), my_perspective_divide(), my_projection() {}

    Point_T3d pre_clip( const Point_E3d& P1 )
    {
        Point_T3d P2 = Point_T3d( P1 );
        Point_T3d P3 = T( P2 );
        return P3;
    }

    Segment_T3d pre_clip( const Segment_E3d& S1 )
    {
        Point_T3d source = pre_clip( S1.source() );
        Point_T3d target = pre_clip( S1.target() );
        return Segment_T3d( source, target );
    }

    Point_E2d post_clip( const Point_T3d& P3 )
    {
        Point_E3d P4 = my_perspective_divide( P3 );
        Point_E2d P5 = my_projection( P4 );
        return P5;
    }

    Segment_E2d post_clip( const Segment_T3d& S3 )
    {
        Point_E2d source = post_clip( S3.source() );
        Point_E2d target = post_clip( S3.target() );
        return Segment_E2d( source, target );
    }
//----------------T3_pipeline_with_clipping_1_End----------------

//----------------T3_pipeline_with_clipping_2_Begin----------------
    std::pair<bool, Point_E2d>
    operator()( const Point_E3d& P1 )
    {
        Point_T3d P3 = pre_clip( P1 );

        if(
           oriented_side(Xmax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Xmin, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Ymax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Ymin, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Zmax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Zmin, P3) == ON_POSITIVE_SIDE )
        {
            Point_E2d P5 = post_clip( P3 );
            return std::make_pair( true, P5 );
        }
        else
            return std::make_pair( false, Point_E2d() );
    }

    std::pair<bool, Segment_E2d>
    operator()( const Segment_E3d& S1 )
    {
        Segment_T3d S3 = pre_clip( S1 );

        if( positive_half_space_clip( Xmax, S3 ) &&
            positive_half_space_clip( Xmin, S3 ) &&
            positive_half_space_clip( Ymax, S3 ) &&
            positive_half_space_clip( Ymin, S3 ) &&
            positive_half_space_clip( Zmax, S3 ) &&
            positive_half_space_clip( Zmin, S3 )
            )
        {
            Segment_E2d S5 = post_clip( S3 );
            return std::make_pair( true, S5 );
        }
        else
            return std::make_pair( false, Segment_E2d() );
    }
};
//----------------T3_pipeline_with_clipping_2_End----------------

void render(Postscript_d& myPS, const Indexed_face_set_d& ifs, const Transformation_T3d& T)
{
    T3_pipeline_with_clipping my_pipeline( T );

    typedef std::vector<Indexed_face_set_d::Polygon>::const_iterator My_polygon_iterator;
    typedef std::vector<int>::const_iterator My_vertex_indices_iterator;
    My_polygon_iterator pit = ifs.polygons.begin();
    while( pit != ifs.polygons.end() )
    {
        My_vertex_indices_iterator vit_last = pit->vertex_indices.begin();
        My_vertex_indices_iterator vit = vit_last + 1;

        while( vit != pit->vertex_indices.end() ) {

            Point_E3d source = ifs.getPoint_E3(*vit_last);
            Point_E3d target = ifs.getPoint_E3(*vit);

            std::pair<bool, Segment_E2d> p = my_pipeline( Segment_E3d( source, target ) );
            if( p.first )
                myPS.draw( p.second );

            vit_last = vit;
            ++vit;
        }

        vit = pit->vertex_indices.begin();        

        Point_E3d source = ifs.getPoint_E3(*vit_last);
        Point_E3d target = ifs.getPoint_E3(*vit);

        std::pair<bool, Segment_E2d> p = my_pipeline( Segment_E3d( source, target ) );
        if( p.first )
            myPS.draw( p.second );

        ++pit;
    }
    myPS.close();
}

void render(const char* filename_in, const char* filename_out,
            int fov, const Point_E3d& viewer)
{
    Indexed_face_set_d ifs;
    assert( !IFS_reader_d::read(ifs, filename_in));

    Transformation_T3d OT(ORTHOGONAL,
                          viewer,
                          Point_E3d(0.0, 0.0, -10.0)); // coi

    Transformation_T3d PT;
    PT.set_perspective(double(fov), 1, 1, 3);
    Transformation_T3d T = PT * OT; // OT is applied first
    Bbox_E2d B(Point_E2d(-5,-5), Point_E2d(5,5));
    Postscript_d myPS(string(filename_out) + "--" + double_to_string_fn(viewer.z()) + ".eps", B);
    Bbox_E2d B_inner(Point_E2d(-4.0,-4.0), Point_E2d(4.0,4.0));
    myPS.draw(B_inner);
    render(myPS, ifs, T);
}

void render_fov_range(const char* filename_in, const char* filename_out,
                      const Point_T3d& viewer, int fov_min, int fov_max)
{
    Indexed_face_set_d ifs;
    assert( !IFS_reader_d::read(ifs, filename_in));

    Transformation_T3d OT(ORTHOGONAL,
                          viewer,
                          Point_T3d(0.0, 0.0, 0.0)); // coi

    for(int fov=fov_min; fov<=fov_max; fov+=10)
    {
        Transformation_T3d PT;
        PT.set_perspective(double(fov), 1, 1, 3);
        Transformation_T3d T = PT * OT; // OT is applied first
        Bbox_E2d B(Point_E2d(-3,-3), Point_E2d(3,3));
        Postscript_d myPS(filename_out + integer_to_zero_padded_string(fov) + ".eps", B);
        myPS.draw_bounding_box();
        render(myPS, ifs, T);
    }
}

void render_viewer_range(const char* filename_in, const char* filename_out,
                         int fov,
                         const Point_E3d& viewer_min, const Point_E3d& viewer_max, int total)
{
    Indexed_face_set_d ifs;
    assert( !IFS_reader_d::read(ifs, filename_in));

    for(int i=0; i<total; ++i)
    {
        double alpha = 1.0 / (total-1) * double(i);
        Point_E3d viewer = interpolate(viewer_min, viewer_max, alpha);
        Transformation_T3d OT(ORTHOGONAL,
                              viewer,
                              Point_E3d(0.0, 0.0, -10.0)); // coi

        Transformation_T3d PT;
        PT.set_perspective(double(fov), 1, 0.1, 100);
        Transformation_T3d T = PT * OT; // OT is applied first
        Bbox_E2d B(Point_E2d(-1.2,-1.2), Point_E2d(1.2,1.2));
        Postscript_d myPS(filename_out + integer_to_zero_padded_string(i, 2) + "--"
                          + double_to_string_fn(viewer.z()) + ".eps", B);
        Bbox_E2d B_inner(Point_E2d(-1.0,-1.0), Point_E2d(1.0,1.0));
        myPS.draw(B_inner);
        render(myPS, ifs, T);
    }
}

int main()
{
    const double epsilon = 1e-7;
    render_viewer_range("../../../objects/cylinder_12.off",
                        "psout/t3-cylinder_12-clip-",
                        80,
                        Point_E3d(0.05, 0.1, 2.5 + epsilon),
                        Point_E3d(0.05, 0.1, 0.0 + epsilon),
                        6);
}
