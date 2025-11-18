#pragma once
#include "BaseDAO.h"
#include "domain/query/SaleReturnOrderQuery.h"
#include "domain/do/SreInfoDO.h"

class SreInfoDAO : public BaseDAO
{
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SreInfoDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SreDetailQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const SreDetailQuery::Wrapper& query, SqlParams& params);
public:

	uint64_t count(const SreDetailQuery::Wrapper& query);

	//通过主id获取所有符合条件的InfoDO
	list<SreInfoViewDO> selectById(const SreDetailQuery::Wrapper& query);

	bool insert(const shared_ptr<SreInfoDO>& sreInfDO);
	
	//?根据ID(pid)删除所有关联的销售退货单详情记录
	bool removeByPid(const string& pid);
};
