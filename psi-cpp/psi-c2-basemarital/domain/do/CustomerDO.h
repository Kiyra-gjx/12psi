#ifndef _CUSTOMERDO_H
#define _CUSTOMERDO_H

#include "DoInclude.h"
/**
 * 客户数据对象
 */
class CustomerDO : public BaseDO
{
public:
	//自增id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 客户编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 客户名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 所属用户群
	MYSQL_SYNTHESIZE(string, user, User);
	// 客户类别
	MYSQL_SYNTHESIZE(string, category, Category);
	// 客户等级
	MYSQL_SYNTHESIZE(string, grade, Grade);
	// 开户银行
	MYSQL_SYNTHESIZE(string, bank, Bank);
	// 银行账号
	MYSQL_SYNTHESIZE(string, account, Account);
	// 纳税号码
	MYSQL_SYNTHESIZE(string, tax, Tax);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data_, Data_);
	// 联系资料
	MYSQL_SYNTHESIZE(string, contacts, Contacts);
	//拼音简写
	MYSQL_SYNTHESIZE(string, py, Py);
	// 账户余额
	MYSQL_SYNTHESIZE(double, balance, Balance);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);


public:
	CustomerDO() :BaseDO("customer") {
		MYSQL_ADD_FIELD_NULLABLE("id", "s", id, false);
		MYSQL_ADD_FIELD_PK("number", "s", number);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("frame", "s", frame, false);
		MYSQL_ADD_FIELD_NULLABLE("user", "s", user, false);
		MYSQL_ADD_FIELD_NULLABLE("category", "s", category, false);
		MYSQL_ADD_FIELD_NULLABLE("grade", "s", grade, false);
		MYSQL_ADD_FIELD("bank", "s", bank);
		MYSQL_ADD_FIELD("account", "s", account);
		MYSQL_ADD_FIELD("tax", "s", tax);
		MYSQL_ADD_FIELD("data", "s", data_);
		MYSQL_ADD_FIELD("contacts", "s", contacts);
		MYSQL_ADD_FIELD_NULLABLE("py", "s", py, false);
		MYSQL_ADD_FIELD("balance", "d", balance);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

using CustomerDOPtr = std::shared_ptr<CustomerDO>;



#endif // !_CUSTOMERDO_H
