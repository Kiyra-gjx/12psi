#include "stdafx.h"
#include "WarehouseDAO.h"
#include "domain/query/WarehouseQuery/WarehouseQuery.h"
#include "WarehouseMapper.h"


std::string WarehouseDAO::queryConditionBuilder(const WarehouseQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->number) {

		sqlCondition << " AND number=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->contacts) {

		sqlCondition << " AND contacts=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->contacts.getValue(""));
	}
	if (query->tel) {

		sqlCondition << " AND tel=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->tel.getValue(""));
	}
	if (query->add) {

		sqlCondition << " AND `add`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->add.getValue(""));
	}
	if (query->data) {

		sqlCondition << " AND data=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t WarehouseDAO::countW(const WarehouseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT count(*) FROM warehouse";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

// 获取仓库列表
std::list<WarehouseDO> WarehouseDAO::selectWarehouseList(const WarehouseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,name,number,frame,data,NULL,NULL,NULL FROM warehouse";
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY `id` DESC";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<WarehouseDO>(sql, WarehouseMapper(), params);
}

// 获取仓库名称列表
std::list<WarehouseDO> WarehouseDAO::selectWarehouseNameList()
{
	string sql = "SELECT id,name,number,NULL,NULL,NULL,NULL,NULL FROM warehouse";
	return sqlSession->executeQuery<WarehouseDO>(sql, WarehouseMapper());
}


//通过ID查询仓库详情数据
PtrWarehouseDO WarehouseDAO::selectWareDetailById(std::string id)
{
	string sql = "SELECT id,name,number,frame,contacts,tel,`add`,data FROM warehouse WHERE `id` = ? ";
	return sqlSession->executeQueryOne<PtrWarehouseDO>(sql, PtrWarehouseMapper(), "%s", id);
}

// 删除指定仓库
int WarehouseDAO::WarehouseDelete_is_warehouse_ById(const std::string id)
{
	string sql = "DELETE FROM `warehouse` WHERE `id` = ?;";
	return sqlSession->executeUpdate(sql, "%s", id);
}
