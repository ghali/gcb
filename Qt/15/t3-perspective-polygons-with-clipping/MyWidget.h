#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "graphics_pipeline/T3_pipeline_with_clipping.h"
#include "graphics_pipeline/geometry_types.h"
#include <algorithm> // for std::min
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
        // const string dir = "c:/Documents and Settings/ghali/Misc/books/igc/objects/";
        // const string dir = "/Users/me/ghali/gcb/chaps/code/objects/";
        const string dir = "../../../objects/";

        const char * src = "cylinder_12.off";
        if( IFS_reader_d::read(ifs, dir + src, this) ) {
            QMessageBox::information(this, "Reading",
                                     QString("Unable to read %1%2").arg(dir.c_str()).arg(src),
                                     QMessageBox::Ok);
            exit(1);
        }

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

        typedef std::vector<Indexed_face_set_d::Polygon>::const_iterator My_polygon_iterator;
        typedef std::vector<int>::const_iterator My_vertex_indices_iterator;
        for(My_polygon_iterator pit = ifs.polygons.begin();
            pit != ifs.polygons.end();
            ++pit)
        {
            Polygon_E3d poly_e3;

            typedef std::vector<int>::const_iterator VIT;
            for(VIT vi = pit->vertex_indices.begin(); vi != pit->vertex_indices.end(); ++vi)
                poly_e3.push_back(ifs.vertices[*vi]);

            std::pair<bool, Polygon_E3d> b_poly_e3 = my_pipeline( poly_e3 );
            if(b_poly_e3.first)
            {
                QPainterPath path;
                typedef Polygon_E3d::Point_const_iterator PCI;
                for(PCI point_it = b_poly_e3.second.begin(); point_it != b_poly_e3.second.end(); ++point_it)
                {
                    QPointF qpf = to_QPointF( my_projection(*point_it));
                    if(point_it == b_poly_e3.second.begin())
                        path.moveTo( qpf );
                    else
                        path.lineTo( qpf );
                }
                path.closeSubpath();
                painter.setBrush(QBrush(QColor(128, 128, 128, 128)));
                painter.drawPath(path);
            }
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
