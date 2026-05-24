#pragma once
#include <QObject>
#include <QGraphicsLineItem>
#include "NodeItem.h"

class EdgeItem : public QObject,public QGraphicsLineItem
{
    Q_OBJECT
public:
    EdgeItem(NodeItem* startNode, NodeItem* endNode, QGraphicsItem* parent = nullptr);
    ~EdgeItem();

private slots:
    void updateLine();

private:
    NodeItem* m_startNode;
    NodeItem* m_endNode;
};