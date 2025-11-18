#pragma once

#ifndef _BUYJS_DO_H
#define _BUYJS_DO_H
#include "DoInclude.h"

/**
 * Js采购单 (已更新为 buy 表结构)
 */
class BuyJsDO : public BaseDO {
	// 编号
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
	// 实付金额
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
	// 审核状态 [0: 未审核 | 1: 已审核]
	MYSQL_SYNTHESIZE(int, examine, Examine);
	// 核销状态 [0: 未核销 | 1: 部分核销 | 2: 已核销]
	MYSQL_SYNTHESIZE(int, nucleus, Nucleus);
	// 费用状态 [0: 未结算 | 1: 部分结算 | 2: 已结算 | 3: 无需结算]
	MYSQL_SYNTHESIZE(int, cse, Cse);
	// 发票状态 [0: 未开票 | 1: 部分开票 | 2: 已开票 | 3: 无需开具]
	MYSQL_SYNTHESIZE(int, invoice, Invoice);
	// 核对状态 [0: 未核对 | 1: 已核对]
	MYSQL_SYNTHESIZE(int, check, Check);
	// 制单人
	MYSQL_SYNTHESIZE(string, user, User);

public:
	BuyJsDO() : BaseDO("buy") 
	{
		// 初始化所有 string
		id = std::make_shared<string>("");
		source = std::make_shared<string>("");
		frame = std::make_shared<string>(""); 
		supplier = std::make_shared<string>("");
		time = std::make_shared<string>(""); 
		number = std::make_shared<string>("");
		logistics = std::make_shared<string>("");
		file = std::make_shared<string>(""); 
		data = std::make_shared<string>("");
		more = std::make_shared<string>("");
		account = std::make_shared<string>("");
		people = std::make_shared<string>(""); 
		user = std::make_shared<string>(""); 

		// 初始化所有 double
		total = std::make_shared<double>(0.0);
		actual = std::make_shared<double>(0.0);
		money = std::make_shared<double>(0.0);
		cost = std::make_shared<double>(0.0);

		// 初始化所有 int 
		examine = std::make_shared<int>(0);
		nucleus = std::make_shared<int>(0);
		cse = std::make_shared<int>(0);
		invoice = std::make_shared<int>(0);
		check = std::make_shared<int>(0);

		// --- 数据库字段映射 ---
		MYSQL_ADD_FIELD_PK("id", "s", id);
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
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("more", "s", more);
		MYSQL_ADD_FIELD("examine", "i", examine);
		MYSQL_ADD_FIELD("nucleus", "i", nucleus);
		MYSQL_ADD_FIELD("cse", "i", cse);
		MYSQL_ADD_FIELD("invoice", "i", invoice);
		MYSQL_ADD_FIELD("check", "i", check);
		MYSQL_ADD_FIELD("user", "s", user); 
	}
};

typedef std::shared_ptr<BuyJsDO> PtrBuyJsDO;
#endif // !_BUYJS_DO_H