#pragma once

#ifndef _SELL_BILL_SERVICE_H_
#define _SELL_BILL_SERVICE_H_

#include "stdafx.h"
#include "domain/do/SellbillDo.h" // 使用 PtrSellbillDO

class SellbillService
{
public:
    // 预留：单据费用/结算等后续逻辑
    bool create(const PtrSellbillDO& /*billDO*/);
    bool update(const PtrSellbillDO& /*billDO*/);
    bool removeById(const std::string& /*id*/);
    PtrSellbillDO queryById(const std::string& /*id*/);
};

#endif // _SELL_BILL_SERVICE_H_
