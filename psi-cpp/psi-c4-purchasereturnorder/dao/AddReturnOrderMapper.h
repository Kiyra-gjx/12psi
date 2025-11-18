#pragma once
#ifndef _BREDOMAPPER_H_
#define _BREDOMAPPER_H_

#include "Mapper.h"
#include "domain/do/getreturnlistD0.h"

class BreMapper : public Mapper<PtrBreDO> {
public:
    PtrBreDO mapper(ResultSet* resultSet) const override {
        PtrBreDO breDO = std::make_shared<BreDO>();

        // 主键ID
        breDO->setId(resultSet->getString("id"));

        // 关联单据
        breDO->setSource(resultSet->getString("source"));

        // 所属组织
        breDO->setFrame(resultSet->getString("frame"));

        // 供应商
        breDO->setSupplier(resultSet->getString("supplier"));

        // 单据时间
        breDO->setTime(resultSet->getString("time"));

        // 单据编号
        breDO->setNumber(resultSet->getString("number"));

        // 单据金额
        breDO->setTotal(resultSet->getDouble("total"));

        // 实际金额
        breDO->setActual(resultSet->getDouble("actual"));

        // 实收金额
        breDO->setMoney(resultSet->getDouble("money"));

        // 单据费用
        breDO->setCost(resultSet->getDouble("cost"));

        // 结算账户
        breDO->setAccount(resultSet->getString("account"));

        // 关联人员
        breDO->setPeople(resultSet->getString("people"));

        // 物流信息
        breDO->setLogistics(resultSet->getString("logistics"));

        // 单据附件
        breDO->setFile(resultSet->getString("file"));

        // 备注信息
        breDO->setData(resultSet->getString("data"));

        // 扩展信息
        breDO->setMore(resultSet->getString("more"));

        // 审核状态
        breDO->setExamine(resultSet->getInt("examine"));

        // 核销状态
        breDO->setNucleus(resultSet->getInt("nucleus"));

        // 费用状态
        breDO->setCse(resultSet->getInt("cse"));

        // 发票状态
        breDO->setInvoice(resultSet->getInt("invoice"));

        // 核对状态
        breDO->setCheck(resultSet->getInt("check"));

        // 制单人
        breDO->setUser(resultSet->getString("user"));

        return breDO;
    }
};

#endif // !_BREDOMAPPER_H_