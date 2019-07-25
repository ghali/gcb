
#include "geometry/E2/geometry_e2.h"
#include "geometry/E2/intersection_e2.h"
#include "geometry/free/clip_2.h"
// #include "misc/Epsilon_double.h"

#include <cassert>
#include <algorithm>

typedef Geometry_E2<double> Geometry_E2d;
typedef Geometry_E2d::Point      Point_E2d;
typedef Geometry_E2d::Hyperplane Segment_E2d;
typedef Geometry_E2d::Polygon    Polygon_E2d;

void two_in_two_out()
{
    Point_E2d pnts[] = { Point_E2d(-2,-2), // in
                         Point_E2d(-2, 2), // in
                         Point_E2d( 2, 2), // out
                         Point_E2d( 2,-2)  // out
    };
    Polygon_E2d poly(pnts+0,pnts+sizeof(pnts)/sizeof(Point_E2d));
    Segment_E2d seg = Segment_E2d( Point_E2d(0,0),
                                   Point_E2d(0,1) );

    bool b = positive_half_space_clip<Geometry_E2d>(seg, poly);
    assert(b);

    Point_E2d clip_pnts[] = { Point_E2d( 0, -2),
                              Point_E2d(-2, -2),
                              Point_E2d(-2,  2),
                              Point_E2d( 0,  2) };

    assert(std::equal(poly.begin(), poly.end(), clip_pnts));
}

void two_in_two_on()
{
    Point_E2d pnts[] = { Point_E2d(-2,-2), // in
                         Point_E2d(-2, 2), // in
                         Point_E2d( 0, 2), // on
                         Point_E2d( 0,-2)  // on
    };
    Polygon_E2d poly(pnts+0,pnts+sizeof(pnts)/sizeof(Point_E2d));
    Segment_E2d seg = Segment_E2d( Point_E2d(0,0),
                                   Point_E2d(0,1) );

    bool b = positive_half_space_clip<Geometry_E2d>(seg, poly);
    assert(b);

    Point_E2d clip_pnts[] = { Point_E2d(-2, -2),
                              Point_E2d(-2,  2),
                              Point_E2d( 0,  2),
                              Point_E2d( 0, -2)
    };

    assert(std::equal(poly.begin(), poly.end(), clip_pnts));
}

void two_on_two_out()
{
    Point_E2d pnts[] = { Point_E2d( 0,-2), // on
                         Point_E2d( 0, 2), // on
                         Point_E2d( 2, 2), // out
                         Point_E2d( 2,-2)  // out
    };
    Polygon_E2d poly(pnts+0,pnts+sizeof(pnts)/sizeof(Point_E2d));
    Segment_E2d seg = Segment_E2d( Point_E2d(0,0),
                                   Point_E2d(0,1) );

    bool b = positive_half_space_clip<Geometry_E2d>(seg, poly);

    assert(!b);
    assert(poly.is_empty());
}

void points_on_boundary()
{
    // -0.5      0.300801 0.5
    // -0.5      1.27213  1.46939
    //  0.5      1.27213  1.46939
    //  0.5      0.300801 0.5
    //  0.469388 0.270127 0.469388
    // -0.469388 0.270127 0.469388

    Point_E2d pnts[] = { Point_E2d(6,1),
                         Point_E2d(5,0),
                         Point_E2d(2,0),
                         Point_E2d(1,1),
                         Point_E2d(1,2),
                         Point_E2d(6,2) 
    };
    Polygon_E2d poly(pnts+0,pnts+sizeof(pnts)/sizeof(Point_E2d));
    Segment_E2d seg = Segment_E2d( Point_E2d(7,1),
                                   Point_E2d(0,1) );

    bool b = positive_half_space_clip<Geometry_E2d>(seg, poly);
    assert(b);

    Point_E2d clip_pnts[] = { Point_E2d(6,1),
                              Point_E2d(5,0),
                              Point_E2d(2,0),
                              Point_E2d(1,1)
    };
    assert(std::equal(poly.begin(), poly.end(), clip_pnts));
}

int main()
{
    two_in_two_out();
    two_in_two_on();
    two_on_two_out();
    points_on_boundary();
}
