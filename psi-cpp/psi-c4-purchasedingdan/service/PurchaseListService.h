#pragma once
#ifndef _PURCHASELIST_SERVICE_
#define _PURCHASELIST_SERVICE_
#include "domain/query/PurchaseListQuery.h"
#include "domain/vo/PurchaseListVO.h"

//采购订单详情服务实现
class PurchaseListService
{
public:
	//查询指定的数据
	PurchaseListPageDTO::Wrapper listAll(const PurchaseListQuery::Wrapper& query);
};

#endif
