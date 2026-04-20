#include "GroupWidget.h"

GroupWidget::GroupWidget(QWidget* parent)
    : QWidget(parent)
{
    // 1. 创建内部子控件
    m_edit = new QLineEdit(this);
    m_btn = new QPushButton("确认", this);

    // 2. 设置布局（组合控件核心，自动排版）
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_edit);
    layout->addWidget(m_btn);
    layout->setSpacing(8);
    layout->setContentsMargins(10, 10, 10, 10);

    // 3. 内部信号转发：子控件信号 → 组合控件对外信号
    connect(m_btn, &QPushButton::clicked, this, &GroupWidget::btnClicked);
}

QString GroupWidget::getText()
{
    return m_edit->text();
}