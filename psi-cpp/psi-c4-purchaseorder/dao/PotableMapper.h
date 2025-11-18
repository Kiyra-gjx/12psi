#pragma once
#ifndef _POTABLE_MAPPER_
#define _POTABLE_MAPPER_

#include "Mapper.h"
#include "../domain/do/PotaleDO.h"

//²É¹ºµ¥±í×Ö¶ÎÓ³Éä
class PotableMapper : public Mapper<PotableDO>
{
public:
	PotableDO mapper(ResultSet* resultSet) const override
	{
		PotableDO data;
		data.setFrame(resultSet->getString(1));
		data.setNumber(resultSet->getString(2));
		data.setSupplier(resultSet->getString(3));
		data.setUser(resultSet->getString(4));
		data.setTime(resultSet->getString(5));
		data.setTotal(resultSet->getDouble(6));
		data.setActual(resultSet->getDouble(7));
		data.setMoney(resultSet->getDouble(8));
		data.setCost(resultSet->getDouble(9));
		data.setPeople(resultSet->getString(10));
		data.setExamine(resultSet->getInt(11));
		data.setNucleus(resultSet->getInt(12));
		data.setCse(resultSet->getInt(13));
		data.setInvoice(resultSet->getInt(14));
		data.setCheck(resultSet->getInt(15));
		data.setData(resultSet->getString(16));
		return data;
	}
};

#endif