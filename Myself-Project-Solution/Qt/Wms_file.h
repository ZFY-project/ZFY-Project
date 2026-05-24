#pragma once
#include <QString>
#include <QMap>
#include "Wms_stock.h"

class WmsFile
{
public:
    WmsFile();

    // 保存库存到文件
    static bool saveStock(WmsStockMgr& stockMgr, const QString& filePath);

    // 从文件加载库存
    static bool loadStock(WmsStockMgr& stockMgr, const QString& filePath);
};
