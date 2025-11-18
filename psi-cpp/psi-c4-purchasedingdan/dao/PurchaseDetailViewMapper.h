#ifndef _PURCHASE_DETAIL_VIEW_MAPPER_
#define _PURCHASE_DETAIL_VIEW_MAPPER_

#include "Mapper.h"
#include "../domain/do/PurchaseDetailViewDO.h"

class PurchaseDetailViewMapper : public Mapper<PurchaseDetailViewDO> {
public:
    PurchaseDetailViewDO mapper(ResultSet* resultSet) const override {
        PurchaseDetailViewDO data;

        // 映射 goods 表字段 
        data.setGoodsName(resultSet->getString(1));  // 商品名称
        data.setGoodsNo(resultSet->getString(2));    // 商品编号 
        data.setSpecModel(resultSet->getString(3));  // 规格型号 
        // 映射 bor_info 表字段
        data.setAttr(resultSet->getString(4));       // 辅助属性 
        data.setUnit(resultSet->getString(5));       // 单位 
        data.setWarehouse(resultSet->getString(6));  // 仓库 
        data.setPrice(resultSet->getDouble(7));      // 单价 
        data.setNums(resultSet->getDouble(8));       // 数量 
        data.setTotal(resultSet->getDouble(9));      // 金额 
        data.setRemark(resultSet->getString(10));    // 备注信息 
        data.setHandle(resultSet->getDouble(11));    // 入库数量
        return data;
    }
};

#endif // !_PURCHASE_DETAIL_VIEW_MAPPER_