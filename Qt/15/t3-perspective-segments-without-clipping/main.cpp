
#include "MyWidget.h"
#include <QtGui>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    MyWidget * w = new MyWidget;
    w->show();
    return app.exec();
}
