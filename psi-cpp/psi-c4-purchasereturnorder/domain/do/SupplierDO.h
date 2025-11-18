#pragma once

#ifndef _SUPPLIER_DO_
#define _SUPPLIER_DO_
#include "DoInclude.h"

/**
 * 供应商数据库实体类
 */
class SupplierDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 供应商名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 拼音信息
	MYSQL_SYNTHESIZE(string, py, Py);
	// 供应商编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 所属用户
	MYSQL_SYNTHESIZE(string, user, User);
	// 供应商类别
	MYSQL_SYNTHESIZE(string, category, Category);
	// 增值税税率
	MYSQL_SYNTHESIZE(double, rate, Rate);
	// 开户银行
	MYSQL_SYNTHESIZE(string, bank, Bank);
	// 银行账号
	MYSQL_SYNTHESIZE(string, account, Account);
	// 纳税号码
	MYSQL_SYNTHESIZE(string, tax, Tax);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 联系资料
	MYSQL_SYNTHESIZE(string, contacts, Contacts);
	// 应付款余额
	MYSQL_SYNTHESIZE(double, balance, Balance);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);


public:
	SupplierDO() : BaseDO("supplier")
	{
		// 主键字段
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 普通字段
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("py", "s", py);
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("category", "s", category);
		MYSQL_ADD_FIELD("rate", "d", rate);
		MYSQL_ADD_FIELD("bank", "s", bank);
		MYSQL_ADD_FIELD("account", "s", account);
		MYSQL_ADD_FIELD("tax", "s", tax);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("contacts", "t", contacts);
		MYSQL_ADD_FIELD("balance", "d", balance);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

// 给SupplierDO智能指针设定一个别名方便使用
typedef std::shared_ptr<SupplierDO> PtrSupplierDO;
#endif // !_SUPPLIER_DO_