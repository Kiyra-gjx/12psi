#pragma once

#include "DoInclude.h"

class SellInfoDO : public BaseDO
{
public:
    // 按照表中字段顺序定义

    // 主键字段
    MYSQL_SYNTHESIZE(std::string, id, Id);                          // 自增主键

    // 关联字段
    MYSQL_SYNTHESIZE(std::string, pid, Pid);                       // 所属ID
    MYSQL_SYNTHESIZE(std::string, source, Source);                 // 关联详情|SOR
    MYSQL_SYNTHESIZE(std::string, goods, Goods);                   // 所属商品

    // 字符串字段
    MYSQL_SYNTHESIZE(std::string, attr, Attr);                  // 辅助属性
    MYSQL_SYNTHESIZE(std::string, unit, Unit);                  // 单位

    // 数值字段
    MYSQL_SYNTHESIZE(std::string, warehouse, Warehouse);           // 仓库
    MYSQL_SYNTHESIZE(std::string, batch, Batch);                // 批次号
    MYSQL_SYNTHESIZE(std::string, mfd, Mfd);                       // 生产日期（时间戳）

    // 金额相关字段
    MYSQL_SYNTHESIZE(double, price, Price);                     // 单价
    MYSQL_SYNTHESIZE(double, nums, Nums);                       // 数量
    MYSQL_SYNTHESIZE(std::string, serial, Serial);              // 序列号
    MYSQL_SYNTHESIZE(double, discount, Discount);               // 折扣率
    MYSQL_SYNTHESIZE(double, dsc, Dsc);                         // 折扣额
    MYSQL_SYNTHESIZE(double, total, Total);                     // 金额
    MYSQL_SYNTHESIZE(double, tax, Tax);                         // 税率
    MYSQL_SYNTHESIZE(double, tat, Tat);                         // 税额
    MYSQL_SYNTHESIZE(double, tpt, Tpt);                         // 价税合计
    MYSQL_SYNTHESIZE(std::string, data, Data);                  // 备注信息
    MYSQL_SYNTHESIZE(double, retreat, Retreat);                 // 退货数量

public:
    SellInfoDO() : BaseDO("sell_info")
    {
        // 严格按照表中字段顺序注册

        // 主键字段
        MYSQL_ADD_FIELD_PK("id", "s", id);                      // int -> "i"

        // 关联字段
        MYSQL_ADD_FIELD("pid", "s", pid);                       // int -> "i"
        MYSQL_ADD_FIELD("source", "s", source);                 // int -> "i"
        MYSQL_ADD_FIELD("goods", "s", goods);                   // int -> "i"

        // 字符串字段
        MYSQL_ADD_FIELD("attr", "s", attr);                     // varchar -> "s"
        MYSQL_ADD_FIELD("unit", "s", unit);                     // varchar -> "s"

        // 数值字段
        MYSQL_ADD_FIELD("warehouse", "s", warehouse);           // int -> "i"
        MYSQL_ADD_FIELD("batch", "s", batch);                   // varchar -> "s"
        MYSQL_ADD_FIELD("mfd", "s", mfd);                       // int -> "i"

        // 金额相关字段
        MYSQL_ADD_FIELD("price", "d", price);                   // decimal -> "d"
        MYSQL_ADD_FIELD("nums", "d", nums);                     // decimal -> "d"
        MYSQL_ADD_FIELD("serial", "s", serial);                 // text -> "s"
        MYSQL_ADD_FIELD("discount", "d", discount);             // decimal -> "d"
        MYSQL_ADD_FIELD("dsc", "d", dsc);                       // decimal -> "d"
        MYSQL_ADD_FIELD("total", "d", total);                   // decimal -> "d"
        MYSQL_ADD_FIELD("tax", "d", tax);                       // decimal -> "d"
        MYSQL_ADD_FIELD("tat", "d", tat);                       // decimal -> "d"
        MYSQL_ADD_FIELD("tpt", "d", tpt);                       // decimal -> "d"
        MYSQL_ADD_FIELD("data", "s", this->data);               // varchar -> "s"
        MYSQL_ADD_FIELD("retreat", "d", retreat);               // decimal -> "d"
    }
};

typedef std::shared_ptr<SellInfoDO> PtrSellInfoDO;


class SellInfoViewDO : public SellInfoDO {
    // 商品名称
    MYSQL_SYNTHESIZE(string, goodsName, GoodsName);
    // 商品编号
    MYSQL_SYNTHESIZE(string, goodsNumber, GoodsNumber);
    // 商品规格
    MYSQL_SYNTHESIZE(string, goodsSpec, GoodsSpec);
};

typedef std::shared_ptr<SellInfoViewDO> PtrSellInfoViewDO;