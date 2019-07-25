#ifndef HELLO_SEGMENT_H
#define HELLO_SEGMENT_H

#include <QtGui>
#include <cmath>

//----------------Hello_Segment_Begin----------------
class Hello_Segment : public QWidget
{
public:
    Hello_Segment(QWidget * parent = 0)
        : QWidget(parent)
    {
        basic_timer.start(5, this); // interval between drawings
        elapsed_timer.start();      // time since start
        move(2300,600);
    }

protected:
    virtual QSize sizeHint() const { return QSize(200, 200); }
    virtual void paintEvent(QPaintEvent * /*event*/)
    {
        render(this);
    }
    virtual void render(QPaintDevice * device)
    {
        QPainter painter(device);
        painter.setRenderHint(QPainter::Antialiasing, true);

        const QRectF window(QPointF(-1.0, -1.0), QPointF(1.0, 1.0));
        const QRectF device_window(0, 0, device->width(), device->height());

        QRectF w2 = get_centered_window(window, device_window);

        QTransform T = interpolate_and_yflip(w2, device_window);
        painter.setTransform( T );

        const QPointF O( 0.0,  0.0);
        qreal minutes = - elapsed_timer.elapsed() / 60.0;
        qreal hours   = minutes / 12.0;
        const qreal hour_length = 0.6;
        const qreal minute_length = 0.9;
        QPointF H(  hour_length * std::cos(hours),     hour_length * std::sin(hours));
        QPointF M(minute_length * std::cos(minutes), minute_length * std::sin(minutes));
        painter.drawLine(O, H);
        painter.drawLine(O, M);
    }
    QTransform interpolate_and_yflip(const QRectF & from, const QRectF & to)
    {
        QTransform T;
        T.translate( to.bottomLeft().x(), to.bottomLeft().y() ); // third: translate from origin
        T.scale(to.width() / from.width(), - to.height() / from.height() ); // second: scale
        T.translate( - from.bottomLeft().x(), - from.topLeft().y() ); // first: translate to origin
        return T;
    }
    QRectF get_centered_window(const QRectF & w /*input*/, const QRectF & d /*reference*/)
    {
        const qreal w_ar = w.width()/w.height();
        const qreal d_ar = d.width()/d.height();

        if(d_ar > w_ar) {
            qreal new_w_width = w.height() * d_ar;
            return QRectF( w.topLeft().x() - (new_w_width - w.width()) / 2.0 , w.topLeft().y(),
                           new_w_width, w.height() );
        }
        else {
            qreal new_w_height = w.width() / d_ar;
            return QRectF( w.topLeft().x(), w.topLeft().y() - (new_w_height - w.height()) / 2.0,
                           w.width(), new_w_height );
        }
    }
    virtual void timerEvent(QTimerEvent * /*event*/)
    {
        update();
    }
//----------------Hello_Segment_End----------------

    virtual void keyPressEvent(QKeyEvent * event)
    {
        QPrinter printer;
        switch(event->key()) {
        case Qt::Key_P:
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("Hello_Segment.pdf");
            render(&printer);
            QMessageBox::information(this, "Print", "Document printed", QMessageBox::Ok);
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    }
private:
    QBasicTimer basic_timer;
    QElapsedTimer elapsed_timer;
};

#endif // HELLO_SEGMENT_H
