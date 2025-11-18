#pragma once
#ifndef _BUYDAO_H_
#define _BUYDAO_H_

#include "BaseDAO.h"
#include "../../domain/do/OrderDO.h"
#include "./BuyMapper.h"
#include "domain/dto/OrderDTO.h"


/**
 * 采购订单数据库访问对象 - 专注于buy表操作
 */
class BuyDAO : public BaseDAO
{
public:
	
	// 批量审核状态更新
	bool batchUpdateExamineStatus(const oatpp::List<oatpp::String>& ids, int examineStatus);

	// 更新订单主表信息
	bool updateBuy(const PtrBuyDO& borDO);
};




#endif