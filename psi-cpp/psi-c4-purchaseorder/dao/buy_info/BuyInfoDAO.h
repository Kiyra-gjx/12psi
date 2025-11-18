#pragma
#ifndef _BUYINFODAO_H
#define _BUYINFODAO_H

#include "BaseDAO.h"
#include "../../domain/do/OrderDO.h"



class BuyInfoDAO:public BaseDAO
{
public:
public:
	// 根据订单ID查询详情
	PtrBuyInfoDO selectByPid(const std::string& pid);

	// 更新订单详情
	bool updateBuyInfo(const PtrBuyInfoDO& borInfoDO);

	// 根据订单ID和商品ID查询详情
	PtrBuyInfoDO selectByPidAndGoods(const std::string& pid, const std::string& goods);
};









#endif