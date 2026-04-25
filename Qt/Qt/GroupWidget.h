#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

// 自定义组合控件：输入框+按钮 打包成一个控件
class GroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupWidget(QWidget* parent = nullptr);

    QString getText();
    QLineEdit* getEdit();
    QPushButton* getBtn();

signals:
    void btnClicked();

private:
    QLineEdit* m_edit;
    QPushButton* m_btn;
};