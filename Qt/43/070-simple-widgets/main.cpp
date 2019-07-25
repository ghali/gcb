
#include "Hello_Segment.h"
#include <QtGui>

//----------------main_Begin----------------
int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    QVBoxLayout * vLayout = new QVBoxLayout;

    Hello_Segment * hs = new Hello_Segment;
    vLayout->addWidget(hs);

    QPushButton * button = new QPushButton("Toggle &Circle");
    vLayout->addWidget(button);

    QObject::connect(button, SIGNAL(released()), hs, SLOT(toggle_circle()));

    QWidget * widget = new QWidget;
    widget->setLayout(vLayout);
    widget->show();

    return app.exec();
}
//----------------main_End----------------
