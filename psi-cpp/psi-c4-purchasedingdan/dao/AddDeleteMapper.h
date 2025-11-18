#pragma once
#ifndef _ADDDELETEMAPPER_H_
#define _ADDDELETEMAPPER_H_
#include "Mapper.h"
#include "domain/do/PurchaseDingDanDO.h"


class AddDeleteMapper : public Mapper<PtrPurchaseDingDanDO> {
public:
    PtrPurchaseDingDanDO mapper(ResultSet* resultSet) const override {
        PtrPurchaseDingDanDO purchaseDingDanDO = std::make_shared<PurchaseDingDanDO>;

        purchaseDingDanDO->setId(resultSet.getString("id"));
        purchaseDingDanDO->setSource(resultSet->getString("source"));
        purchaseDingDanDO->setFrame(resultSet->getString("frame"));
        purchaseDingDanDO->setSupplier(resultSet.getString("supplier"));
        purchaseDingDanDO->setTime(resultSet.getString("time"));
        purchaseDingDanDO->setNumber(resultSet.getString("number"));
        purchaseDingDanDO->setTotal(resultSet.getDouble("total"));
        purchaseDingDanDO->setActual(resultSet->getDouble("Actual"));
        purchaseDingDanDO->setPeople(resultSet.getString("people"));
        purchaseDingDanDO->setArrival(resultSet.getString("arrival"));
        purchaseDingDanDO->setLogistics(resultSet.getString("logistics"));
        purchaseDingDanDO->setFile(resultSet.getString("file"));
        purchaseDingDanDO->setData(resultSet.getString("data"));
        purchaseDingDanDO->setMore(resultSet->getString("more"));
        purchaseDingDanDO->setExamine(resultSet->getInt("examine"));
        purchaseDingDanDO->setState(resultSet.getInt("state"));
        purchaseDingDanDO->setUser(resultSet.getString("user"));

        return purchaseDingDanDO;
    }

};

#endif // !_ADDDELETEMAPPER_H_

