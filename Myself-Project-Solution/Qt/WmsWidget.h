#pragma once
#include <QWidget>
#include "Wms_stock.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class WmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WmsWidget(QWidget* parent = nullptr);
    ~WmsWidget();

private slots:
    void inBtnClick();
    void outBtnClick();
    void refreshTable();

private:
    WmsStockMgr mgr;
    QLineEdit* matEdit;
    QLineEdit* locEdit;
    QLineEdit* numEdit;
    QTableWidget* table;
};