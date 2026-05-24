#include "Wms_file.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

bool WmsFile::saveStock(WmsStockMgr& stockMgr, const QString& filePath)
{
	auto stockMap = stockMgr.getAllData();
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "保存文件失败：" << file.errorString();
        return false;
    }
    QDataStream out(&file);
    out << stockMap;  // 写入整个库存

    file.close();
    return true;
}
// 加载库存
bool WmsFile::loadStock(WmsStockMgr& stockMgr, const QString& filePath)
{
    QMap<QString, Wms_stock> stockMap;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "加载文件失败：" << file.errorString();
        return false;
    }

    QDataStream in(&file);
    in >> stockMap;  // 读取整个库存

    file.close();

    // 把读取到的数据 重新设置给库存管理类
    // 这里我们需要在 WmsStockMgr 里加一个 setAllData 函数
    // stockMgr.setAllData(stockMap);

    return true;
}
