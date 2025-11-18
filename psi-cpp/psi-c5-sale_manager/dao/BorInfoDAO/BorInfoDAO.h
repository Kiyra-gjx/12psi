#pragma once
#pragma once
#ifndef _BORINFODAO_H_
#define _BORINFODAO_H_

#include "BaseDAO.h"
#include "../../domain/do/BorInfoDO.h"

/**
 * 采购订单详情表数据库访问对象
 */
class BorInfoDAO : public BaseDAO
{
public:
	// 根据订单ID查询详情
	PtrBorInfoDO selectBorInfoByPid(const std::string& pid);

	// 更新订单详情
	bool updateBorInfo(const PtrBorInfoDO& borInfoDO);

	// 根据订单ID和商品ID查询详情
	PtrBorInfoDO selectByPidAndGoods(const std::string& pid, const std::string& goods);
};

#endif // !_BORINFODAO_H_