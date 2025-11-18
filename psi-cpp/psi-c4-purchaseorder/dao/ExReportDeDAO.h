#pragma once

#ifndef _EXREPORTDE_DAO_
#define _EXREPORTDE_DAO_
#include "BaseDAO.h"
#include "../domain/query/ExReportDeQUERY.h"
#include "domain/do/BuyInfoDO.h"

/**
 * 示例表数据库操作实现
 */
class ExReportDeDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	inline std::string queryConditionBuilder(const ExReportDeQUERY::Wrapper& query, SqlParams& params);

public:
	// 统计数据条数
	uint64_t count(const ExReportDeQUERY::Wrapper& query);
	// 分页查询数据
	std::list<BuyInfoDO> selectWithPage(const ExReportDeQUERY::Wrapper& query);

	// 统计数据条数
	//uint64_t count(const ExReportDeQUERY::Wrapper& query);
	// 分页查询数据
	// std::shared_ptr<PotableInfoDO> ExReportDeDAO::selectOne(const ExReportDeQUERY::Wrapper& query);
	//// 通过姓名查询数据
//	std::list<ExReportSimDO> selectByName(const string& name);
	// 通过ID查询数据
	// PotableInfoDO selectById(std::string id);
};
#endif // !_SAMPLE_DAO_
