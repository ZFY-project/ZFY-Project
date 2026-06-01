#pragma once
#include <QObject>
#include <QGraphicsLineItem>
#include "NodeItem.h"
//自定义节点连线类
class EdgeItem : public QObject,public QGraphicsLineItem
{
    Q_OBJECT
public:
    EdgeItem(NodeItem* startNode, NodeItem* endNode, QGraphicsItem* parent = nullptr);
    ~EdgeItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private slots:
    void updatePos();

private:
    NodeItem* m_startNode;
    NodeItem* m_endNode;
    QPointF m_p1, m_p2, m_p3, m_p4; //起点、拐点1、拐点2、终点
};