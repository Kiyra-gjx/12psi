#ifndef _ROOMINFO_H_
#define _ROOMINFO_H_
#include "DoInclude.h"

class RoomInfoDO :public BaseDO
{
	//room_info_id
	MYSQL_SYNTHESIZE(int, id, RoomInfoId);
	//所属仓储
	MYSQL_SYNTHESIZE(int, pid, RoomInfoPid);
	//单据类型
	MYSQL_SYNTHESIZE(string, type, RoomInfoType)
	//所属类
	MYSQL_SYNTHESIZE(int, room_info_class, RoomInfoClass);
	//所属详情
	MYSQL_SYNTHESIZE(int, info, RoomInfoInfo);
	//单据时间
	MYSQL_SYNTHESIZE(int, time, RoomInfoTime);
	//方向
	MYSQL_SYNTHESIZE(bool, direction, RoomInfoDirection);
	//基础单价
	MYSQL_SYNTHESIZE(double, price, RoomInfoPrice);
	//基础数量
	MYSQL_SYNTHESIZE(double, nums, RoomInfoNums);

public:
	RoomInfoDO():BaseDO("room_info") {
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("pid", "i", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("room_info_class", "i", room_info_class);
		MYSQL_ADD_FIELD("info", "i", info);
		MYSQL_ADD_FIELD("time", "d", time);
		MYSQL_ADD_FIELD("direction", "b", balance);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("nums", "d", nums);
	}
};

// 定义一个用户实体的智能指针
typedef std::shared_ptr<RoomInfoDO> PtrRoomInfoDO;

#endif // ! ACCOUNT_H