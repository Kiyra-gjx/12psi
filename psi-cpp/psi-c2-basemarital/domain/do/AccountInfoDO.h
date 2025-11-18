#ifndef _ACCOUNT_INFO_DO_
#define _ACCOUNT_INFO_DO_

#include "DoInclude.h"

/**
 * 账户信息数据库实体类
 */

class AccountInfoDO : public BaseDO
{
	//id
	MYSQL_SYNTHESIZE(string, id, Id);
	//所属账户
	MYSQL_SYNTHESIZE(string, pid, Pid);
	//单据类型
	MYSQL_SYNTHESIZE(string, type, Type);
	//所属类
	MYSQL_SYNTHESIZE(string, class_, Class_);
	//单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	//方向[0:出][1:入]
	MYSQL_SYNTHESIZE(int, direction, Direction);
	//金额
	MYSQL_SYNTHESIZE(double, money, Money);


public:
	AccountInfoDO() : BaseDO("account_info")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("class", "s", class_);
		MYSQL_ADD_FIELD("time", "dt", time);
		MYSQL_ADD_FIELD("direction", "i", direction);
		MYSQL_ADD_FIELD("money", "d", money);
	}

};
// 给account_infoDO智能指针设定一个别名方便使用
typedef std::shared_ptr<AccountInfoDO> PtrAccountInfoDO;


#endif // !_ACCOUNT_INFO_DO_