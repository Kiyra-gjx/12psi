#pragma once
#ifndef _PURCHASEORDERJS_SERVICE_H_
#define _PURCHASEORDERJS_SERVICE_H_
#include <list>
#include "../domain/dto/PurchaseOrderJsDTO.h"
#include <oatpp/core/Types.hpp>

/**
 * 新增删除采购单服务声明
 */
class PurchaseOrderService
{
public:
	// 通过ID删除数据
	string removePurchaseOrder(string id);

	
	string addPurchaseOrder(const OrderAddDTO::Wrapper dto);
};

#endif // !_PURCHASEORDERJS_SERVICE_H_