#pragma once

#ifndef FUNDSMAPPER_H_
#define FUNDSMAPPER_H_

#include "Mapper.h"
#include"../../domain/do/AccountDO.h"

class AccountMapper : public Mapper<AccountDO>
{
public:
	AccountDO mapper(ResultSet* resultSet) const override
	{
		AccountDO data;
		data.setId(resultSet->getString(1));
		data.setAccountname(resultSet->getString(2));
		data.setAccountnumber(resultSet->getString(3));
		data.setFrame(resultSet->getString(4));
		data.setTime(resultSet->getString(5));
		data.setInitial(resultSet->getDouble(6));
		data.setBalance(resultSet->getDouble(7));
		data.setData(resultSet->getString(8));
		return data;
	}
};

class PtrAccountMapper : public Mapper<PtrAccountDO>
{
public:
	PtrAccountDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<AccountDO>();
		data->setId(resultSet->getString(1));
		data->setAccountname(resultSet->getString(2));
		data->setAccountnumber(resultSet->getString(3));
		data->setFrame(resultSet->getString(4));
		data->setTime(resultSet->getString(5));
		data->setInitial(resultSet->getDouble(6));
		data->setBalance(resultSet->getDouble(7));
		data->setData(resultSet->getString(8));
		return data;
	}
};


#endif // !FUNDSMAPPER_H_
