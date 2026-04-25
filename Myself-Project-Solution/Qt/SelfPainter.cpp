#include "SelfPainter.h"
#include<QPen>
#include<QRectF>
#include<QFont>

SelfPainter::SelfPainter(QWidget* parent)
	:QWidget(parent),m_value(0),m_circleWidth(20),m_progressColor(new QColor(Qt::blue))
{

}

SelfPainter::~SelfPainter()
{
}

void SelfPainter::setValue(int value)
{
	
	if (value >= 0 && value <= 100)
	{
		m_value=value;
		update();
	}
}

int SelfPainter::getValue()
{
	return m_value;
}

void SelfPainter::setCircleWidth(int width)
{
	m_circleWidth= width ;
	update();
}

void SelfPainter::setProgressColor(QColor* color)
{
	delete m_progressColor;
	m_progressColor=color;
	update();
}

void SelfPainter::paintEvent(QPaintEvent* event)
{
	QPainter* painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);// 开启抗锯齿，更平滑
	
	auto side = qMin(width(), height());
	QRectF rect(
		m_circleWidth / 2.0,   // 左边距 = 圆环宽度一半
		m_circleWidth / 2.0,   // 上边距 = 圆环宽度一半
		side - m_circleWidth,  // 宽度 = 最小边 - 圆环宽度
		side - m_circleWidth   // 高度 = 最小边 - 圆环宽度
	);
	//创建着色圆环
	QPen penBackground;               // 创建画笔
	penBackground.setColor(Qt::lightGray); // 灰色（背景）
	penBackground.setWidth(m_circleWidth); // 画笔宽度 = 圆环宽度
	painter->setPen(penBackground);
	painter->drawArc(rect, 0, 360 * 16);

	// 设置进度颜色画笔 + 设置画笔宽度
	QPen progressPen;
	progressPen.setColor(*m_progressColor);      // 进度颜色
	progressPen.setWidth(m_circleWidth);         // 画笔宽度 = 圆环宽度
	progressPen.setCapStyle(Qt::RoundCap);       // 圆角（可选，更好看）
	painter->setPen(progressPen);
	// 计算进度对应的圆弧角度
	int angle = m_value * 360 / 100;            // 百分比 → 角度
	// 调用 drawArc 画对应角度的圆弧（从顶部开始）
	painter->drawArc(rect, 90 * 16, -angle * 16);

	// 设置黑色画笔
	painter->setPen(Qt::black);

	// 调整字体大小
	QFont font;
	font.setPointSize(18);       // 字体大小
	painter->setFont(font);

	// 3. 在矩形中心绘制进度百分比
	painter->drawText(rect, Qt::AlignCenter, QString::number(m_value) + "%");

}
