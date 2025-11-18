#pragma once

#ifndef _SRE_INFO_DO_H
#define _SRE_INFO_DO_H

#include "DoInclude.h"
/* SreInfo 表数据库实体类 */

class SreInfoDO : public BaseDO
{
public:
    // 主键编号
    MYSQL_SYNTHESIZE(string, id, Id);
    // 父级ID
    MYSQL_SYNTHESIZE(string, pid, Pid);
    // 关联详情
    MYSQL_SYNTHESIZE(string, source, Source);
    // 商品ID
    MYSQL_SYNTHESIZE(string, goods, Goods);
    // 商品属性
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
    MYSQL_SYNTHESIZE(double, dsc, Dsc);//折扣额应该是double
    // 合计
    MYSQL_SYNTHESIZE(double, total, Total);
    // 税额
    MYSQL_SYNTHESIZE(double, tax, Tax);
    // 税率
    MYSQL_SYNTHESIZE(double, tat, Tat);
    // 总税额
    MYSQL_SYNTHESIZE(double, tpt, Tpt);
    // 附加数据
    MYSQL_SYNTHESIZE(string, data, Data);
    // 退货标记
    MYSQL_SYNTHESIZE(int, retreat, Retreat);
    //// 生产日期
    //MYSQL_SYNTHESIZE(string, mfd, Mfd); // ————新加生产日期
    // 8. 商品信息扩展（报表场景需用）
    MYSQL_SYNTHESIZE(string, goodsName, GoodsName);               // 商品名称
    MYSQL_SYNTHESIZE(string, spec, Spec);               // 商品规格

public:
    SreInfoDO() : BaseDO("sre_info")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("pid", "s", pid, false);
        MYSQL_ADD_FIELD_NULLABLE("source", "s", source, true);
        MYSQL_ADD_FIELD_NULLABLE("goods", "s", goods, false);
        MYSQL_ADD_FIELD_NULLABLE("attr", "s", attr, true);
        MYSQL_ADD_FIELD_NULLABLE("unit", "s", unit, false);
        MYSQL_ADD_FIELD_NULLABLE("warehouse", "s", warehouse, false);
        MYSQL_ADD_FIELD_NULLABLE("batch", "s", batch, true);
        MYSQL_ADD_FIELD_NULLABLE("mfd", "dt", mfd, true);
        MYSQL_ADD_FIELD_NULLABLE("price", "d", price, false);
        MYSQL_ADD_FIELD_NULLABLE("nums", "d", nums, false);    
        MYSQL_ADD_FIELD_NULLABLE("serial", "s", serial, true);
        MYSQL_ADD_FIELD_NULLABLE("discount", "d", discount, true);
        MYSQL_ADD_FIELD_NULLABLE("dsc", "s", dsc, true);
        MYSQL_ADD_FIELD_NULLABLE("total", "d", total, false);
        MYSQL_ADD_FIELD_NULLABLE("tax", "d", tax, true);
        MYSQL_ADD_FIELD_NULLABLE("tat", "d", tat, true);
        MYSQL_ADD_FIELD_NULLABLE("tpt", "d", tpt, true);
        MYSQL_ADD_FIELD_NULLABLE("data", "s", this->data, true); // data修改为this->data 
        MYSQL_ADD_FIELD_NULLABLE("retreat", "i", retreat, true);
        //MYSQL_ADD_FIELD_NULLABLE("mfd", "s", mfd, false);
        MYSQL_ADD_FIELD_NULLABLE("goodsName", "s", goodsName, false);
        MYSQL_ADD_FIELD_NULLABLE("spec", "s", spec, false);
    }
};

// 给 SreInfoDO 智能指针设定一个别名方便使用
typedef std::shared_ptr<SreInfoDO> PtrSreInfoDO;

class SreInfoViewDO : public SreInfoDO{
    // 商品名称
    MYSQL_SYNTHESIZE(string, goodsName, GoodsName);
    // 商品编号
    MYSQL_SYNTHESIZE(string, goodsNumber, GoodsNumber);
    // 商品规格
    MYSQL_SYNTHESIZE(string, goodsSpec, GoodsSpec);
};

#endif // !_SRE_INFO_DO_H