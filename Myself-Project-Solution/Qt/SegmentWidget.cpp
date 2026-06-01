#include "SegmentWidget.h"
#include "EdgeItem.h"
#include "NodeItem.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QVBoxLayout>
SegmentWidget::SegmentWidget(QWidget* parent):QWidget(parent)
{
	btn_addNode = new QPushButton("addNode", this);
	connect(btn_addNode, &QPushButton::clicked, this, &SegmentWidget::onAddNode);
	btn_connect = new QPushButton("connectNodes", this);
	connect(btn_connect, &QPushButton::clicked, this, &SegmentWidget::onStartConnect);

	m_scene = new QGraphicsScene(this);
	m_view = new QGraphicsView(m_scene);
	m_view->resize(640, 480);
	m_view->setRenderHint(QPainter::Antialiasing);//抗锯齿
	m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(btn_addNode);
	layout->addWidget(btn_connect);
	layout->addWidget(m_view);
	m_view->viewport()->installEventFilter(this);

	/*
		//创建两个节点
	NodeItem* node1 = new NodeItem;
	NodeItem* node2 = new NodeItem;
	//设置节点位置
	node1->setPos(0, 0);
	node2->setPos(50, 60);
	//创建连线
	EdgeItem* edge = new EdgeItem(node1, node2);
	//添加到场景
	scene->addItem(node1);
	scene->addItem(node2);
	scene->addItem(edge);
	QGraphicsView* view = new QGraphicsView(scene);

	// 用布局把 view 放到窗口里
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(view);*/

}

SegmentWidget::~SegmentWidget()
{
}
bool SegmentWidget::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_view->viewport() && event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse = static_cast<QMouseEvent*>(event);

		if (mouse->button() == Qt::LeftButton )
		{
			if (isOpened)
			{
				// 点哪里，创建节点在哪里
				QPointF clickPos = m_view->mapToScene(mouse->pos());

				NodeItem* node = new NodeItem;
				node->setPos(clickPos);
				m_scene->addItem(node);

				// 创建完关闭
				isOpened = false;
				m_view->setCursor(Qt::ArrowCursor);
				return true;
			}
			else if (isConnectted)
			{
				// 获取点击位置的 item
				QPointF scenePos = m_view->mapToScene(mouse->pos());
				QGraphicsItem* item = m_scene->itemAt(scenePos, QTransform());

				// 判断是不是节点
				NodeItem* clickedNode = dynamic_cast<NodeItem*>(item);
				if (!clickedNode) 
					return true;

				// 第一次点击：记录第一个节点
				if (!firstNode)
				{
					firstNode = clickedNode;
				}
				// 第二次点击：连线
				else
				{
					// 创建连线
					EdgeItem* edge = new EdgeItem(firstNode, clickedNode);
					
					m_scene->addItem(edge);
					//m_scene->update();

					// 重置
					firstNode = nullptr;
					isConnectted= false;
					m_view->setCursor(Qt::ArrowCursor);
				}
				return true;
			}
		}
	}

	return QWidget::eventFilter(obj, event);
}
void SegmentWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		isOpened = false;
		isConnectted = false;
		firstNode = nullptr;
		m_view->setCursor(Qt::ArrowCursor);
		return;
	}
	else if (event->key() == Qt::Key_Delete)
	{
		QList<QGraphicsItem*> delList = m_scene->selectedItems();
		for (auto item : delList)
		{
			m_scene->removeItem(item);
			delete item;
		}
		return;
	}
	return QWidget::keyPressEvent(event);
}
void SegmentWidget::onStartConnect()
{
	isConnectted = true;
	m_view->setCursor(Qt::PointingHandCursor);
}
void SegmentWidget::onAddNode()
{
	isOpened = true;
	m_view->setCursor(Qt::CrossCursor);

}
