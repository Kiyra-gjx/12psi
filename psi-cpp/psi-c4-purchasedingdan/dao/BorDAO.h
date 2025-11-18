#pragma once
#ifndef _DINGDANDAO_H_
#define _DINGDANDAO_H_

#include "BaseDAO.h"
#include "../domain/do/DingdanDO.h"
#include "./BorMapper.h"
#include "domain/dto/DingdanDTO.h"

/**
 * 采购订单数据库访问对象 - 专注于bor表操作
 */
class BorDAO : public BaseDAO
{
private:

public:

	// 批量审核状态更新
	bool batchUpdateExamineStatus(const oatpp::List<oatpp::String>& ids, int examineStatus);

	// 更新订单主表信息
	bool updateBor(const PtrBorDO& borDO);
};

#endif // !_DINGDANDAO_H_