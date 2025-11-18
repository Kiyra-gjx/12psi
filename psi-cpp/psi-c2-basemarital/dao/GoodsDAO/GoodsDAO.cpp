#include "GoodsDAO.h"
#include "GoodsMapper.h"

// 统计数据条数
uint64_t GoodsDAO::count(const GoodsQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM goods ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}
// 分页查询数据
std::list<GoodsDO> GoodsDAO::selectWithPage(const GoodsQuery::Wrapper& query) {
	SqlParams params;
	string sql = "SELECT id,name,number,spec,category,brand,unit,code,type,data FROM goods ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	//sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	
	return sqlSession->executeQuery<GoodsDO>(sql, GoodsMapper(), params);

}
//查询详细信息
PtrGoodsDO GoodsDAO::selectById(std::string id) {
	string sql = "SELECT * FROM goods WHERE `id`=?";
	return sqlSession->executeQueryOne<PtrGoodsDO>(sql, PtrGoodsMapper(), "%s", id);
}


inline std::string GoodsDAO::queryConditionBuilder(const GoodsQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND name=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->number) {

		sqlCondition << " AND number=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
	}
	if (query->specification_model) {

		sqlCondition << " AND model=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->specification_model.getValue(""));
	}
	if (query->category) {

		sqlCondition << " AND category=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->category.getValue(""));
	}	
	if (query->brand) {

		sqlCondition << " AND brand=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->brand.getValue(""));
	}
	if (query->goods_unit) {

		sqlCondition << " AND goods_unit=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->goods_unit.getValue(""));
	}	
	if (query->code) {

		sqlCondition << " AND term=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->code.getValue(""));
	}
	if (query->type) {

		sqlCondition << " AND type=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->type.getValue(""));
	}
	if (query->memo) {

		sqlCondition << " AND memo=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->memo.getValue(""));
	}

	return sqlCondition.str();
}

