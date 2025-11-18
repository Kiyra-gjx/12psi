#include "stdafx.h"
#include "WarehouseController.h"
#include "service/WarehouseService/WarehouseService.h"
#include "../ApiDeclarativeServicesHelper.h"


//获取分页查询仓库列表
WareListPageJsonVO::Wrapper WarehouseController::executequeryWare(const WarehouseQuery::Wrapper& query)
{
	WarehouseService service;
	auto dto = service.WarehouselistAll(query);
	auto jvo = WareListPageJsonVO::createShared();
	jvo->success(dto);
	return jvo;
}

//获取仓库名称列表
WareNameListJsonVO::Wrapper WarehouseController::executeWarename()
{
	WarehouseService service;
	auto dto = service.WareNameList();
	auto jvo = WareNameListJsonVO::createShared();
	jvo->success(dto);
	return jvo;
}

// 获取仓库详情
WarehouseDetailJsonVO::Wrapper WarehouseController::executeQueryDetail(const String& id)
{
	//定义返回到前端的JsonVO对象
	auto wareDetailJvo = WarehouseDetailJsonVO::createShared();

	//检验参数id是否为空
	if (!id) {
		wareDetailJvo->init(nullptr, RS_PARAMS_INVALID);
		return wareDetailJvo;
	}

	//定义Service对象，调用服务
	WarehouseService wareSer;
	//定义dto接收返回结果
	auto wareDto = wareSer.getWarehouseDetailById(id.getValue({}));
	
	// 将vo状态变为成功，进行返回
	wareDetailJvo->success(wareDto);
	return wareDetailJvo;
}

// 添加仓库
StringJsonVO::Wrapper WarehouseController::executeAdd(const WarehouseAddDTO::Wrapper& dto)
{
	// 定义返回到前端的JsonVo对象
	auto wareAddJvo = StringJsonVO::createShared();

	// 检验参数
	// 非空检验
	if (!dto->name || !dto->number || !dto->frame)
	{
		//有效值检验(无)
		wareAddJvo->init(nullptr, RS_PARAMS_INVALID);
		return wareAddJvo;
	}

	// 定义Service对象，调用服务
	WarehouseService wareSer;
	//将前端传入的组装好的dto传入，定义string接收返回的id
	string id = wareSer.addWarehouse(dto);
	
	//判断id是否为空将vo进行成功、失败设置
	if (id != "")
	{
		wareAddJvo->success(id);
	}
	else
	{
		wareAddJvo->fail("");
	}

	return wareAddJvo;
}

// 修改仓库
// WarehouseController.cpp 中修改 execUpdate 函数
StringJsonVO::Wrapper WarehouseController::execUpdate(const WarehouseDetailDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 1. 创建与声明一致的返回对象（WarehouseDetailJsonVO）
	auto jvo = StringJsonVO::createShared();

	// 2. 参数校验（注意：oatpp String 是 ObjectWrapper，需用 get() 判断是否为空）
	if (!dto->id || dto->id->empty()) { // 确保 id 不为空且非空字符串
		jvo->init(nullptr, RS_PARAMS_INVALID); // 错误状态：参数无效
		return jvo;
	}

	// 3. 调用服务层更新
	WarehouseService service;
	dto->setPayload(&payload);
	if (service.updateData(dto)) {
		// 成功时返回更新后的完整 DTO（符合 WarehouseDetailJsonVO 对 WarehouseDetailDTO 的包装）
		// 改：成功时只返回id
		jvo->success(dto->id);
	}
	else {
		// 失败时返回空数据+错误状态
		jvo->fail(nullptr);
	}

	return jvo; // 此时返回类型与声明一致
}

ListJsonVO<String>::Wrapper WarehouseController::execRemove(const List<String>& ids)
{

	auto jvo = ListJsonVO<String>::createShared();


	if (ids->empty()) {

		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}


	WarehouseService service;
	if (service.removeData(ids)) {
		jvo->success(ids);
	}
	else {
		jvo->fail(nullptr);
	}

	return jvo;
}
