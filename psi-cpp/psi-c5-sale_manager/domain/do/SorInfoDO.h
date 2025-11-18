#pragma once

#ifndef _SORINFO_DO_
#define _SORINFO_DO_
#include "DoInclude.h"

/*
	销售订单详情DO （对应数据库的sor_info表）
*/
class SorInfoDO : public BaseDO
{

	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, pid, Pid);
	MYSQL_SYNTHESIZE(string, goods, Goods);
	MYSQL_SYNTHESIZE(string, attr, Attr);
	MYSQL_SYNTHESIZE(string, unit, Unit);
	MYSQL_SYNTHESIZE(string, warehouse, Warehouse);
	MYSQL_SYNTHESIZE(double, price, Price);
	MYSQL_SYNTHESIZE(int, nums, Nums);
	MYSQL_SYNTHESIZE(double, discount, Discount);
	MYSQL_SYNTHESIZE(double, dsc, Dsc);
	MYSQL_SYNTHESIZE(double, total, Total);
	MYSQL_SYNTHESIZE(double, tax, Tax);
	MYSQL_SYNTHESIZE(double, tat, Tat);
	MYSQL_SYNTHESIZE(double, tpt, Tpt);
	MYSQL_SYNTHESIZE(string, data, Data);
	MYSQL_SYNTHESIZE(double, handle, Handle);
	// 商品信息扩展，用于报表显示
	MYSQL_SYNTHESIZE(string, goodsName, GoodsName);
	MYSQL_SYNTHESIZE(string, spec, Spec);

public:
	SorInfoDO() :BaseDO("sor_info")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("pid", "s", pid, false);
		MYSQL_ADD_FIELD_NULLABLE("goods", "s", goods, false);
		MYSQL_ADD_FIELD_NULLABLE("attr", "s", attr, true);
		MYSQL_ADD_FIELD_NULLABLE("unit", "s", unit, false);
		MYSQL_ADD_FIELD_NULLABLE("warehouse", "s", warehouse, true);
		MYSQL_ADD_FIELD_NULLABLE("price", "i", price, false);
		MYSQL_ADD_FIELD_NULLABLE("nums", "i", nums, false);
		MYSQL_ADD_FIELD_NULLABLE("discount", "i", discount, false);
		MYSQL_ADD_FIELD_NULLABLE("dsc", "i", dsc, false);
		MYSQL_ADD_FIELD_NULLABLE("total", "i", total, false);
		MYSQL_ADD_FIELD_NULLABLE("tax", "i", tax, false);
		MYSQL_ADD_FIELD_NULLABLE("tat", "i", tat, false);
		MYSQL_ADD_FIELD_NULLABLE("tpt", "i", tpt, false);
		MYSQL_ADD_FIELD_NULLABLE("data", "s", this->data, true);
		MYSQL_ADD_FIELD_NULLABLE("handle", "i", handle, true);
		//MYSQL_ADD_FIELD_NULLABLE("goodsName", "s", goodsName);
		//MYSQL_ADD_FIELD_NULLABLE("spec", "s", spec);	
	}
};
typedef std::shared_ptr<SorInfoDO> PtrSorInfoDO;

#endif 
