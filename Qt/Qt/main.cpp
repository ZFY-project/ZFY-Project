#include "MyWidget.h"
#include <QApplication>
#include<SelfPainter.h>
#include"GroupWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();
    GroupWidget x;
    x.show();
    return a.exec();
}