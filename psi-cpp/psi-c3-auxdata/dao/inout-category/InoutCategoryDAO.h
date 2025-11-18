#ifndef INOUTCATEGORYDAO_H_
#define INOUTCATEGORYDAO_H_
#include "BaseDAO.h"
#include "../../domain/do/inout-category/InoutCategoryDO.h"
#include "../../domain/query/inout-category/InoutCategoryQuery.h"

class InoutCategoryDAO : public BaseDAO
{
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    InoutCategoryDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const InoutCategoryQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据InoutCategoryQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const InoutCategoryQuery::Wrapper& query, SqlParams& params);
	inline std::string queryPageConditionBuilder(const InoutCategoryPageQuery::Wrapper& query, SqlParams& params);
public:
	//获取收支类别名称列表（条件）
	list<InoutCategoryDO> selectNames(const InoutCategoryQuery::Wrapper& query);
	//统计总条数
	uint64_t count(const InoutCategoryPageQuery::Wrapper& query);
	//获取收支类别列表（条件+分页）
	list<InoutCategoryDO> selectPage(const InoutCategoryPageQuery::Wrapper& query);
	//获取指定类别详情
	PtrInoutCategoryDO selectById(const string& id);

};

#endif // !INOUTCATEGORYDAO_H_