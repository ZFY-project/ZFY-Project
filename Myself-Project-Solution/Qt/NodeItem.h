#pragma once
#include <qgraphicsitem.h>
class NodeItem :
    public QGraphicsObject  
{
    Q_OBJECT
public:
    explicit NodeItem(QGraphicsItem* parent = nullptr);
    QRectF boundingRect()const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;

signals:
    void positionChanged();// 节点位置变化时发出的信号，用来更新连线
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value)override;
};

