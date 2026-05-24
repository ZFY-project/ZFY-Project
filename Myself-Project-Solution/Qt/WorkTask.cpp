#include "WorkTask.h"
#include<QDebug>
#include<QThread>

WorkTask::WorkTask(QObject* parent)
{
}
void WorkTask::doLongTask()
{
    qDebug() << "thread ID:" << QThread::currentThreadId;
    for (int i = 0; i <= 100; i += 1)
    {
        QThread::msleep(200); // 模拟耗时计算/文件/网络
        emit sigProgress(i);  // 发信号给UI
    }

    emit sigFinish("task has finished");
}