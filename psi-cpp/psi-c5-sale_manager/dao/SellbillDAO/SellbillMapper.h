
#ifndef _SELLBILLMAPPER_H_
#define _SELLBILLMAPPER_H_

#include "Mapper.h"
#include "domain/do/SellbillDO.h"

class SellbillMapper : public Mapper<PtrSellbillDO>
{
public:
    PtrSellbillDO mapper(ResultSet* resultSet) const override
    {
        PtrSellbillDO bill = std::make_shared<SellbillDO>();
        bill->setId(resultSet->getString("id"));
        bill->setPid(resultSet->getString("pid"));
        bill->setType(resultSet->getString("type"));
        bill->setSource(resultSet->getString("source"));
        bill->setTime(resultSet->getString("time"));
        bill->setMoney(resultSet->getDouble("money"));
        return bill;
    }
};

#endif
