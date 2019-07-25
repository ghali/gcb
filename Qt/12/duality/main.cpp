
#include "MyGraphicsScene.h"

#include <QtGui>

// was: 2011-Feb-question-try7-store-nodes

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    MyGraphicsScene * scene = new MyGraphicsScene;
    QGraphicsView * view = new QGraphicsView(scene);

    view->setTransform( QTransform().scale(1.0, -1.0) ); // revert y-axis
    view->resize(QSize(640,480));
    view->move(300,200);
    view->show();               // show before fit
    view->setRenderHints(QPainter::Antialiasing);
    view->fitInView(view->scene()->sceneRect(), Qt::KeepAspectRatio);

    return app.exec();
}
