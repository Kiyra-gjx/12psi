#pragma once
#ifndef _ORDERDO_H_
#define _ORDERDO_H_

#include "./DoInclude.h"

// 采购单主表DO - 对应bor表
class BuyDO : public BaseDO {
	// 订单ID
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
	// 审核状态
	MYSQL_SYNTHESIZE(int, examine, Examine);
	// 核销状态
	MYSQL_SYNTHESIZE(int, nucleus, Nucleus);
	// 费用状态
	MYSQL_SYNTHESIZE(int, cse, Cse);
	// 发展状态
	MYSQL_SYNTHESIZE(int, invoice, Invoice);
	// 核对状态
	MYSQL_SYNTHESIZE(int, check, Check);
	// 制单人
	MYSQL_SYNTHESIZE(string, user, User);

	
public:
	BuyDO() : BaseDO("buy") {
		//联表查询,需要添加不同的字段值
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("supplier", "s", supplier);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("examine", "s", examine);
		MYSQL_ADD_FIELD("nucleus", "d", nucleus);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("people", "s", people);
		MYSQL_ADD_FIELD("cse", "s", cse);
		MYSQL_ADD_FIELD("invoice", "s", invoice);
		MYSQL_ADD_FIELD("check", "s", check);
		MYSQL_ADD_FIELD("user", "s", user);
	}
};


// 采购订单详情表DO - 对应bor_info表
class BuyInfoDO : public BaseDO {
	// 详情ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 所属ID (关联buy表)
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 关联详情
	MYSQL_SYNTHESIZE(string, source, Source);
	// 所属商品 (关联goods表)
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
	// 折扣额
	MYSQL_SYNTHESIZE(double, dsc, Dsc);
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
	BuyInfoDO() : BaseDO("buy_info") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("source", "s", source);
		MYSQL_ADD_FIELD("goods", "s", goods);
		
	}
};

// 商品表DO - 对应goods表
class GoodsDO : public BaseDO {
	// 商品ID
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
	// 商品单位
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
	// 产品类型
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
	// 序列产品
	MYSQL_SYNTHESIZE(int, serial, Serial);
	// 批次产品
	MYSQL_SYNTHESIZE(int, batch, Batch);
	// 有效期
	MYSQL_SYNTHESIZE(int, validity, Validity);
	// 保质期
	MYSQL_SYNTHESIZE(int, protect, Protect);
	// 预警阀值
	MYSQL_SYNTHESIZE(int, threshold, Threshold);
	// 扩展信息
	MYSQL_SYNTHESIZE(string, more, More);

public:
	GoodsDO() : BaseDO("goods") {
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
		MYSQL_ADD_FIELD("data", "s", this->data);
		MYSQL_ADD_FIELD("imgs", "s", imgs);
		MYSQL_ADD_FIELD("details", "s", details);
		MYSQL_ADD_FIELD("units", "s", units);
		MYSQL_ADD_FIELD("strategy", "s", strategy);
		MYSQL_ADD_FIELD("serial", "i", serial);
		MYSQL_ADD_FIELD("batch", "i", batch);
		MYSQL_ADD_FIELD("validity", "i", validity);
		MYSQL_ADD_FIELD("protect", "i", protect);
		MYSQL_ADD_FIELD("threshold", "i", threshold);
		MYSQL_ADD_FIELD("more", "s", more);
	}
};

// 兼容性定义 - 保持向后兼容
typedef BuyInfoDO DingdanDetailDO;
// 智能指针类型定义
typedef std::shared_ptr<BuyDO> PtrBuyDO;
typedef std::shared_ptr<BuyInfoDO> PtrBuyInfoDO;
typedef std::shared_ptr<GoodsDO> PtrGoodsDO;
//
//// 兼容性智能指针定义
//typedef std::shared_ptr<DingdanDetailDO> PtrDetailDO;

class LogDO : public BaseDO {
	// ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 操作时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 操作用户
	MYSQL_SYNTHESIZE(string, user, User);
	// 操作信息
	MYSQL_SYNTHESIZE(string, info, Info);

	LogDO() : BaseDO("log") {
		MYSQL_ADD_FIELD("id", "s", id);
		MYSQL_ADD_FIELD("time", "s", time);
		MYSQL_ADD_FIELD("user", "s", user);
		MYSQL_ADD_FIELD("info", "s", info);
	}
};

#endif // !_DINGDANDO_H_
