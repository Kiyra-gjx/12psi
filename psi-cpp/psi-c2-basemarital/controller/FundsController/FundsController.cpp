#include "stdafx.h"
#include "FundsController.h"

AccountDetailJsonVO::Wrapper FundsController::excuteQueryDetail(const String& id)
{
	// 定义返回数据对象
	auto jvo = AccountDetailJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 定义一个Service
	FundsService service;
	// 执行数据新增
	auto res = service.getAccountById(id.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
}
StringJsonVO::Wrapper FundsController::excuteAdd(const AddAccountDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();
//非空校验

	if (!dto->accountname|| !dto->accountnumber|| !dto->frame|| !dto->time|| !dto->initial || !dto->balance)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	
//有效值校验
	if (!dto->accountname->empty() || !dto->accountnumber->empty() || !dto->frame->empty() || !dto->time->empty() || dto->initial < 0 || dto->balance < 0)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	FundsService service;
	dto->setPayload(&payload);
	std::string id = service.saveNewAccount(dto);
	if (id != "") {
		jvo->success(id);
	}
	else
	{
		jvo->fail("");
	}
	//响应结果
	return jvo;
}
StringJsonVO::Wrapper FundsController::excuteModify(const AccountDetailDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 定义一个Service
	FundsService service;
	// 执行数据修改
	dto->setPayload(&payload);
	if (service.updateAccount(dto)) {
		jvo->success(dto->id);
	}
	else
	{
		jvo->fail(dto->id);
	}
	// 响应结果
	return jvo;
}

FundsPageJsonVO::Wrapper FundsController::execQueryFunds(const FundsQuery::Wrapper& query)
{
	return FundsPageJsonVO::Wrapper();
}

ListJsonVO<String>::Wrapper FundsController::execRemoveFund(const List<String>& ids)
{
	auto json = ListJsonVO<String>::createShared();
	if (!ids)
	{
		json->init(nullptr, RS_PARAMS_INVALID);
		return json;
	}
	FundsService service;
	auto res = service.deleteFunds(ids);
	if (res)
	{
		json->success(ids);
	}
	else
	{
		json->fail(nullptr);
	}
	return json;
}