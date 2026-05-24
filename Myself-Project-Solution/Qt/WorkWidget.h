#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
class WorkWidget :
    public QWidget
{
    Q_OBJECT
public:
    WorkWidget(QWidget* parent = nullptr);
    ~WorkWidget();
private:
    QPushButton* btn;
    QLabel* progressLabel;
private slots:

    void onStartClicked();
    void updateProgress(int val);


};

