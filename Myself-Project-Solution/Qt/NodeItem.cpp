#include "NodeItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
//自定义图块类
NodeItem::NodeItem(QGraphicsItem* parent)
	:QGraphicsObject(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges); // 位置变化发信号->用于触发itemChange函数
}

QRectF NodeItem::boundingRect() const
{
	return QRectF(-25, -25, 80, 50	); // 节点的包围盒，决定点击范围
}

void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setBrush(Qt::lightGray);
	painter->drawRect(boundingRect()); // 画个矩形当模块主体
	painter->drawEllipse(QRectF(-28, -3, 6, 6)); //左引脚小圆
	painter->drawEllipse(QRectF(52, -3, 6, 6));  //右引脚小圆
	//选中：红色粗边框
	if (option->state & QStyle::State_Selected)
	{
		painter->setPen(QPen(Qt::red, 3)); // 红色、3像素粗
		painter->drawRect(boundingRect());
	}
}

QPointF NodeItem::getLeftPin() const
{
	return mapToScene(QPointF(-25, 0));
}

QPointF NodeItem::getRightPin() const
{
	return mapToScene(QPointF(55, 0));
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		emit positionChanged(); // 位置变了就发信号
	}
	return QGraphicsObject::itemChange(change, value);
}
