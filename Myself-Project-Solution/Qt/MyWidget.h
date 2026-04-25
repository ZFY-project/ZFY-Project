#pragma once
#include<QWidget>
#include<QLineEdit>
#include <QPainter>
#include <QMouseEvent>
#include<QPushButton>
class MyWidget :
    public QWidget
{
   Q_OBJECT
public:
    explicit MyWidget(QWidget* parent = nullptr);
    ~MyWidget();

    void mousePressEvent(QMouseEvent* ev)override;
    void paintEvent(QPaintEvent* event)override;
};

