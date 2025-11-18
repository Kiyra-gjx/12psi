#ifndef _WAREHOUSECONTROLLER_H_
#define _WAREHOUSECONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/WarehouseQuery/WarehouseQuery.h"
#include "domain/dto/WarehouseDTO/WarehouseDTO.h"
#include "domain/vo/WarehouseVO/WarehouseVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("ware.tag")

class WarehouseController : public oatpp::web::server::api::ApiController
{

	API_ACCESS_DECLARE(WarehouseController);

public:
	// 3.1 获取仓库列表（条件+分页）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("ware.get.summary"), 
		queryWarehouse,
		WarehouseQuery, 
		WareListPageJsonVO::Wrapper, 
		API_TAG
	);
	// 3.1获取仓库列表（条件+分页）
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET, 
		"/ware/query", 
		queryWarehouse, 
		WarehouseQuery,
		executequeryWare(query)
	);

	// 3.2 获取仓库名称列表
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ware.get.name.summary"),
		queryWarename,
		WareNameListJsonVO::Wrapper, 
		API_TAG
	);
	// 3.2 获取仓库名称列表
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(
		API_M_GET, 
		"/ware/getname", 
		queryWarename, 
		executeWarename()
	);


	// 获取指定仓库详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ware.query-detail.summary"),
		queryWarehouseDetail,
		WarehouseDetailJsonVO::Wrapper, 
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("ware.field.id"), "1001", true);
	);
	// 获取指定仓库详情
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/ware/detail",
		queryWarehouseDetail,
		QUERY(String, id),
		executeQueryDetail(id) 
	);
	
	//添加仓库
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ware.add.summary"),
		addWare,
		StringJsonVO::Wrapper,
		API_TAG
	);
	//添加仓库
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/ware/add",
		addWare,
		BODY_DTO(WarehouseAddDTO::Wrapper, dto),
		executeAdd(dto)
	);

	// WarehouseController.h 中修改 update 接口的声明
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ware.update.summary"),
		update, 
		//WarehouseDetailJsonVO::Wrapper, // 改为与实现一致的类型
		StringJsonVO::Wrapper,//改为只返回id
		API_TAG
	);
	// 修改仓库
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT, 
		"/ware/update", 
		update, 
		BODY_DTO(WarehouseDetailDTO::Wrapper, dto),  
		execUpdate(dto, authObject->getPayload())
	);

	//删除仓库
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("ware.remove.summary"), remove, ListJsonVO<String>::Wrapper, API_TAG
	);
	//删除仓库
	API_HANDLER_ENDPOINT_AUTH(
		API_M_DEL, "/ware/remove", remove, BODY_DTO(List<String>, ids), execRemove(ids)
	);

private: 
	//获取仓库列表（条件+分页
	WareListPageJsonVO::Wrapper executequeryWare(const WarehouseQuery::Wrapper& query);
	//获取仓库名称列表
	WareNameListJsonVO::Wrapper executeWarename();
	//获取指定仓库详情
	WarehouseDetailJsonVO::Wrapper executeQueryDetail(const String& id);
	//添加仓库
	StringJsonVO::Wrapper executeAdd(const WarehouseAddDTO::Wrapper& dto);
	//修改仓库
	StringJsonVO::Wrapper execUpdate(const WarehouseDetailDTO::Wrapper& dto, const PayloadDTO& payload);
	//删除仓库
	ListJsonVO<String>::Wrapper execRemove(const List<String>& ids);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif