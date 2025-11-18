#ifndef  ACCOUNT_H
#define ACCOUNT_H
#include "DoInclude.h"

class AccountDO :public  BaseDO
{
	//账户id
	MYSQL_SYNTHESIZE(string, id, Id);
	//账户名称
	MYSQL_SYNTHESIZE(string, accountname, Accountname);
	//账户编号
	MYSQL_SYNTHESIZE(string, accountnumber, Accountnumber);
	//所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	//余额日期
	MYSQL_SYNTHESIZE(string, time, Time);
	//期初余额
	MYSQL_SYNTHESIZE(double, initial, Initial);
	//账户余额
	MYSQL_SYNTHESIZE(double, balance, Balance);
	//备注信息
	MYSQL_SYNTHESIZE(string, data, Data);

public:
	AccountDO() :BaseDO("account") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("accountname", "s", accountname);
		MYSQL_ADD_FIELD("accountnumber", "s", accountnumber);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("initial", "d", initial);
		MYSQL_ADD_FIELD("balance", "d", balance);
		MYSQL_ADD_FIELD("data", "s", data);
	}
};
// 定义一个用户实体的智能指针
typedef std::shared_ptr<AccountDO> PtrAccountDO;

#endif // ! ACCOUNT_H