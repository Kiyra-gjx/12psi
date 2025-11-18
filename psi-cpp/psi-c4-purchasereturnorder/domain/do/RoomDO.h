#pragma once


#ifndef _ROOM_DO_
#define _ROOM_DO_
#include "DoInclude.h"

/**
 * 库存数据库实体类
 */
class RoomDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属仓库
	MYSQL_SYNTHESIZE(string, warehouse, Warehouse);
	// 所属商品
	MYSQL_SYNTHESIZE(string, goods, Goods);
	// 辅助属性
	MYSQL_SYNTHESIZE(string, attr, Attr);
	// 库存数量
	MYSQL_SYNTHESIZE(double, nums, Nums);

	// 下面这些是数据库中没有的，但为了方便写代码，加了一些字段
	// 单据详情ID
	MYSQL_SYNTHESIZE(string, info, Info);
	// 单据ID
	MYSQL_SYNTHESIZE(string, cid, Cid);
	// 单据详情的单价
	MYSQL_SYNTHESIZE(double, price, Price);
	// 单据详情的数量
	MYSQL_SYNTHESIZE(double, nb, Nb);

public:
	RoomDO() : BaseDO("room")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("warehouse", "s", warehouse);
		MYSQL_ADD_FIELD("goods", "s", goods);
		MYSQL_ADD_FIELD("attr", "s", attr);
		MYSQL_ADD_FIELD("nums", "d", nums);
	}
};

// 给RoomDO智能指针设定一个别名方便使用
typedef std::shared_ptr<RoomDO> PtrRoomDO;
#endif // !_ROOM_DO_