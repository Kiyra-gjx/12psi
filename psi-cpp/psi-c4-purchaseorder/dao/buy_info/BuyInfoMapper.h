#pragma once
#ifndef _BUYINFOMAPPER_H_
#define _BUYINFOMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/OrderDO.h"


class BuyInfoMapper : public Mapper<PtrBuyInfoDO>
{
public:
	PtrBuyInfoDO mapper(ResultSet* rs) const override {
		auto borInfo = std::make_shared<BuyInfoDO>();
		borInfo->setId(rs->getString("id"));
		borInfo->setPid(rs->getString("pid"));
		borInfo->setSource(rs->getString("source"));
		borInfo->setGoods(rs->getString("goods"));
		borInfo->setAttr(rs->getString("attr"));
		borInfo->setUnit(rs->getString("unit"));
		borInfo->setWarehouse(rs->getString("warehouse"));
		borInfo->setPrice(rs->getDouble("price"));
		borInfo->setBatch(rs->getString("batch"));
		borInfo->setMfd(rs->getString("mfd"));
		borInfo->setPrice(rs->getDouble("price"));
		borInfo->setNums(rs->getDouble("nums"));
		borInfo->setSerial(rs->getString("serial"));
		borInfo->setDiscount(rs->getDouble("discount"));
		borInfo->setDsc(rs->getDouble("dsc"));
		borInfo->setTotal(rs->getDouble("total"));
		borInfo->setTax(rs->getDouble("tax"));
		borInfo->setTat(rs->getDouble("tat"));
		borInfo->setTpt(rs->getDouble("tpt"));
		borInfo->setData(rs->getString("data"));
		borInfo->setRetreat(rs->getDouble("retreat"));
		return borInfo;
	}
};

#endif // !_BORINFOMAPPER_H_