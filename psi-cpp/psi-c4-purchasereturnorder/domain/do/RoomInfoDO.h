#pragma once


#pragma once


#ifndef _ROOM_INFO_DO_
#define _ROOM_INFO_DO_
#include "DoInclude.h"

/**
 * 库存详情数据库实体类
 */
class RoomInfoDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属仓储
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 单据类型
	MYSQL_SYNTHESIZE(string, type, Type);
	// 所属单据ID
	MYSQL_SYNTHESIZE(string, cid, Cid);  // 修正关键字冲突，将class改为cid
	// 所属单据详情ID
	MYSQL_SYNTHESIZE(string, info, Info);
	// 单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 方向[0:出|1:入]
	MYSQL_SYNTHESIZE(int, direction, Direction);
	// 基础单价
	MYSQL_SYNTHESIZE(double, price, Price);
	// 基础数量
	MYSQL_SYNTHESIZE(double, nums, Nums);

public:
	RoomInfoDO() : BaseDO("room_info")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("class", "s", cid);  // 数据库字段仍为class，映射到cid成员
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("time", "datetime", time);
		MYSQL_ADD_FIELD("direction", "i", direction);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("nums", "d", nums);
	}
};

// 给RoomInfoDO智能智能指针设定一个别名方便使用
typedef std::shared_ptr<RoomInfoDO> PtrRoomInfoDO;
#endif // !_ROOM_INFO_DO_