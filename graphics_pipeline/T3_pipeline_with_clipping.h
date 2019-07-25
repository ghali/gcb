#ifndef T3_PIPELINE_WITH_CLIPPING_H
#define T3_PIPELINE_WITH_CLIPPING_H

#include <iostream>
using std::cout; using std::endl;

#include "misc/conversions.h"
#include "geometry_types.h"
#include "geometry/T3/intersection_t3.h"
#include "geometry/T3/predicates_t3.h"
#include "geometry/free/clip_2.h"

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
public:
    T3_pipeline_with_clipping( const Transformation_T3d & _T )
        : T(_T), my_perspective_divide() {}

    Point_T3d pre_clip( const Point_E3d& P1 ) const
    {
        Point_T3d P2 = Point_T3d( P1 );
        Point_T3d P3 = T( P2 );
        return P3;
    }

    Segment_T3d pre_clip( const Segment_E3d & S1 ) const
    {
        Point_T3d source = pre_clip( S1.source() );
        Point_T3d target = pre_clip( S1.target() );
        return Segment_T3d( source, target );
    }

    Polygon_T3d pre_clip( const Polygon_E3d & poly_e3 ) const
    {
        Polygon_T3d poly_t3;
        typedef Polygon_E3d::Point_const_iterator PCI;
        for(PCI pe3 = poly_e3.begin(); pe3 != poly_e3.end(); ++pe3) {
            const Point_T3d pt3 = pre_clip( *pe3 );
            poly_t3.push_back(pt3);
        }
        return poly_t3;
    }

    Point_E3d post_clip( const Point_T3d & P3 ) const
    {
        Point_E3d P4 = my_perspective_divide( P3 );
        return P4;
    }

    Segment_E3d post_clip( const Segment_T3d & S3 ) const
    {
        Point_E3d source = post_clip( S3.source() );
        Point_E3d target = post_clip( S3.target() );
        return Segment_E3d( source, target );
    }

    Polygon_E3d post_clip( const Polygon_T3d & poly_t3 ) const
    {
        Polygon_E3d poly_e3;
        typedef Polygon_T3d::Point_const_iterator PCI;
        for(PCI pt3 = poly_t3.begin(); pt3 != poly_t3.end(); ++pt3) {
            const Point_E3d pe3 = post_clip( *pt3 );
            poly_e3.push_back(pe3);
        }
        return poly_e3;
    }
//----------------T3_pipeline_with_clipping_1_End----------------

//----------------T3_pipeline_with_clipping_2_Begin----------------
    std::pair<bool, Point_E3d>
    operator()( const Point_E3d & P1 ) const
    {
        Point_T3d P3 = pre_clip( P1 );

        if(oriented_side(Xmax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Xmin, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Ymax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Ymin, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Zmax, P3) == ON_POSITIVE_SIDE &&
           oriented_side(Zmin, P3) == ON_POSITIVE_SIDE )
        {
            Point_E3d P5 = post_clip( P3 );
            return std::make_pair( true, P5 );
        }
        else
            return std::make_pair( false, Point_E3d() );
    }

    std::pair<bool, Segment_E3d>
    operator()( const Segment_E3d & S1 ) const
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
            Segment_E3d S5 = post_clip( S3 );
            return std::make_pair( true, S5 );
        }
        else
            return std::make_pair( false, Segment_E3d() );
    }

    std::pair<bool, Polygon_E3d>
    operator()( const Polygon_E3d & poly_e3 ) const
    {
        Polygon_T3d poly_t3 = pre_clip( poly_e3 );

        if( positive_half_space_clip<Geometry_T3d>( Xmax, poly_t3 ) &&
            positive_half_space_clip<Geometry_T3d>( Xmin, poly_t3 ) &&
            positive_half_space_clip<Geometry_T3d>( Ymax, poly_t3 ) &&
            positive_half_space_clip<Geometry_T3d>( Ymin, poly_t3 ) &&
            positive_half_space_clip<Geometry_T3d>( Zmax, poly_t3 ) &&
            positive_half_space_clip<Geometry_T3d>( Zmin, poly_t3 )
            )
        {
            Polygon_E3d poly_e3 = post_clip( poly_t3 );
            return std::make_pair( true, poly_e3 );
        }
        else
            return std::make_pair( false, Polygon_E3d() );
    }
};
//----------------T3_pipeline_with_clipping_2_End----------------

#endif // T3_PIPELINE_WITH_CLIPPING_H
