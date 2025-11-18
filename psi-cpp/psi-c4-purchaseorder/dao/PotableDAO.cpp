#include "stdafx.h"
#include"PotableDAO.h"
#include"PotableMapper.h"

std::string PotableDAO::queryConditionBuilder(const PotableQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", string, query->name.getValue(""));
	}
	if (query->supplier) {

		sqlCondition << " AND `supplier`=?";
		SQLPARAMS_PUSH(params, "s", string, query->supplier.getValue(""));
	}
	if (query->number) {

		sqlCondition << " AND number=?";
		SQLPARAMS_PUSH(params, "s", string, query->number.getValue(""));
	}
	if (query->user) {

		sqlCondition << " AND user=?";
		SQLPARAMS_PUSH(params, "s", string, query->user.getValue(""));
	}
	if (query->s_time) {

		sqlCondition << " AND time>=?";
		SQLPARAMS_PUSH(params, "s", string, query->s_time.getValue(""));
	}
	if (query->e_time) {

		sqlCondition << " AND time<=?";
		SQLPARAMS_PUSH(params, "s", string, query->e_time.getValue(""));
	}
	if (query->people) {

		sqlCondition << " AND people=?";
		SQLPARAMS_PUSH(params, "s", string, query->people.getValue(""));
	}
	if (query->examine) {

		sqlCondition << " AND examine=?";
		SQLPARAMS_PUSH(params, "i", int, query->examine.getValue(0));

	}
	if (query->nucleus) {

		sqlCondition << " AND nucleus=?";
		SQLPARAMS_PUSH(params, "i", int, query->nucleus.getValue(0));
	}

	if (query->cse) {
		sqlCondition << " AND cse=?";
		SQLPARAMS_PUSH(params, "i", int, query->cse.getValue(0));
	}
	
	if (query->invoice) {
		sqlCondition << " AND invoice=?";
		SQLPARAMS_PUSH(params, "i", int, query->invoice.getValue(0));
	}

	if (query->check) {
		sqlCondition << " AND \'check\'=?";
		SQLPARAMS_PUSH(params, "i", int, query->check.getValue(0));
	}

	if (query->data) {
		sqlCondition << " AND \'data\'=?";
		SQLPARAMS_PUSH(params, "s", string, query->data.getValue(""));
	}
	return sqlCondition.str();
}


std::list<PotableDO> PotableDAO::selectWithPage(const PotableQuery::Wrapper& query)
{
	//sqlParams是用来存放执行sal语句之后保存的信息
	SqlParams params;
	string sql = "WITH g AS(SELECT goods.name,buy_info.pid FROM goods JOIN buy_info ON goods.id=buy_info.goods)\
	SELECT * FROM buy JOIN g ON g.pid=buy.id";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<PotableDO>(sql, PotableMapper(), params);
}

uint64_t PotableDAO::count(const PotableQuery::Wrapper& query) {
	SqlParams params;
	string sql = "WITH g AS(SELECT goods.name,buy_info.pid FROM goods JOIN buy_info ON goods.id=buy_info.goods)\
	SELECT * FROM buy JOIN g ON g.pid=buy.id";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}