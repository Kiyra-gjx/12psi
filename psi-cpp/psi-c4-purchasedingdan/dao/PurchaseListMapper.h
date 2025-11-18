#ifndef _PURCHASELIST_MAPPER_
#define _PURCHASELIST_MAPPER_

#include "Mapper.h"
#include "../domain/do/PurchaseDingDanDO.h"

/**
 * 采购订单DO与数据库字段的映射器
 */
class PurchaseListMapper : public Mapper<PurchaseDingDanDO> {
public:
    PurchaseDingDanDO mapper(ResultSet* resultSet) const override {
        PurchaseDingDanDO data;
        // 主键id
        data.setId(resultSet->getString(1));
        // 关联单据
        data.setSource(resultSet->getString(2));
        // 所属组织
        data.setFrame(resultSet->getString(3));
        // 供应商
        data.setSupplier(resultSet->getString(4));
        // 单据时间
        data.setTime(resultSet->getString(5));
        // 单据编号
        data.setNumber(resultSet->getString(6));
        // 单据金额
        data.setTotal(resultSet->getDouble(7));
        // 实际金额
        data.setActual(resultSet->getDouble(8));
        // people
        data.setPeople(resultSet->getString(9));
        // 到货时间
        data.setArrival(resultSet->getString(10));
        // 物流信息
        data.setLogistics(resultSet->getString(11));
        // 单据附件
        data.setFile(resultSet->getString(12));
        // data
        data.setData(resultSet->getString(13));
        // 扩展信息
        data.setMore(resultSet->getString(14));
        // examine
        data.setExamine(resultSet->getInt(15));
        // state
        data.setState(resultSet->getInt(16));
        // user
        data.setUser(resultSet->getString(17));
        return data;
    }
};

#endif // !_PURCHASELIST_MAPPER_