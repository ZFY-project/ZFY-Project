#include "Wms_stock.h"

bool WmsStockMgr::stockIn(const QString& matCode, const QString& locCode, int num)
{
	if(num<=0)
	{
		return false;
	}
	else if (num > 0)
	{
		QString key = matCode + "|" + locCode;
		m_stock[key].num += num;
		return true;
	}
}

bool WmsStockMgr::stockOut(const QString& matCode, const QString& locCode, int num)
{
	if (num <= 0)
	{
		return false;
	}
	QString key = matCode + "|" + locCode;
	// 不存在 或 数量不够
	if (!m_stock.contains(key) || m_stock[key].num < num)
		return false;

	m_stock[key].num -= num;
	return true;
}

int WmsStockMgr::getStockNum(const QString& matCode, const QString& locCode)
{
	QString key = matCode + "|" + locCode;

	// 2. 如果不存在，返回 0
	if (!m_stock.contains(key)) {
		return 0;
	}
	return m_stock[key].num;
}

QMap<QString,Wms_stock> WmsStockMgr::getAllData()
{
	return m_stock;
}

void WmsStockMgr::setAllData(const QMap<QString, Wms_stock>& data)
{
	m_stock = data;
}
