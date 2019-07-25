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
        QPainter painter(this);
        const QPointF A( 50.0,  50.0);
        const QPointF B(150.0, 150.0);
        painter.drawLine(A, B);
    }
};
//----------------Hello_Segment_End----------------

#endif // HELLO_SEGMENT_H
