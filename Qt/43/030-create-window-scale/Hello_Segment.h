#ifndef HELLO_SEGMENT_H
#define HELLO_SEGMENT_H

#include <QtGui>

//----------------Hello_Segment_Begin----------------
class Hello_Segment : public QWidget
{
public:
    Hello_Segment(QWidget * parent = 0)
        : QWidget(parent)
    {}

protected:
    virtual QSize sizeHint() const { return QSize(200, 200); }
    virtual void paintEvent(QPaintEvent * /*event*/)
    {
        render(this);
    }
    virtual void render(QPaintDevice * device)
    {
        QPainter painter(device);

        const QRectF window(QPointF(-5.0, -4.0), QPointF(5.0, 4.0));
        const QRectF device_window(0, 0, device->width(), device->height());
        QTransform T = interpolate_and_yflip(window, device_window);
        painter.setTransform( T );

        QPointF A(-4.0, -3.0);
        QPointF B( 4.0,  3.0);
        painter.drawLine(A, B);
    }
    QTransform interpolate_and_yflip(const QRectF & from, const QRectF & to)
    {
        QTransform T;
        T.translate( to.bottomLeft().x(), to.bottomLeft().y() ); // third: translate from origin
        T.scale(to.width() / from.width(), - to.height() / from.height() ); // second: scale
        T.translate( - from.bottomLeft().x(), - from.topLeft().y() ); // first: translate to origin
        return T;
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
};

#endif // HELLO_SEGMENT_H
