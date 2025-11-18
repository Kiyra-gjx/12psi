#pragma once
#ifndef _SRE_BILL_MAPPER_H_
#define _SRE_BILL_MAPPER_H_

#include "Mapper.h"
#include "domain/do/SrebillDO.h"

class SrebillMapper : public Mapper<PtSrebillDO> {
public:
	PtSrebillDO mapper(ResultSet* resultSet) const override {
		auto bill = std::make_shared<SrebillDO>();
		// map columns: id, pid, type, source, time, money
		bill->setId(resultSet->getString(1));
		bill->setPid(resultSet->getString(2));
		bill->setType(resultSet->getString(3));
		bill->setSource(resultSet->getString(4));
		bill->setTime(resultSet->getString(5));
		bill->setMoney(resultSet->getDouble(6));
		return bill;
	}
};

#endif // _SRE_BILL_MAPPER_H_
