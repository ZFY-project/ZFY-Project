#pragma once
#include <qwidget.h>
#include<QPainter>
#include<QColor>
class SelfPainter :
    public QWidget
{
    Q_OBJECT
public:
    SelfPainter(QWidget* parent = nullptr);
    ~SelfPainter();
    void setValue(int value);
    int getValue();
    void setCircleWidth(int width);
    void setProgressColor(QColor* color);
protected:
    void paintEvent(QPaintEvent* event)override;
private:
    int m_value;          // 存储进度值（0~100）
    int m_circleWidth;    // 存储圆环宽度（像素）
    QColor *m_progressColor;// 存储进度条颜色
};

