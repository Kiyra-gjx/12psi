#pragma once
#ifndef _BUYMAPPER_H_
#define _BUYMAPPER_H_

#include "Mapper.h"
#include "domain/do/OrderDO.h"


class BuyMapper : public Mapper<PtrBuyDO> {
public:
	PtrBuyDO mapper(ResultSet* resultSet) const override
	{
		
		PtrBuyDO orderDO = std::make_shared<BuyDO>();
		orderDO->setId(resultSet->getString("id"));
		orderDO->setSource(resultSet->getString("source"));
		orderDO->setFrame(resultSet->getString("frame"));
		orderDO->setSupplier(resultSet->getString("supplier"));
		orderDO->setTime(resultSet->getString("time"));
		orderDO->setNumber(resultSet->getString("number"));
		orderDO->setTotal(resultSet->getDouble("total"));
		orderDO->setActual(resultSet->getDouble("actual"));
		orderDO->setMoney(resultSet->getDouble("money"));
		orderDO->setCost(resultSet->getDouble("cost"));
		orderDO->setAccount(resultSet->getString("account"));
		orderDO->setPeople(resultSet->getString("people"));
		orderDO->setLogistics(resultSet->getString("logistics"));
		orderDO->setFile(resultSet->getString("file"));
		orderDO->setData(resultSet->getString("data"));
		orderDO->setMore(resultSet->getString("more"));
		orderDO->setExamine(resultSet->getInt("examine"));
		orderDO->setNucleus(resultSet->getInt("nucleus"));
		orderDO->setCse(resultSet->getInt("cse"));
		orderDO->setInvoice(resultSet->getInt("invoice"));
		orderDO->setCheck(resultSet->getInt("check"));
		orderDO->setUser(resultSet->getString("user"));


		return orderDO;

	}
};






#endif // !_DINGDANMAPPER_H_