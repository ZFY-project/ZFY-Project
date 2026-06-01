#include "EdgeItem.h"
#include <QPen>
#include <QLineF>
#include <QStyleOptionGraphicsItem>
#include<QPainter>

EdgeItem::EdgeItem(NodeItem* startNode, NodeItem* endNode, QGraphicsItem* parent)
    : QGraphicsLineItem(parent)
    , m_startNode(startNode)
    , m_endNode(endNode)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2));
    updatePos();

    connect(m_startNode, &NodeItem::positionChanged, this, &EdgeItem::updatePos);
    connect(m_endNode, &NodeItem::positionChanged, this, &EdgeItem::updatePos);
    setZValue(-1);
}

EdgeItem::~EdgeItem()
{
}

void EdgeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(m_p1, m_p2); //横
    painter->drawLine(m_p2, m_p3); //竖
    painter->drawLine(m_p3, m_p4); //横
}


void EdgeItem::updatePos()
{
    //起点取右引脚，终点取左引脚
    m_p1 = m_startNode->getRightPin();//起点：输出(右)
    m_p4 = m_endNode->getLeftPin();   //终点：输入(左)
    qreal midY = (m_p1.y() + m_p4.y()) / 2;
    // 横竖横：先水平→竖直→水平
    m_p2 = QPointF((m_p1.x() + m_p4.x()) / 2, m_p1.y());
    m_p3 = QPointF((m_p1.x() + m_p4.x()) / 2, m_p4.y());
    
}