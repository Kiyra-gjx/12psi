#pragma once
#ifndef _POTABLE_INFO_DO_
#define _POTABLE_INFO_DO_
#include "./DoInclude.h"

//采购单数据库实体类
class PotableInfoDO :public BaseDO
{
    //商品名字
    MYSQL_SYNTHESIZE(string, name, Name);
    // 主键
    MYSQL_SYNTHESIZE(string, id, Id);
    // 所属ID
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
    // 生产日期（date → string）
    MYSQL_SYNTHESIZE(string, mfd, Mfd);
    // 单价（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, price, Price);
    // 数量（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, nums, Nums);
    // 序列号（text → string）
    MYSQL_SYNTHESIZE(string, serial, Serial);
    // 折扣率（decimal(5,2) → double）
    MYSQL_SYNTHESIZE(double, discount, Discount);
    // 折扣额（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, dsc, Dsc);
    // 金额（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, total, Total);
    // 税率（decimal(5,2) → double）
    MYSQL_SYNTHESIZE(double, tax, Tax);
    // 税额（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, tat, Tat);
    // 价税合计（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, tpt, Tpt);
    // 备注信息
    MYSQL_SYNTHESIZE(string, data, Data);
    // 退货数量（decimal(12,4) → double）
    MYSQL_SYNTHESIZE(double, retreat, Retreat);

public:
	PotableInfoDO() :BaseDO("potableInfo")
	{
        MYSQL_ADD_FIELD_PK("name", "s", name);
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
        MYSQL_ADD_FIELD("dsc", "d", dsc);
        MYSQL_ADD_FIELD("total", "d", total);
        MYSQL_ADD_FIELD("tax", "d", tax);
        MYSQL_ADD_FIELD("tat", "d", tat);
        MYSQL_ADD_FIELD("tpt", "d", tpt);
        MYSQL_ADD_FIELD("data", "s", this->data);
        MYSQL_ADD_FIELD("retreat", "d", retreat);
	}

};
#endif
