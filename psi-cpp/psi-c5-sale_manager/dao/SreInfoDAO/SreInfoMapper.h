#pragma once
#include "domain/do/SreInfoDO.h"
#include "Mapper.h"

//将单条数据库数据转化为SreInfoViewDO
class SreInfoMapper : public Mapper<SreInfoViewDO> {
public:
	SreInfoViewDO mapper(ResultSet* res) const override{
		SreInfoViewDO data;
		data.setGoodsName(res->getString("goods_name"));
		data.setGoodsNumber(res->getString("goods_number"));
		data.setGoodsSpec(res->getString("goods_spec"));
		data.setAttr(res->getString("attr"));
		data.setUnit(res->getString("unit"));
		data.setWarehouse(res->getString("warehouse"));
		data.setBatch(res->getString("batch"));
		data.setMfd(res->getString("mfd"));
		data.setPrice(res->getDouble("price"));
		data.setNums(res->getDouble("nums"));
		data.setDiscount(res->getDouble("discount"));
		data.setDsc(res->getDouble("dsc"));
		data.setTotal(res->getDouble("total"));
		data.setData(res->getString("data"));
		return data;
	}
};