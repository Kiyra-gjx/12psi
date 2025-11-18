#include "stdafx.h"
#include "OrderController.h"
#include "service/OrderService.h"

StringJsonVO::Wrapper OrderController::executeModifyDingdan(const OrderDetailDTO::Wrapper& dto)
{
	// 定义返回对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 调用服务层修改订单
	OrderService service;
	// 执行修改
	if (service.modifyOrder(dto)) {
		jvo->success(dto->id);
	}
	else
	{
		jvo->fail(dto->id);
	}

	return jvo;
}

StringJsonVO::Wrapper OrderController::execExamine(const OrderExamineDTO::Wrapper& dto)
{
	// 定义返回对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	if (!dto->ids || dto->ids->size() == 0) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}



	// 调用Service执行审核
	OrderService service;
	return service.examineDingdan(dto);
}
