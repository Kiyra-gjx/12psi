#pragma once

#ifndef _PURCHASEORDER_DAO_H_
#define _PURCHASEORDER_DAO_H_
#include "BaseDAO.h"
#include "../domain/do/BuyJsDO.h"
#include "../domain/do/BuyInfoDO.h" 

class PurchaseOrderDAO : public BaseDAO
{
public:
	// 通过ID删除数据 
	int deleteById(string id);

	// (用于检查 'examine=1' 或 'examine=0' 的记录是否存在)
	uint64_t countByIdAndStatus(string id, int status);

	// 根据主表ID (pid) 删除所有buy_info副表明细 
	int deleteInfoByPid(string pid);

	// 新增采购单主表 (buy)
	std::string addPurchaseOrder(const BuyJsDO& data);

	// 新增采购单明细表 (buy_info)
	bool addInfo(const BuyInfoDO& data);

};
#endif // !_PURCHASEORDER_DAO_H_