#ifndef _WAREHOUSE_DAO_
#define _WAREHOUSE_DAO_
#include "BaseDAO.h"
#include "domain/query/WarehouseQuery/WarehouseQuery.h"
#include "domain/do/WarehouseDO.h"

class WarehouseDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    WarehouseDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const WarehouseQuery::Wrapper& query, SqlParams& params);

public:
	
	// 统计数据条数
	uint64_t countW(const WarehouseQuery::Wrapper& query);

	//通过参数查找仓库列表
	std::list<WarehouseDO> selectWarehouseList(const WarehouseQuery::Wrapper& query);

	//获取仓库列表
	std::list<WarehouseDO>selectWarehouseNameList();

	//通过ID查询仓库详情数据
	PtrWarehouseDO selectWareDetailById(std::string id);
	//新增仓库——调用基类BaseDO的Insert

	//// 统计数据条数
	//uint64_t count(const WarehouseQuery::Wrapper& query);
	//// 分页查询数据
	//std::list<WarehouseDO> selectWithPage(const WarehouseQuery::Wrapper& query);
	// 通过ID删除数据
	int WarehouseDelete_is_warehouse_ById(const std::string id);
};


#endif