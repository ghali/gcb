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

#include "misc/conversions.h"
#include "geometry_types.h"

//----------------P3_Perspective_Pipeline_Begin----------------
class Pipeline
{
    const Transformation_P3d T;
    const Perspective_divide_d my_perspective_divide;
    const Project_on_xy_d my_projection;
public:
    Pipeline( const Transformation_P3d& _T ) :
        T(_T), my_perspective_divide(), my_projection() {}

    Point_E2d operator()( const Point_E3d& P1 )
    {
        Point_P3d P2 = Point_P3d( P1 );
        Point_P3d P3 = T( P2 );
        Point_E3d P4 = my_perspective_divide( P3 );
        Point_E2d P5 = my_projection( P4 );
        return P5;
    }
};
//----------------P3_Perspective_Pipeline_End----------------
void render(
            Postscript_d& myPS,
            const Indexed_face_set_d& ifs,
            const Transformation_P3d& T)
{
    Pipeline my_pipeline( T );

    typedef Indexed_face_set_d::Polygon IfsP;
    typedef std::vector<IfsP>::const_iterator My_polygon_iterator;
    typedef std::vector<int>::const_iterator My_vertex_indices_iterator;
    My_polygon_iterator pit = ifs.polygons.begin();
    while( pit != ifs.polygons.end() )
    {
        My_vertex_indices_iterator vit = pit->vertex_indices.begin();
        myPS.moveto( my_pipeline( ifs.getPoint_E3(*vit) ) );

        while( ++vit != pit->vertex_indices.end() )
            myPS.lineto( my_pipeline( ifs.getPoint_E3(*vit) ) );

        myPS.closepath();
        myPS.stroke();
        pit++;
    }
    myPS.close();
}
//----------------------------------------------------------------
void render(const char* filename_in, const char* filename_out,
            int fov, const Point_E3d& viewer)
{
    Indexed_face_set_d ifs;
    assert( !IFS_reader_d::read(ifs, filename_in));

    Transformation_P3d OT(ORTHOGONAL,
                          viewer,
                          Point_E3d(0.0, 0.0, -10.0)); // coi

    Transformation_P3d PT;
    PT.set_perspective(double(fov), 1, 1, 3);
    Transformation_P3d T = PT * OT; // OT is applied first
    Bbox_E2d B(Point_E2d(-5,-5), Point_E2d(5,5));
    Postscript_d myPS(string(filename_out) + "--" + double_to_string_fn(viewer.z()) + ".eps", B);
    Bbox_E2d B_inner(Point_E2d(-4.0,-4.0), Point_E2d(4.0,4.0));
    myPS.draw(B_inner);
    render(myPS, ifs, T);
}
//----------------------------------------------------------------
void render_fov_range(const char* filename_in, const char* filename_out,
                      const Point_E3d& viewer, int fov_min, int fov_max)
{
    Indexed_face_set_d ifs;
    assert( !IFS_reader_d::read(ifs, filename_in));

    Transformation_P3d OT(ORTHOGONAL,
                          viewer,
                          Point_E3d(0.0, 0.0, 0.0)); // coi

    for(int fov=fov_min; fov<=fov_max; fov+=10)
    {
        Transformation_P3d PT;
        PT.set_perspective(double(fov), 1, 1, 3);
        Transformation_P3d T = PT * OT; // OT is applied first
        Bbox_E2d B(Point_E2d(-3,-3), Point_E2d(3,3));
        Postscript_d myPS(filename_out + integer_to_zero_padded_string(fov) + ".eps", B);
        myPS.draw_bounding_box();
        render(myPS, ifs, T);
    }
}
//----------------------------------------------------------------
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
        Transformation_P3d OT(ORTHOGONAL,
                              viewer,
                              Point_E3d(0.0, 0.0, -10.0)); // coi

        Transformation_P3d PT;
        PT.set_perspective(double(fov), 1, 0.1, 100);
        Transformation_P3d T = PT * OT; // OT is applied first
        Bbox_E2d B(Point_E2d(-1.2,-1.2), Point_E2d(1.2,1.2));
        Postscript_d myPS(filename_out + integer_to_zero_padded_string(i, 2) + "--"
                          + double_to_string_fn(viewer.z()) + ".eps", B);
        Bbox_E2d B_inner(Point_E2d(-1.0,-1.0), Point_E2d(1.0,1.0));
        myPS.draw(B_inner);
        render(myPS, ifs, T);
    }
}
//----------------------------------------------------------------
int main()
{
    const double epsilon = 1e-7;
    render_viewer_range("../../../objects/cylinder_12.off",
                        "psout/cylinder_12-",
                        80,
                        Point_E3d(0.05, 0.1, 2.5 + epsilon),
                        Point_E3d(0.05, 0.1, 0.0 + epsilon),
                        6);
}
