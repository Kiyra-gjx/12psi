#include "stdafx.h"
#include "DingdanController.h"
#include "../service/DingdanService.h"
//
StringJsonVO::Wrapper DingdanController::executeModifyDingdan(const DingdanDetailDTO::Wrapper& dto, const PayloadDTO& payload)
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
	DingdanService service;
	// 执行修改
	dto->setPayload(&payload);
	if (service.modifyDingdanMultiTable(dto)) {
		jvo->success(dto->id);
	}
	else
	{
		jvo->fail(dto->id);
	}

	return jvo;
}

StringJsonVO::Wrapper DingdanController::execExamine(const DingdanExamineDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	if (!dto->ids || dto->ids->size() == 0) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 设置payload信息到DTO
	dto->setPayload(&payload);

	// 调用Service执行审核
	DingdanService service;
	return service.examineDingdan(dto);
}
