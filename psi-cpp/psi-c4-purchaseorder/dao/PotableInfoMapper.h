#pragma once
#ifndef _POTABLE_MAPPER_
#define _POTABLE_MAPPER_

#include "Mapper.h"
#include "../domain/do/PotableInfoDO.h"

//²É¹ºµ¥±í×Ö¶ÎÓ³Éä
class PotableInfoMapper : public Mapper<PotableInfoDO>
{
public:
	PotableInfoDO mapper(ResultSet* resultSet) const override
	{
		PotableInfoDO data;
		data.setAttr(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setUnit(resultSet->getString(3));
		data.setPrice(resultSet->getDouble(4));
		data.setWarehouse(resultSet->getString(5));
		data.setNums(resultSet->getDouble(6));
		data.setDiscount(resultSet->getDouble(7));
		data.setDsc(resultSet->getDouble(8));
		data.setTotal(resultSet->getDouble(9));
		data.setData(resultSet->getString(10));
		data.setTat(resultSet->getDouble(11));
		data.setTpt(resultSet->getDouble(12));
		data.setTax(resultSet->getDouble(13));
		return data;
	}
};

#endif
