#pragma once

#ifndef _ROOM_DO_
#define _ROOM_DO_

#include "DoInclude.h"

/**
*  room数据对象
*/

class RoomDO : public BaseDO
{
private:
	// ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属仓库
	MYSQL_SYNTHESIZE(string, warehouse, Warehouse);
	// 所属商品
	MYSQL_SYNTHESIZE(string, goods, Goods);
	// 辅助属性
	MYSQL_SYNTHESIZE(string, attr, Attr);
	// 库存数量
	MYSQL_SYNTHESIZE(double, nums, Nums);
public:
	RoomDO() : BaseDO("room")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("warehouse", "s", warehouse);
		MYSQL_ADD_FIELD("goods", "s", goods);
		MYSQL_ADD_FIELD_NULLABLE("attr", "s", attr, true);
		MYSQL_ADD_FIELD("nums", "d", nums);
	}
};

#endif // !_ROOM_DO_
