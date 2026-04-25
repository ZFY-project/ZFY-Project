#include "MyWidget.h"
#include<QDebug>
#include<QVBoxLayout>
#include "GroupWidget.h"
#include"SelfPainter.h"
#include<QSlider>
#include<QVBoxLayout >
MyWidget::MyWidget(QWidget* parent):QWidget(parent)
{
    //组合控件
    resize(640, 480);
    // 直接new你的自定义组合控件
    GroupWidget* group = new GroupWidget(this);

    // 绑定组合控件的自定义信号
    connect(group, &GroupWidget::btnClicked, this, [=]() {
        qDebug() << "组合控件按钮点击：" << group->getText();
    });

    //自绘控件
    SelfPainter* m_progress = new SelfPainter(this);
    m_progress->setFixedSize(150, 150);

    // 3. 调用接口设置【自定义样式】
    m_progress->setCircleWidth(25);          // 设置圆环宽度
    //m_progress->setProgressColor(new QColor(255, 0, 0)); // 设置进度颜色（红色）
    m_progress->setValue(0);                // 设置当前进度 66%

    QSlider* slider = new QSlider(Qt::Horizontal,this);
    slider->setRange(0, 100);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(group);
    layout->addWidget(m_progress);
    layout->addWidget(slider);
    
    connect(slider, &QSlider::valueChanged, m_progress, &SelfPainter::setValue);
    connect(group->getBtn(), &QPushButton::clicked, group->getEdit(), [=]() {
        group->getEdit()->setText(QString::number(m_progress->getValue()) + "%");
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
