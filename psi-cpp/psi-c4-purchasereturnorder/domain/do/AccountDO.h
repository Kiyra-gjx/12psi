#pragma once

#pragma once

#ifndef _ACCOUNT_DO_
#define _ACCOUNT_DO_
#include "DoInclude.h"

/**
 * 账户数据库实体类
 */
class AccountDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 账户名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 账户编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 余额日期
	MYSQL_SYNTHESIZE(string, time, Time);
	// 期初余额
	MYSQL_SYNTHESIZE(double, initial, Initial);
	// 账户余额
	MYSQL_SYNTHESIZE(double, balance, Balance);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);

public:
	AccountDO() : BaseDO("account")  // 假设表名为account，需根据实际表名调整
	{
		// 主键字段
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 普通字段
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("initial", "d", initial);
		MYSQL_ADD_FIELD("balance", "d", balance);
		MYSQL_ADD_FIELD("data", "s", data);
	}
};

// 给AccountDO智能指针设定一个别名方便使用
typedef std::shared_ptr<AccountDO> PtrAccountDO;
#endif // !_ACCOUNT_DO_