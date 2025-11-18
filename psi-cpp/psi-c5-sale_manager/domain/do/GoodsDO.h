#pragma once

#ifndef _GOODS_DO_H
#define _GOODS_DO_H

#include "DoInclude.h"
/* Goods商品数据库实体类 */

class GoodsDO : public BaseDO
{
    //编号
    MYSQL_SYNTHESIZE(string, id, Id);
    // 姓名
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
    MYSQL_SYNTHESIZE(int, protect, Protect);
    // 预警阀值
    MYSQL_SYNTHESIZE(int, threshold, Threshold);
    // 扩展信息
    MYSQL_SYNTHESIZE(string, more, More);

public:
    // MYSQL_ADD_FIELD_NULLABLE
    GoodsDO() : BaseDO("goods")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
        MYSQL_ADD_FIELD_NULLABLE("py", "s", py, false);
        MYSQL_ADD_FIELD_NULLABLE("number", "s", number, false);
        MYSQL_ADD_FIELD_NULLABLE("spec", "s", spec, true);
        MYSQL_ADD_FIELD_NULLABLE("category", "s", category, false);
        MYSQL_ADD_FIELD_NULLABLE("brand", "s", brand, true);
        MYSQL_ADD_FIELD_NULLABLE("unit", "s", unit, false);
        MYSQL_ADD_FIELD_NULLABLE("buy", "d", buy, false);
        MYSQL_ADD_FIELD_NULLABLE("sell", "d", sell, false);
        MYSQL_ADD_FIELD_NULLABLE("code", "s", code, true);
        MYSQL_ADD_FIELD_NULLABLE("location", "s", location, true);
        MYSQL_ADD_FIELD_NULLABLE("stock", "d", stock, false);
        MYSQL_ADD_FIELD_NULLABLE("type", "i", type, false);
        MYSQL_ADD_FIELD_NULLABLE("data", "s", this->data, true);
        MYSQL_ADD_FIELD_NULLABLE("imgs", "s", imgs, true);
        MYSQL_ADD_FIELD_NULLABLE("details", "s", details, true);
        MYSQL_ADD_FIELD_NULLABLE("units", "s", units, true);
        MYSQL_ADD_FIELD_NULLABLE("strategy", "s", strategy, true);
        MYSQL_ADD_FIELD_NULLABLE("serial", "i", serial, true);
        MYSQL_ADD_FIELD_NULLABLE("batch", "i", batch, true);
        MYSQL_ADD_FIELD_NULLABLE("validity", "i", validity, true);
        MYSQL_ADD_FIELD_NULLABLE("protect", "i", protect, true);
        MYSQL_ADD_FIELD_NULLABLE("threshold", "i", threshold, true);
        MYSQL_ADD_FIELD_NULLABLE("more", "s", more, false);
    }
};

// 给GoodsDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GoodsDO> PtrGoodsDO;
#endif // !_GOODS_DO_H
