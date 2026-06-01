#pragma once
#include<QString>
#include<vector>
#include<QMap>
#include <QDataStream>
struct Wms_stock
{
	QString matCode;//绑定物料编码
	QString locCode;//绑定库位编码
	int num;//库存数量
};

// 关键：声明流运算符，让Qt知道如何读写这个结构体
QDataStream& operator<<(QDataStream& out, const Wms_stock& stock);
QDataStream& operator>>(QDataStream& in, Wms_stock& stock);

class WmsStockMgr
{
public:
	WmsStockMgr();
	~WmsStockMgr();

    //入库
    bool stockIn(const QString& matCode, const QString& locCode, int num);
    //出库
    bool stockOut(const QString& matCode, const QString& locCode, int num);
    //查库存
    int getStockNum(const QString& matCode, const QString& locCode);
    //获取全部数据
    QMap<QString,Wms_stock>getAllData();
    void setAllData(const QMap<QString, Wms_stock>& data);
private:
    QMap<QString, Wms_stock>m_stock;

};
