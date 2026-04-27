#include "MyWidget.h"
#include <QApplication>
#include<SelfPainter.h>
#include"GroupWidget.h"
#include"MyGLWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;
    w.show();

    return a.exec();
}