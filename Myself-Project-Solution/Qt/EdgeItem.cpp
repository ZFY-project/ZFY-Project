#include "EdgeItem.h"
#include <QPen>
#include <QLineF>

EdgeItem::EdgeItem(NodeItem* startNode, NodeItem* endNode, QGraphicsItem* parent)
    : QGraphicsLineItem(parent)
    , m_startNode(startNode)
    , m_endNode(endNode)
{
    setPen(QPen(Qt::black, 2));
    updateLine();

    connect(m_startNode, &NodeItem::positionChanged, this, &EdgeItem::updateLine);
    connect(m_endNode, &NodeItem::positionChanged, this, &EdgeItem::updateLine);
    setZValue(-1);
}

EdgeItem::~EdgeItem()
{
}

void EdgeItem::updateLine()
{
    QPointF s = m_startNode->pos();
    QPointF e = m_endNode->pos();
    setLine(QLineF(s, e));
}