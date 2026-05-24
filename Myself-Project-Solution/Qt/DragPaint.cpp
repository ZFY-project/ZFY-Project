#include "DragPaint.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<QVBoxLayout>

DragPaint::DragPaint(QWidget* parent):QWidget(parent)
{
    //创建场景
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);//场景大小
    //创建视图把场景装进去
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setDragMode(QGraphicsView::RubberBandDrag);//拖动方式
    view->setRenderHint(QPainter::Antialiasing);//抗锯齿
    //给主窗口设置布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    //添加一个可拖动的矩形
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(0, 0, 100, 50);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    rectItem->setFlag(QGraphicsItem::ItemIsSelectable);
    rectItem->setPos(200, 200); // 初始位置
    scene->addItem(rectItem);
}

DragPaint::~DragPaint()
{
}
