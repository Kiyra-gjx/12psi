#include "stdafx.h"
#include "InoutCategoryDAO.h"
#include "InoutCategoryMapper.h"

//普通查询条件构建函数
std::string InoutCategoryDAO::queryConditionBuilder(const InoutCategoryQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->type) {
		sqlCondition << " AND type=?";
		SQLPARAMS_PUSH(params, "i", int32_t, *(query->type));
	}
	return sqlCondition.str();
}

//分页查询条件构建函数
std::string InoutCategoryDAO::queryPageConditionBuilder(const InoutCategoryPageQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->type) {
		sqlCondition << " AND type=?";
		SQLPARAMS_PUSH(params, "i", int32_t, *(query->type));
	}
	if (query->name) {
		sqlCondition << " AND name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", string, *(query->name));
	}

	return sqlCondition.str();
}

//获取收支类别名称列表（条件）
list<InoutCategoryDO> InoutCategoryDAO::selectNames(const InoutCategoryQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,name FROM iet";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序
	sql += " ORDER BY sort ASC";
	//执行查询
	return sqlSession->executeQuery<InoutCategoryDO>(sql, InoutCategorySimpleMapper(), params);
}

//统计总条数
uint64_t InoutCategoryDAO::count(const InoutCategoryPageQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM iet";
	//构建查询条件
	sql += queryPageConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

//获取收支类别列表（条件+分页）
list<InoutCategoryDO> InoutCategoryDAO::selectPage(const InoutCategoryPageQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,name,type,sort FROM iet";
	//构建查询条件
	sql += queryPageConditionBuilder(query, params);
	//构建排序
	sql += " ORDER BY sort ASC";
	//构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	//执行查询
	return sqlSession->executeQuery<InoutCategoryDO>(sql, InoutCategoryMapper(), params);
}

//获取指定类别详情
PtrInoutCategoryDO InoutCategoryDAO::selectById(const string& id)
{
	string sql = "SELECT id,name,type,sort,data FROM iet WHERE id=?";
	return sqlSession->executeQueryOne<PtrInoutCategoryDO>(sql, PtrInoutCategoryMapper(),"%s",id);
}