#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "graphics_pipeline/T3_pipeline_without_clipping.h"
#include "graphics_pipeline/geometry_types.h"
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
          // viewer_min( Point_E3d(0.05, 0.1, 2.5 + epsilon) ),
          // viewer_max( Point_E3d(0.05, 0.1, 0.0 + epsilon) ),
          viewer_min( Point_E3d(0, 0, /*2.5*/  2.5 + epsilon) ),
          viewer_max( Point_E3d(0, 0, /*0.0*/  0.0 + epsilon) ),
          i(0),
          total(50),
          fov(80)
    {
        const char * src = "/Users/me/ghali/gcb/chaps/code/objects/cylinder_12.off";
        assert( !IFS_reader_d::read(ifs, src, this) );

        find_transformation();

        B_inner = QRectF (QPointF(-1.0,-1.0), QPointF(1.0,1.0));
    }
protected:
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
        // painter.drawText(QPointF(5,10), QString("%1").arg(i));

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
        T3_pipeline_without_clipping my_pipeline( T );

        typedef std::vector<Indexed_face_set_d::Polygon>::const_iterator My_polygon_iterator;
        typedef std::vector<int>::const_iterator My_vertex_indices_iterator;
        My_polygon_iterator pit = ifs.polygons.begin();
        while( pit != ifs.polygons.end() )
        {
            My_vertex_indices_iterator vit = pit->vertex_indices.begin();

            QPainterPath path;
            path.moveTo( to_QPointF(my_pipeline( ifs.getPoint_E3(*vit) )) );

            while( ++vit != pit->vertex_indices.end() )
                path.lineTo( to_QPointF(my_pipeline( ifs.getPoint_E3(*vit) )) );

            path.closeSubpath();
            painter.drawPath(path);
            pit++;
        }
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

    Indexed_face_set_d ifs;
    Transformation_T3d T;
    QRectF B_inner;
};

#endif // MYWIDGET_H
