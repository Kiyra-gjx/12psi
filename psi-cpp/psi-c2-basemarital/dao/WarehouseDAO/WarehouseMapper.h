#pragma 

#ifndef _WAREHOUSE_MAPPER_
#define _WAREHOUSE_MAPPER_

#include "Mapper.h"
#include "domain/do/WarehouseDO.h"

/*
* ²Ö¿â±í×Ö¶ÎÆ¥ÅäÓ³Éä
 */
class WarehouseMapper : public Mapper<WarehouseDO>
{
public:
	WarehouseDO mapper(ResultSet* resultSet) const override
	{
		WarehouseDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setNumber(resultSet->getString(3));
		data.setFrame(resultSet->getString(4));
		data.setContacts(resultSet->getString(5));
		data.setTel(resultSet->getString(6));
		data.setAdd(resultSet->getString(7));
		data.setData(resultSet->getString(8));

		return data;
	}
};

/*
* ²Ö¿â±í×Ö¶ÎÆ¥ÅäÓ³Éä-´´½¨ÖÇÄÜÖ¸Õë¶ÔÏó 
 */
class PtrWarehouseMapper : public Mapper<PtrWarehouseDO>
{
public:
	PtrWarehouseDO mapper(ResultSet* resultSet) const override
	{
		auto data = make_shared<WarehouseDO>();
		data->setId(resultSet->getString(1));
		data->setName(resultSet->getString(2));
		data->setNumber(resultSet->getString(3));
		data->setFrame(resultSet->getString(4));
		data->setContacts(resultSet->getString(5));
		data->setTel(resultSet->getString(6));
		data->setAdd(resultSet->getString(7));
		data->setData(resultSet->getString(8));

		return data;
	}
};


#endif