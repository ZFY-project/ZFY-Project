#pragma once
#include <qwidget.h>
class DragPaint :
    public QWidget
{
    Q_OBJECT

public:
    DragPaint(QWidget* parent = nullptr);
    ~DragPaint();
};

