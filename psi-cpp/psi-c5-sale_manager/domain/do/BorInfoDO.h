#pragma once

#ifndef _BORINFO_DO_
#define _BORINFO_DO_

#include "DoInclude.h"

class BorInfoDO : public BaseDO {

	// 主键ID
	MYSQL_SYNTHESIZE(std::string, id, Id);
	// 所属ID（外键到主表）
	MYSQL_SYNTHESIZE(std::string, pid, Pid);
	// 所属商品
	MYSQL_SYNTHESIZE(std::string, goods, Goods);
	// 辅助属性
	MYSQL_SYNTHESIZE(std::string, attr, Attr);
	// 单位
	MYSQL_SYNTHESIZE(std::string, unit, Unit);
	// 仓库
	MYSQL_SYNTHESIZE(std::string, warehouse, Warehouse);
	// 单价 decimal(12,4)
	MYSQL_SYNTHESIZE(double, price, Price);
	// 数量 decimal(12,4)
	MYSQL_SYNTHESIZE(double, nums, Nums);
	// 折扣率 decimal(5,2)
	MYSQL_SYNTHESIZE(double, discount, Discount);
	// 折扣额 decimal(12,4)
	MYSQL_SYNTHESIZE(double, dsc, Dsc);
	// 金额 decimal(12,4)
	MYSQL_SYNTHESIZE(double, total, Total);
	// 税率 decimal(5,2)
	MYSQL_SYNTHESIZE(double, tax, Tax);
	// 税额 decimal(12,4)
	MYSQL_SYNTHESIZE(double, tat, Tat);
	// 价税合计 decimal(12,4)
	MYSQL_SYNTHESIZE(double, tpt, Tpt);
	// 备注信息
	MYSQL_SYNTHESIZE(std::string, data, Data);
	// 入库数量 decimal(12,4)
	MYSQL_SYNTHESIZE(double, handle, Handle);


public:
	BorInfoDO() : BaseDO("bor_info") {
		// 主键
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// 普通字段（字段名，类型标识，成员变量）
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("goods", "s", goods);
		MYSQL_ADD_FIELD("attr", "s", attr);
		MYSQL_ADD_FIELD("unit", "s", unit);
		MYSQL_ADD_FIELD("warehouse", "s", warehouse);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("nums", "d", nums);
		MYSQL_ADD_FIELD("discount", "d", discount);
		MYSQL_ADD_FIELD("dsc", "d", dsc);
		MYSQL_ADD_FIELD("total", "d", total);
		MYSQL_ADD_FIELD("tax", "d", tax);
		MYSQL_ADD_FIELD("tat", "d", tat);
		MYSQL_ADD_FIELD("tpt", "d", tpt);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("handle", "d", handle);
	}
};

typedef std::shared_ptr<BorInfoDO> PtrBorInfoDO;

#endif // !_BORINFO_DO_

