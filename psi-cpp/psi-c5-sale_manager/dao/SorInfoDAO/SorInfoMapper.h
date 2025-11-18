#pragma once

#ifndef _DETAUKSAKEORDER_MAPPER_
#define _DETAUKSAKEORDER_MAPPER_

#include "Mapper.h"
#include "../../domain/do/SorInfoDO.h"


/*
	销售订单详情表匹配映射
*/

class SorInfoMapper : public Mapper<PtrSorInfoDO>
{
public:
	PtrSorInfoDO mapper(ResultSet* res)const override
	{
		PtrSorInfoDO data = std::make_shared<SorInfoDO>();
		data->setId(res->getString("id"));
		data->setPid(res->getString("pid"));
		data->setGoods(res->getString("goods"));
		data->setAttr(res->getString("attr"));
		data->setUnit(res->getString("unit"));
		data->setWarehouse(res->getString("warehouse"));
		data->setPrice(res->getDouble("price"));
		data->setNums(res->getInt("nums"));
		data->setDiscount(res->getDouble("discount"));
		data->setDsc(res->getDouble("dsc"));
		data->setTotal(res->getDouble("total"));
		data->setTax(res->getDouble("tax"));
		data->setTat(res->getDouble("tat"));
		data->setTpt(res->getDouble("tpt"));
		data->setData(res->getString("data"));
		data->setHandle(res->getDouble("handle"));
	
		return data;

	}
};

/*
	创建智能指针对象
*/

class PtrSorInfoMapper : public Mapper<PtrSorInfoDO>
{
public:
	PtrSorInfoDO mapper(ResultSet* res)const override
	{
		PtrSorInfoDO data = std::make_shared<SorInfoDO>();
		data->setId(res->getString("id"));
		data->setPid(res->getString("pid"));
		data->setAttr(res->getString("attr"));
		data->setGoods(res->getString("goods"));
		data->setUnit(res->getString("unit"));
		data->setWarehouse(res->getString("warehouse"));
		data->setPrice(res->getDouble("price"));
		data->setNums(res->getInt("nums"));
		data->setDiscount(res->getDouble("discount"));
		data->setDsc(res->getDouble("dsc"));
		data->setTotal(res->getDouble("total"));
		data->setTax(res->getDouble("tax"));
		data->setTat(res->getDouble("tat"));
		data->setTpt(res->getDouble("tpt"));
		data->setData(res->getString("data"));
		data->setHandle(res->getDouble("handle"));
		return data;
	}
};

class SorInfoByPidMapper : public Mapper<PtrSorInfoDO> {
public:
	PtrSorInfoDO mapper(ResultSet* res)const override {
		PtrSorInfoDO data = std::make_shared<SorInfoDO>();
		data->setId(res->getString("id"));
		data->setPid(res->getString("pid"));
        data->setGoods(res->getString("goods"));
		data->setAttr(res->getString("attr"));
		data->setUnit(res->getString("unit"));
		data->setWarehouse(res->getString("warehouse"));
		data->setPrice(res->getDouble("price"));
		data->setNums(res->getInt("nums"));
		data->setDiscount(res->getDouble("discount"));
		data->setDsc(res->getDouble("dsc"));
		data->setTotal(res->getDouble("total"));
		data->setData(res->getString("data"));
		return data;
	}
};

#endif // ! _DETAUKSAKEORDER_MAPPER_
