#include "MyWidget.h"
#include<QDebug>
#include<QVBoxLayout>
#include "GroupWidget.h"
MyWidget::MyWidget(QWidget* parent):QWidget(parent)
{
    resize(640, 480);
    // 直接new你的自定义组合控件
    GroupWidget* group = new GroupWidget(this);

    // 绑定组合控件的自定义信号
    connect(group, &GroupWidget::btnClicked, this, [=]() {
        qDebug() << "组合控件按钮点击：" << group->getText();
        });

}

MyWidget::~MyWidget()
{

}

void MyWidget::mousePressEvent(QMouseEvent* ev)
{

}

void MyWidget::paintEvent(QPaintEvent* event)
{
   
}
