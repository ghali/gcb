#ifndef MYWIDGET_H
#define MYWIDGET_H

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#include "graphics_pipeline/T3_pipeline_with_clipping.h"
#include "geometry_types.h"
#include <QtGui>

QPointF to_QPointF(const Point_E2d & p)
{
    return QPointF(p.x(), p.y());
}

const double epsilon = 1e-7;

class MyWidget : public QWidget
{
public:
    MyWidget(QWidget * parent = 0)
        : QWidget(parent),
          viewer_min( Point_E3d(0.05, 0.1, 2.5 + epsilon) ),
          viewer_max( Point_E3d(0.05, 0.1, 0.0 + epsilon) ),
          i(0),
          total(50),
          fov(90)
    {
        this->move(2200,600);
        build_scene();
        find_transformation();
        B_inner = QRectF (QPointF(-1.0,-1.0), QPointF(1.0,1.0));
    }
protected:
    void build_scene()
    {
        Point_S2d A( 0.8, 1,1);
        Point_S2d B( 1,-1,1);
        Point_S2d C(-1, 1,1);

        points.push_back(A);
        //points.push_back(B);
        //points.push_back(C);

        //segments.push_back(Segment_S2d(A, B));
        //segments.push_back(Segment_S2d(B, C));
        //segments.push_back(Segment_S2d(C, A));

        //Polygon_S2d poly;
        //poly.push_back(A);
        //poly.push_back(B);
        //poly.push_back(C);
        //polygons.push_back(poly);

        Circle_S2d acirc(A);
        //Circle_S2d bcirc(B);
        //Circle_S2d ccirc(C);
        circles.push_back(acirc);
        //circles.push_back(bcirc);
        //circles.push_back(ccirc);
    }
    void find_transformation()
    {
        double alpha = 1.0 / (total-1) * double(i);
        Point_E3d viewer = interpolate(viewer_min, viewer_max, alpha);
        Transformation_T3d OT(ORTHOGONAL,
                              viewer,
                              Point_E3d(0.0, 0.0, -10.0)); // coi

        Transformation_T3d PT;
        PT.set_perspective(double(fov), 1, 0.1, 100);
        /*Transformation_T3d*/ T = PT * OT; // OT is applied first
    }

    QSize sizeHint() const { return QSize(200, 200); }
    QTransform interpolate_and_yflip(const QRectF & from, const QRectF & to)
    {
        QTransform T;
        T.translate( to.bottomLeft().x(), to.bottomLeft().y() ); // third: translate from origin
        T.scale(to.width() / from.width(), - to.height() / from.height() ); // second: scale
        T.translate( - from.bottomLeft().x(), - from.topLeft().y() ); // first: translate to origin
        return T;
    }
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.drawText(QPointF(5,10), QString("%1").arg(i));

        const QRectF w(QPointF(-1.2,-1.2), QPointF(1.2,1.2));

        const QRectF d(0, 0, this->width(), this->height());
        QTransform T = interpolate_and_yflip(w, d);
        painter.setTransform( T );
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.drawRect(B_inner);

        render(painter);
    }

    void render(QPainter & painter)
    {
        const T3_pipeline_with_clipping my_pipeline( T );

        const Project_on_xy_d my_projection = Project_on_xy_d();

        painter.setBrush(QBrush(QColor(128, 128, 128, 128)));

        draw_points(painter, my_pipeline, my_projection);
        draw_segments(painter, my_pipeline, my_projection);
        draw_circles(painter, my_pipeline, my_projection);
    }
    void draw_points(QPainter & painter,
                     const T3_pipeline_with_clipping & my_pipeline,
                     const Project_on_xy_d & my_projection)
    {
        QPainterPath path;
        typedef std::vector<Point_S2d>::const_iterator PCI;
        for(PCI p = points.begin(); p != points.end(); ++p)
        {
            Point_E3d origin(0,0,0);
            Vector_E3d ve3 = p->get_Direction_E3().getVector_E3();
            Point_E3d pe3 = origin + ve3;

            Segment_E3d seg(origin, pe3);
            draw_segment_e3(seg, path, my_pipeline, my_projection);
        }
        painter.drawPath(path);
    }
    void draw_segment_e3(const Segment_E3d & seg, QPainterPath & path,
                         const T3_pipeline_with_clipping & my_pipeline,
                         const Project_on_xy_d & my_projection)
    {
        std::pair<bool, Segment_E3d> seg_tr = my_pipeline(seg);
        if(seg_tr.first)
        {
            QPointF qpf_1 = to_QPointF( my_projection(seg_tr.second.source()));
            path.moveTo( qpf_1 );
            QPointF qpf_2 = to_QPointF( my_projection(seg_tr.second.target()));
            path.lineTo( qpf_2 );
        }
    }
    // void draw_segment_s2(
    //                      )
    // {
    // }
    void draw_segments(QPainter & painter,
                       const T3_pipeline_with_clipping & my_pipeline,
                       const Project_on_xy_d & my_projection)
    {
        QPainterPath path;
        typedef std::vector<Segment_S2d>::const_iterator SCI;
        for(SCI seg = segments.begin(); seg != segments.end(); ++seg)
        {
            const MyDouble increment = 0.075;
            Point_E3d last;
            for(MyDouble u = 0.0; u < 1.0; u += increment )
            {
                const Point_E3d origin(0,0,0);
                Point_S2d  ps2 = slerp(seg->source(), seg->target(), u);
                Vector_E3d ve3 = ps2.get_Direction_E3().getVector_E3();
                Point_E3d  current = origin + ve3;

                if(u != 0)
                    draw_segment_e3( Segment_E3d(last, current), path, my_pipeline, my_projection);

                last = current;
            }
        }
        painter.drawPath(path);
    }

    void draw_circles(QPainter & painter,
                      const T3_pipeline_with_clipping & my_pipeline,
                      const Project_on_xy_d & my_projection)
    {
        QPainterPath path;
        typedef std::vector<Circle_S2d>::const_iterator CCI;
        for(CCI circle = circles.begin(); circle != circles.end(); ++circle)
        {
            Point_S2d base1 = circle->base1();
            Point_S2d base2 = circle->base2();

            const double DIVISIONS = 60.0;
            Point_E3d last;
            for(double theta = 0.0; theta <= 2*M_PI + M_PI/2*DIVISIONS; theta += M_PI/DIVISIONS)
            {
                Point_E3d origin(0,0,0);
                Point_S2d ps2 = base1 * cos(theta) + base2 * sin(theta);
                Vector_E3d ve3 = ps2.get_Direction_E3().getVector_E3();
                Point_E3d  current = origin + ve3;

                if(theta != 0)
                    draw_segment_e3( Segment_E3d(last, current), path, my_pipeline, my_projection);

                last = current;
            }
        }
        painter.drawPath(path);
    }

    void keyPressEvent(QKeyEvent * event)
    {
        switch( event->key() ) {
        case Qt::Key_Up:
            i = (i+1) % total;
            find_transformation();
            update();
            break;
        case Qt::Key_Down:
            i = i ? (i-1) : (total - 1);
            find_transformation();
            update();
            break;
        case Qt::Key_Escape:
            close();
        default:
            QWidget::keyPressEvent(event);
        }
    }

    const Point_E3d viewer_min;
    const Point_E3d viewer_max;
    int i;
    const int total;
    const int fov;

    std::vector<Point_S2d> points;
    std::vector<Segment_S2d> segments;
    std::vector<Polygon_S2d> polygons;
    std::vector<Circle_S2d> circles;

    Transformation_T3d T;
    QRectF B_inner;
};

#endif // MYWIDGET_H
