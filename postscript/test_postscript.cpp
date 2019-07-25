// test_postscript.C

typedef double MyDouble;

// Geometry in E2
#include "geometry/E2/point_e2.h"
#include "geometry/E2/segment_e2.h"
#include "geometry/E2/bbox_e2.h"
typedef Point_E2<MyDouble>      Point_E2d;
typedef Segment_E2<MyDouble>  Segment_E2d;
typedef Bbox_E2<MyDouble>        Bbox_E2d;

// PostScript
#include "postscript/postscript.h"
typedef Postscript<MyDouble> Postscript_d;

#include <cstdlib>
#include <cassert>

void test_draw_segment()
{
    Point_E2d P1(-1.0,-1.0);
    Point_E2d P2( 1.0, 1.0);
    Bbox_E2d B(P1, P2);
    Postscript_d myPS("tests/output_1.eps", B);
    myPS.draw_bounding_box();
    Segment_E2d S(P1, P2);
    myPS.draw(S);
    myPS.close();

    assert( !std::system("diff tests/output_1_base.eps tests/output_1.eps") );
}

void test_draw_in_viewport()
{
    Point_E2d P1(0.0, 0.0);
    Point_E2d P2(1.0, 1.0);
    Bbox_E2d B(P1, P2);
    Postscript_d myPS("tests/output_2.eps", B);
    myPS.draw_bounding_box();

    Point_E2d P1w( 0.0, 0.0);
    Point_E2d P2w( 1.0, 1.0);
    Bbox_E2d Bw(P1w, P2w);

    Point_E2d P1a( 0.2, 0.2);
    Point_E2d P2a( 0.4, 0.4);
    Bbox_E2d Ba(P1a, P2a);
    myPS.set_viewport(Bw, Ba);
    myPS.draw_bounding_box();
    Segment_E2d S1(P1w, P2w);
    myPS.draw(S1);

    Point_E2d P1b( 0.6, 0.2);
    Point_E2d P2b( 0.8, 0.4);
    Bbox_E2d Bb(P1b, P2b);    
    myPS.set_viewport(Bw, Bb);
    myPS.draw_bounding_box();

    Point_E2d P3b1( 1.0, 0.0);
    Point_E2d P3b2( 0.0, 1.0);
    Segment_E2d S2(P3b1, P3b2);
    myPS.draw(S2);

    myPS.close();

    assert( !std::system("diff tests/output_2_base.eps tests/output_2.eps") );
}

int main()
{
    test_draw_segment();
    test_draw_in_viewport();
}
