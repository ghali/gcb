
#include "Hello_Segment.h"
#include <QtGui>

//----------------main_Begin----------------
int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Hello_Segment * hs = new Hello_Segment;
    hs->show();
    return app.exec();
}
//----------------main_End----------------
