#pragma once
#ifndef _SREBILL_DAO_H_
#define _SREBILL_DAO_H_

#include "BaseDAO.h"
#include "domain/do/SrebillDO.h"
#include "SrebillMapper.h"
#include "../../domain/query/SaleReturnOrderQuery.h"

/**
 * 销售退货核销数据表操作实现
 */
class SrebillDAO : public BaseDAO
{
public:
	//*************以下都是业务功能*******************
	//// 统计数据条数
	//uint64_t count(const SreListQuery::Wrapper& query);
	// 插入数据
	uint64_t insert(const PtSrebillDO& dto);
	// 修改数据
	bool update(const PtSrebillDO& dto);
	// 通过ID删除数据
	bool removeById(const string& id);
	// 通过销售退货单ID删除数据
	bool removeByPid(const string& pid);
	// 通过ID查询数据
	PtSrebillDO selectById(const string& id);
	// 通过销售退货单ID查询数据
	list<PtSrebillDO> selectByPid(const string& pid);

private:
	// 构建查询条件
	string buildQueryCondition(const SreDetailQuery::Wrapper& query, SqlParams& params);
};

#endif // !_SREBILL_DAO_H_