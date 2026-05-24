#include "WorkWidget.h"
#include "WorkTask.h"
#include <QThread>
#include <QVBoxLayout>
#include <QDebug>
#include "WorkWidget.h"

WorkWidget::WorkWidget(QWidget* parent)
	:QWidget(parent)
{
    this->setFixedSize(400, 200);
    QVBoxLayout* lay = new QVBoxLayout(this);

    btn = new QPushButton("begin");
    progressLabel = new QLabel("progress：0%");

    lay->addWidget(btn);
    lay->addWidget(progressLabel);

    connect(btn, &QPushButton::clicked,
        this, &WorkWidget::onStartClicked);

    qDebug() << "main thread ID：" << QThread::currentThreadId();
}
WorkWidget::~WorkWidget()
{
}
void WorkWidget::onStartClicked()
{
    // 1. 创建工作对象、线程对象
    WorkTask* worker = new WorkTask;
    QThread* thread = new QThread;

    // 2. 核心：把工作对象 移动到 子线程
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &WorkTask::doLongTask);
    // 工作进度/完成 -> 更新UI
    connect(worker, &WorkTask::sigProgress, this, &WorkWidget::updateProgress);
    connect(worker, &WorkTask::sigFinish, this, [=](QString msg) 
    {
            progressLabel->setText(msg);
    });
    // 任务结束 -> 退出线程、释放资源（防内存泄漏）
    connect(worker, &WorkTask::sigFinish, thread, &QThread::quit);
    connect(worker, &WorkTask::sigFinish, worker, &WorkTask::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    // 4. 启动子线程
    thread->start();
}
void WorkWidget::updateProgress(int val)
{
    progressLabel->setText(QString("progress：%1%").arg(val));
}
