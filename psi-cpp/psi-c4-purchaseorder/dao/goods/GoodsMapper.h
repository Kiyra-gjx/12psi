#pragma once
#ifndef _GOODSMAPPER_H_
#define _GOODSMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/OrderDO.h"

class GoodsMapper : public Mapper<PtrGoodsDO>
{
public:
	PtrGoodsDO mapper(ResultSet* rs) const override {
		auto goods = std::make_shared<GoodsDO>();
		goods->setId(rs->getString("id"));
		goods->setName(rs->getString("name"));
		goods->setPy(rs->getString("py"));
		goods->setNumber(rs->getString("number"));
		goods->setSpec(rs->getString("spec"));
		goods->setCategory(rs->getString("category"));
		goods->setBrand(rs->getString("brand"));
		goods->setUnit(rs->getString("unit"));
		goods->setBuy(rs->getDouble("buy"));
		goods->setSell(rs->getDouble("sell"));
		goods->setCode(rs->getString("code"));
		goods->setLocation(rs->getString("location"));
		goods->setStock(rs->getDouble("stock"));
		goods->setType(rs->getInt("type"));
		goods->setData(rs->getString("data"));
		goods->setImgs(rs->getString("imgs"));
		goods->setDetails(rs->getString("details"));
		goods->setUnits(rs->getString("units"));
		goods->setStrategy(rs->getString("strategy"));
		goods->setSerial(rs->getInt("serial"));
		goods->setBatch(rs->getInt("batch"));
		goods->setValidity(rs->getInt("validity"));
		goods->setProtect(rs->getInt("protect"));
		goods->setThreshold(rs->getInt("threshold"));
		goods->setMore(rs->getString("more"));
		return goods;
	}
};

#endif // !_GOODSMAPPER_H_