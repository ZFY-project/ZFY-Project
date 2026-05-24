#include "WmsWidget.h"
#include "Wms_file.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

WmsWidget::WmsWidget(QWidget* parent) : QWidget(parent)
{
    // 一启动就加载文件
    WmsFile::loadStock(mgr, "stock.data");

    // 界面
    matEdit = new QLineEdit(this);
    locEdit = new QLineEdit(this);
    numEdit = new QLineEdit(this);
    matEdit->setPlaceholderText("物料");
    locEdit->setPlaceholderText("库位");
    numEdit->setPlaceholderText("数量");

    QPushButton* inBtn = new QPushButton("入库", this);
    QPushButton* outBtn = new QPushButton("出库", this);

    QHBoxLayout* hlay = new QHBoxLayout;
    hlay->addWidget(matEdit);
    hlay->addWidget(locEdit);
    hlay->addWidget(numEdit);
    hlay->addWidget(inBtn);
    hlay->addWidget(outBtn);

    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({ "物料","库位","数量" });

    QVBoxLayout* vlay = new QVBoxLayout(this);
    vlay->addLayout(hlay);
    vlay->addWidget(table);
    setLayout(vlay);

    connect(inBtn, &QPushButton::clicked, this, &WmsWidget::inBtnClick);
    connect(outBtn, &QPushButton::clicked, this, &WmsWidget::outBtnClick);

    refreshTable();
}

WmsWidget::~WmsWidget()
{
    // 关闭时自动保存
    WmsFile::saveStock(mgr, "stock.data");
}

void WmsWidget::inBtnClick()
{
    mgr.stockIn(matEdit->text(), locEdit->text(), numEdit->text().toInt());
    refreshTable();
}

void WmsWidget::outBtnClick()
{
    bool ok = mgr.stockOut(matEdit->text(), locEdit->text(), numEdit->text().toInt());
    if (!ok) QMessageBox::warning(this, "", "失败");
    refreshTable();
}

void WmsWidget::refreshTable()
{
    auto map = mgr.getAllData();
    table->setRowCount(0);
    for (auto it = map.begin(); it != map.end(); ++it) {
        int r = table->rowCount();
        table->insertRow(r);
        table->setItem(r, 0, new QTableWidgetItem(it.value().matCode));
        table->setItem(r, 1, new QTableWidgetItem(it.value().locCode));
        table->setItem(r, 2, new QTableWidgetItem(QString::number(it.value().num)));
    }
}