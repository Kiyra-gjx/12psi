#pragma once
#ifndef _ORDER_SERVICE_
#define _ORDER_SERVICE_


#include "domain/dto/OrderDTO.h"
#include "domain/dto/OrderExamineDTO.h"
#include "domain/vo/OrderVO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/do/OrderDO.h"


class OrderService
{
public:
    /**
     * 修改采购订单主数据
     * @param dto 采购单DTO对象
     * @return 操作是否成功
     */
	// 修改采购单
	bool modifyOrder(const OrderDetailDTO::Wrapper& dto);

	//审核和反审核订单
	StringJsonVO::Wrapper examineDingdan(const OrderExamineDTO::Wrapper& dto);
private:
	// 辅助方法：将DTO转换为多个DO对象
	bool convertDtoToDos(const OrderDetailDTO::Wrapper& dto, PtrBuyDO& BorDO, PtrBuyInfoDO& BorInfoDO, PtrGoodsDO& goodsDO);
};


















#endif 