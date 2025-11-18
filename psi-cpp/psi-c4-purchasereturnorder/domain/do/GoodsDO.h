#pragma once

#ifndef _GOODS_DO_
#define _GOODS_DO_
#include "DoInclude.h"

/**
 * 商品数据库实体类
 */
class GoodsDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 商品名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 拼音信息
	MYSQL_SYNTHESIZE(string, py, Py);
	// 商品编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 规格型号
	MYSQL_SYNTHESIZE(string, spec, Spec);
	// 商品类别
	MYSQL_SYNTHESIZE(string, category, Category);
	// 商品品牌
	MYSQL_SYNTHESIZE(string, brand, Brand);
	// 商品单位[*:常规单位|-1:多单位]
	MYSQL_SYNTHESIZE(string, unit, Unit);
	// 采购价格
	MYSQL_SYNTHESIZE(double, buy, Buy);
	// 销售价格
	MYSQL_SYNTHESIZE(double, sell, Sell);
	// 商品条码
	MYSQL_SYNTHESIZE(string, code, Code);
	// 商品货位
	MYSQL_SYNTHESIZE(string, location, Location);
	// 库存阈值
	MYSQL_SYNTHESIZE(double, stock, Stock);
	// 产品类型[0:常规商品|1:服务商品]
	MYSQL_SYNTHESIZE(int, type, Type);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
	// 商品图像
	MYSQL_SYNTHESIZE(string, imgs, Imgs);
	// 图文详情
	MYSQL_SYNTHESIZE(string, details, Details);
	// 多单位配置
	MYSQL_SYNTHESIZE(string, units, Units);
	// 折扣策略
	MYSQL_SYNTHESIZE(string, strategy, Strategy);
	// 序列产品[0:关闭|1:启用]
	MYSQL_SYNTHESIZE(int, serial, Serial);
	// 批次产品[0:关闭|1:启用]
	MYSQL_SYNTHESIZE(int, batch, Batch);
	// 有效期[0:关闭|1:启用]
	MYSQL_SYNTHESIZE(int, validity, Validity);
	// 保质期
	MYSQL_SYNTHESIZE(short, protect, Protect);
	// 预警阀值
	MYSQL_SYNTHESIZE(short, threshold, Threshold);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);

public:
	GoodsDO() : BaseDO("goods")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("py", "s", py);
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("spec", "s", spec);
		MYSQL_ADD_FIELD("category", "s", category);
		MYSQL_ADD_FIELD("brand", "s", brand);
		MYSQL_ADD_FIELD("unit", "s", unit);
		MYSQL_ADD_FIELD("buy", "d", buy);
		MYSQL_ADD_FIELD("sell", "d", sell);
		MYSQL_ADD_FIELD("code", "s", code);
		MYSQL_ADD_FIELD("location", "s", location);
		MYSQL_ADD_FIELD("stock", "d", stock);
		MYSQL_ADD_FIELD("type", "i", type);
		MYSQL_ADD_FIELD("data", "s", data);
		MYSQL_ADD_FIELD("imgs", "s", imgs);
		MYSQL_ADD_FIELD("details", "s", details);
		MYSQL_ADD_FIELD("units", "s", units);
		MYSQL_ADD_FIELD("strategy", "s", strategy);
		MYSQL_ADD_FIELD("serial", "i", serial);
		MYSQL_ADD_FIELD("batch", "i", batch);
		MYSQL_ADD_FIELD("validity", "i", validity);
		MYSQL_ADD_FIELD("protect", "s", protect);
		MYSQL_ADD_FIELD("threshold", "s", threshold);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

// 给GoodsDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GoodsDO> PtrGoodsDO;
#endif // !_GOODS_DO_