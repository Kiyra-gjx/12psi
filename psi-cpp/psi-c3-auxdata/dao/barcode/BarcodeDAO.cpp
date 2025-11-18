#include "BarcodeDAO.h"

inline std::string BarcodeDAO::queryConditionBuilder(const BarcodeClassPageQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (!query->type.getValue(0)) {
		sqlCondition << " AND type=?";
		SQLPARAMS_PUSH(params, "i", v_int64, query->type.getValue(0));
	}
	if (!query->name.getValue("").empty()) {

		sqlCondition << " AND name=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (!query->content.getValue("").empty()) {
		sqlCondition << " AND content=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->content.getValue(""));
	}
	if (!query->notes.getValue("").empty()) {

		sqlCondition << " AND notes=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->notes.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t BarcodeDAO::count(const BarcodeClassPageQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM barcode ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<BarcodeDO> BarcodeDAO::selectWithClassAndPage(const BarcodeClassPageQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,type,name,content,notes FROM barcode ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<BarcodeDO>(sql, BarcodeMapper(), params);
}

PtrBarcodeDO BarcodeDAO::selectById(const string& id)
{
	string sql = "SELECT id,type,name,content,notes FROM barcode WHERE id=?";
	return sqlSession->executeQueryOne<PtrBarcodeDO>(sql, PtrBarcodeMapper(), "%s", id);
}
