#include <QApplication>
#include "MyGLWidget.h"
#include "WorkWidget.h"
#include "SelfPainter.h"
#include "MyWidget.h"
#include "DragPaint.h"
#include "SegmentWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SegmentWidget w;
    w.show();
    return a.exec();
}
