#pragma once
#ifndef _BORINFOMAPPER_H_
#define _BORINFOMAPPER_H_

#include "Mapper.h"
#include "../domain/do/DingdanDO.h"

/**
 * BorInfo
 */
class BorInfoMapper : public Mapper<PtrBorInfoDO>
{
public:
	PtrBorInfoDO mapper(ResultSet* rs) const override {
		auto borInfo = std::make_shared<BorInfoDO>();
		borInfo->setId(rs->getString("id"));
		borInfo->setPid(rs->getString("pid"));
		borInfo->setGoods(rs->getString("goods"));
		borInfo->setAttr(rs->getString("attr"));
		borInfo->setUnit(rs->getString("unit"));
		borInfo->setWarehouse(rs->getString("warehouse"));
		borInfo->setPrice(rs->getDouble("price"));
		borInfo->setNums(rs->getDouble("nums"));
		borInfo->setDiscount(rs->getDouble("discount"));
		borInfo->setDsc(rs->getDouble("dsc"));
		borInfo->setTotal(rs->getDouble("total"));
		borInfo->setTax(rs->getDouble("tax"));
		borInfo->setTat(rs->getDouble("tat"));
		borInfo->setTpt(rs->getDouble("tpt"));
		borInfo->setData(rs->getString("data"));
		borInfo->setHandle(rs->getDouble("handle"));
		return borInfo;
	}
};

#endif // !_BORINFOMAPPER_H_