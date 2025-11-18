#ifndef _PURCHASEDETAILVIEWDO_H_
#define _PURCHASEDETAILVIEWDO_H_

#include "DoInclude.h" 

// 采购订单详情视图DO
// 包含了 bor_info 表和 goods 表的字段，用于联表查询结果的映射
class PurchaseDetailViewDO : public BaseDO {
public:

    // 来自 goods 表的字段
    MYSQL_SYNTHESIZE(string, goodsName, GoodsName);  // 商品名称
    MYSQL_SYNTHESIZE(string, goodsNo, GoodsNo);      // 商品编号
    MYSQL_SYNTHESIZE(string, specModel, SpecModel);  // 规格型号
    // 来自 bor_info 表的字段
    MYSQL_SYNTHESIZE(string, attr, Attr);            // 辅助属性
    MYSQL_SYNTHESIZE(string, unit, Unit);            // 单位
    MYSQL_SYNTHESIZE(string, warehouse, Warehouse);  // 仓库
    MYSQL_SYNTHESIZE(double, price, Price);          // 单价
    MYSQL_SYNTHESIZE(double, nums, Nums);            // 数量
    MYSQL_SYNTHESIZE(double, total, Total);          // 金额
    MYSQL_SYNTHESIZE(string, remark, Remark);        // 备注信息 
    MYSQL_SYNTHESIZE(double, handle, Handle);        // 入库数量

public:
    PurchaseDetailViewDO() : BaseDO("detail_view") {

        // 普通字段（字段名，类型标识，成员变量）
        MYSQL_ADD_FIELD("goodsName", "s", goodsName);
        MYSQL_ADD_FIELD("goodsNo", "s", goodsNo);
        MYSQL_ADD_FIELD("specModel", "s", specModel);
        MYSQL_ADD_FIELD("attr", "s", attr);
        MYSQL_ADD_FIELD("unit", "s", unit);
        MYSQL_ADD_FIELD("warehouse", "s", warehouse);
        MYSQL_ADD_FIELD("price", "d", price);
        MYSQL_ADD_FIELD("total", "d", total);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("handle", "d", handle);
    }
};

typedef shared_ptr<PurchaseDetailViewDO> PtrPurchaseDetailViewDO;

#endif // _PURCHASEDETAILVIEWDO_H_