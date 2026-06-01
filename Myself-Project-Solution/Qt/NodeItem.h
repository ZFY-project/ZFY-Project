#pragma once
#include <QGraphicsItem>
class NodeItem :
    public QGraphicsObject  
{
    Q_OBJECT
public:
    explicit NodeItem(QGraphicsItem* parent = nullptr);
    QRectF boundingRect()const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;

    QPointF getLeftPin() const;  //左出线点
    QPointF getRightPin() const; //右出线点

signals:
    void positionChanged();// 节点位置变化时发出的信号，用来更新连线
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value)override;
};



