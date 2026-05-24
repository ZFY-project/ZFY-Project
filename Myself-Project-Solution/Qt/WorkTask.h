#pragma once
#include <qobject.h>
class WorkTask :
    public QObject
{
    Q_OBJECT
public:
    explicit WorkTask(QObject* parent = nullptr);
public slots:
    void doLongTask();
signals:
    void sigProgress(int value);
    void sigFinish(QString msg);

};

