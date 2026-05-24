#pragma once
#include <QWidget>
#include<QPushButton>
#include<QMouseEvent>
#include<QGraphicsView>
#include"NodeItem.h"

class SegmentWidget :
    public QWidget
{
    Q_OBJECT
public:
    SegmentWidget(QWidget* parent = nullptr);
    ~SegmentWidget();
signals:
    void canvasClicked(QPointF pos);
private:
    QPushButton* btn_addNode;
    QPushButton* btn_connect;
    bool isOpened = false;
    bool isConnectted = false;
    NodeItem* firstNode=nullptr;
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    //void mousePressEvent(QMouseEvent* event)override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
private slots:
    void onAddNode();
    void onStartConnect();
};

