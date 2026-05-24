#include "NodeItem.h"
#include <QPainter>
//自定义节点类
NodeItem::NodeItem(QGraphicsItem* parent)
	:QGraphicsObject(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges); // 位置变化发信号->用于触发itemChange函数
}

QRectF NodeItem::boundingRect() const
{
	return QRectF(-25, -25, 50, 50	); // 节点的包围盒，决定点击范围
}

void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setBrush(Qt::lightGray);
	painter->drawEllipse(boundingRect()); // 画个圆当节点
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemPositionChange && scene()) {
		emit positionChanged(); // 位置变了就发信号
	}
	return QGraphicsObject::itemChange(change, value);
}
