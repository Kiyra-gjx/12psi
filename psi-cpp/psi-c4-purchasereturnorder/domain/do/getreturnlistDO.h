#pragma once

#ifndef _BRE_DO_
#define _BRE_DO_
#include "DoInclude.h"

/**
 * 采购退货单数据库实体类
 */
class BreDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 关联单据
	MYSQL_SYNTHESIZE(string, source, Source);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 供应商
	MYSQL_SYNTHESIZE(string, supplier, Supplier);
	// 单据时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 单据编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 单据金额
	MYSQL_SYNTHESIZE(double, total, Total);
	// 实际金额
	MYSQL_SYNTHESIZE(double, actual, Actual);
	// 实收金额
	MYSQL_SYNTHESIZE(double, money, Money);
	// 单据费用
	MYSQL_SYNTHESIZE(double, cost, Cost);
	// 结算账户
	MYSQL_SYNTHESIZE(string, account, Account);
	// 关联人员
	MYSQL_SYNTHESIZE(string, people, People);
	// 物流信息
	MYSQL_SYNTHESIZE(string, logistics, Logistics);
	// 单据附件
	MYSQL_SYNTHESIZE(string, file, File);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);
	// 审核状态[0:未审核|1:已审核]
	MYSQL_SYNTHESIZE(int, examine, Examine);
	// 核销状态[0:未核销|1:部分核销|2:已核销]
	MYSQL_SYNTHESIZE(int, nucleus, Nucleus);
	// 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算]
	MYSQL_SYNTHESIZE(int, cse, Cse);
	// 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开具]
	MYSQL_SYNTHESIZE(int, invoice, Invoice);
	// 核对状态[0:未核对|1:已核对]
	MYSQL_SYNTHESIZE(int, check, Check);
	// 制单人
	MYSQL_SYNTHESIZE(string, user, User);

public:
	BreDO() : BaseDO("bre")
	{
		// 主键字段
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 普通字段
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("supplier", "s", supplier);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("total", "d", total);
		MYSQL_ADD_FIELD("actual", "d", actual);
		MYSQL_ADD_FIELD("money", "d", money);
		MYSQL_ADD_FIELD("cost", "d", cost);
		MYSQL_ADD_FIELD("account", "s", account);
		MYSQL_ADD_FIELD("people", "s", people);
		MYSQL_ADD_FIELD("logistics", "s", logistics);
		MYSQL_ADD_FIELD("file", "s", file);
		MYSQL_ADD_FIELD("data", "s", this->data);
		MYSQL_ADD_FIELD("more", "s", more);
		MYSQL_ADD_FIELD("examine", "i", examine);
		MYSQL_ADD_FIELD("nucleus", "i", nucleus);
		MYSQL_ADD_FIELD("cse", "i", cse);
		MYSQL_ADD_FIELD("invoice", "i", invoice);
		MYSQL_ADD_FIELD("check", "i", check);
		MYSQL_ADD_FIELD("user", "s", user);
	}
};

// 给BreDO智能指针设定一个别名方便使用
typedef std::shared_ptr<BreDO> PtrBreDO;
#endif // !_BRE_DO_