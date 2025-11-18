#pragma once


#ifndef _REVIEWORDER_DAO_
#define _REVIEWORDER_DAO_
#include "BaseDAO.h"
#include"../domain/do/getreturnlistDO.h"
#include"../domain/do/BreInfoDO.h"
#include"../domain/do/RoomDO.h"
#include"domain/do/RoomInfoDO.h"
#include"domain/do/AccountInfoDO.h"

/**
 * 审核操作的数据库操作实现
 */
class ReviewOrderDAO : public BaseDAO
{
private:

public:

	// 通过ID查询采购退货单的数据
	PtrBreDO selectById(std::string id);

	// 通过Pid查询采购退货单的详情
	// 返回值是list，所以用的是BreInfoDO，而不是PtrBreInfoDO
	std::list<BreInfoDO> selectByPid(std::string pid);

	// 通过 goods 和 warehouse 来查看商品库存
	PtrRoomDO selectGoods(std::string goods, std::string warehouse);

	// 通过 pid 和 class 来查找资金记录的ID
	PtrAccountInfoDO selectByPC(string pid, string cid);

	// 仓库ID、单据ID、单据详情ID --> 仓库详情
	PtrRoomInfoDO selectByPCI(std::string pid, std::string cid, std::string info);

};
#endif // !_REVIEWORDER_DAO_
