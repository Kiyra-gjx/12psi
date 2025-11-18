#include "stdafx.h"
#include "SupplierDAO.h"
#include "SupplierMapper.h"

std::string SupplierDAO::queryConditionBuilder(const SupplierQuery::Wrapper& query, SqlParams& params)
{
	std::stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";

	if (query->id)
	{
		sqlCondition << " AND `id` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
	}

	if (query->name)
	{
		sqlCondition << " AND `name` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	if (query->category)
	{
		sqlCondition << " AND `category` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->category.getValue(""));
	}

	

	if (query->contacts)
	{
		sqlCondition << " AND `contacts` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->contacts.getValue(""));
	}

	return sqlCondition.str();
}

// 查询总条数
uint64_t SupplierDAO::count(const SupplierQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM supplier ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询
std::list<SupplierDO> SupplierDAO::selectWithPage(const SupplierQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT id,name,contacts,phone,address,email FROM supplier ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<SupplierDO>(sql, SupplierMapper(), params);
}

// 按名称查询单个供应商
PtrSupplierDO SupplierDAO::selectByName(const std::string& name)
{
	std::string sql = "SELECT id,name,contacts,phone,address,email FROM supplier WHERE `name`=? LIMIT 1";
	return sqlSession->executeQueryOne<PtrSupplierDO>(sql, PtrSupplierMapper(), "%s", name);
}

// 按ID查询供应商
PtrSupplierDO SupplierDAO::selectById(const std::string& id)
{
	std::string sql = "SELECT id,name,contacts,phone,address,email FROM supplier WHERE `id`=? LIMIT 1";
	return sqlSession->executeQueryOne<PtrSupplierDO>(sql, PtrSupplierMapper(), "%s", id);
}
