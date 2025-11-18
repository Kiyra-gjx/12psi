#ifndef _SUPPLIER_MAPPER_
#define _SUPPLIER_MAPPER_
#include "Mapper.h"
#include "../../domain/do/SupplierDO.h"

class SupplierMapper : public Mapper<SupplierDO>
{
public:
	SupplierDO mapper(ResultSet* resultSet) const override
	{
		SupplierDO data;
		data.setId(resultSet->getString(1));
		data.setName(resultSet->getString(2));
		data.setPy(resultSet->getString(3));
		data.setNumber(resultSet->getString(4));
		data.setFrame(resultSet->getString(5));
		data.setUser(resultSet->getString(6));
		data.setCategory(resultSet->getString(7));
		data.setRate(resultSet->getDouble(8));
		data.setBank(resultSet->getString(9));
		data.setAccount(resultSet->getString(10));
		data.setTax(resultSet->getString(11));
		data.setData(resultSet->getString(12));
		data.setContacts(resultSet->getString(13));
		data.setBalance(resultSet->getDouble(14));
		data.setMore(resultSet->getString(15));
		return data;
	}
};

class PtrSupplierMapper : public Mapper<PtrSupplierDO>
{
public:
	PtrSupplierDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SupplierDO>();
		data->setId(resultSet->getString(1));
		data->setName(resultSet->getString(2));
		data->setPy(resultSet->getString(3));
		data->setNumber(resultSet->getString(4));
		data->setFrame(resultSet->getString(5));
		data->setUser(resultSet->getString(6));
		data->setCategory(resultSet->getString(7));
		data->setRate(resultSet->getDouble(8));
		data->setBank(resultSet->getString(9));
		data->setAccount(resultSet->getString(10));
		data->setTax(resultSet->getString(11));
		data->setData(resultSet->getString(12));
		data->setContacts(resultSet->getString(13));
		data->setBalance(resultSet->getDouble(14));
		data->setMore(resultSet->getString(15));
		return data;
	}
};

#endif // !_SUPPLIER_MAPPER_

