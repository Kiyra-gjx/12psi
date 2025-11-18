#pragma

#ifndef _WAREHOUSE_SERVICE_
#define _WAREHOUSE_SERVICE_

#include "domain/dto/WarehouseDTO/WarehouseDTO.h"
#include "domain/query/WarehouseQuery/WarehouseQuery.h"
#include "domain/vo/WarehouseVO/WarehouseVO.h"


class WarehouseService 
{
public:
	//分页查询仓库列表
	WareListPageDTO::Wrapper WarehouselistAll(const WarehouseQuery::Wrapper& query);

	//查询仓库名称列表
	oatpp::List<WareNameListDTO::Wrapper> WareNameList();

	// 根据Id查询指定仓库详情信息
	WarehouseDetailDTO::Wrapper getWarehouseDetailById(const string& id);
	// 新增仓库
	string addWarehouse(const WarehouseAddDTO::Wrapper& dto);

	// 修改数据
	bool updateData(const WarehouseDetailDTO::Wrapper& dto);
	// 通过ID删除数据
	bool removeData(const oatpp::List<oatpp::String>& ids);

};

#endif 
