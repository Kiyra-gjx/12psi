#pragma once

#ifndef _BUYINFO_DO_H
#define _BUYINFO_DO_H
#include "DoInclude.h"

/**
 * 采购单info (已更新为 buy_info 表结构)
 */
class BuyInfoDO : public BaseDO {
	// id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属id
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 关联详情|BOR 
	MYSQL_SYNTHESIZE(string, source, Source);
	// 所属商品 
	MYSQL_SYNTHESIZE(string, goods, Goods);
	// 辅助属性
	MYSQL_SYNTHESIZE(string, attr, Attr);
	// 单位
	MYSQL_SYNTHESIZE(string, unit, Unit);
	// 仓库 
	MYSQL_SYNTHESIZE(string, warehouse, Warehouse);
	// 批次号
	MYSQL_SYNTHESIZE(string, batch, Batch);
	// 生产日期
	MYSQL_SYNTHESIZE(string, mfd, Mfd);
	// 单价
	MYSQL_SYNTHESIZE(double, price, Price);
	// 数量
	MYSQL_SYNTHESIZE(double, nums, Nums);
	// 序列号
	MYSQL_SYNTHESIZE(string, serial, Serial);
	// 折扣率
	MYSQL_SYNTHESIZE(double, discount, Discount);
	// 金额
	MYSQL_SYNTHESIZE(double, total, Total);
	// 税率
	MYSQL_SYNTHESIZE(double, tax, Tax);
	// 税额
	MYSQL_SYNTHESIZE(double, tat, Tat);
	// 价税合计
	MYSQL_SYNTHESIZE(double, tpt, Tpt);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 退货数量
	MYSQL_SYNTHESIZE(double, retreat, Retreat);


public:
	BuyInfoDO() : BaseDO("buy_info")
	{
		// 初始化所有 string
		id = std::make_shared<string>("");
		pid = std::make_shared<string>("");
		source = std::make_shared<string>("");
		goods = std::make_shared<string>("");
		attr = std::make_shared<string>("");
		unit = std::make_shared<string>("");
		warehouse = std::make_shared<string>("");
		batch = std::make_shared<string>("");
		mfd = std::make_shared<string>("1990-01-01");
		serial = std::make_shared<string>("");
		data = std::make_shared<string>("");

		// 初始化所有 double
		price = std::make_shared<double>(0.0);
		nums = std::make_shared<double>(0.0);
		discount = std::make_shared<double>(0.0);
		total = std::make_shared<double>(0.0);
		tax = std::make_shared<double>(0.0);
		tat = std::make_shared<double>(0.0);
		tpt = std::make_shared<double>(0.0);
		retreat = std::make_shared<double>(0.0);

		// --- 数据库字段映射 ---
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("goods", "s", goods);
		MYSQL_ADD_FIELD("attr", "s", attr);
		MYSQL_ADD_FIELD("unit", "s", unit);
		MYSQL_ADD_FIELD("warehouse", "s", warehouse);
		MYSQL_ADD_FIELD("batch", "s", batch);
		MYSQL_ADD_FIELD("mfd", "s", mfd);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("nums", "d", nums);
		MYSQL_ADD_FIELD("serial", "s", serial);
		MYSQL_ADD_FIELD("discount", "d", discount);
		MYSQL_ADD_FIELD("total", "d", total);
		MYSQL_ADD_FIELD("tax", "d", tax);
		MYSQL_ADD_FIELD("tat", "d", tat);
		MYSQL_ADD_FIELD("tpt", "d", tpt);
		MYSQL_ADD_FIELD("data", "s", this->data);
		MYSQL_ADD_FIELD("retreat", "d", retreat);
	}
};

typedef std::shared_ptr<BuyInfoDO> PtrBuyInfoDO;
#endif // !_BUYINFO_DO_H