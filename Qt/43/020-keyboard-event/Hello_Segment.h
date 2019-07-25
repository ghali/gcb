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
    void render(QPaintDevice * device)
    {
        QPainter painter(device);
        QPointF A( 50.0,  50.0);
        QPointF B(150.0, 150.0);
        painter.drawLine(A, B);
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
