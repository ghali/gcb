#ifndef T3_PIPELINE_WITHOUT_CLIPPING_H
#define T3_PIPELINE_WITHOUT_CLIPPING_H

#include "misc/conversions.h"
#include "geometry_types.h"

//----------------T3_pipeline_without_clipping_Begin----------------
class T3_pipeline_without_clipping
{
    const Transformation_T3d T;
    const Perspective_divide_d my_perspective_divide;
    const Project_on_xy_d my_projection;
public:
    T3_pipeline_without_clipping( const Transformation_T3d& _T ) :
        T(_T), my_perspective_divide(), my_projection() {}

    Point_E2d operator()( const Point_E3d& P1 )
    {
        const Point_T3d P2 = Point_T3d( P1 );
        const Point_T3d P3 = T( P2 );
        const Point_E3d P4 = my_perspective_divide( P3 );
        const Point_E2d P5 = my_projection( P4 );
        return P5;
    }
};
//----------------T3_pipeline_without_clipping_End----------------

#endif // T3_PIPELINE_WITHOUT_CLIPPING_H
