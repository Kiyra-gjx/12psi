#pragma once

#ifndef _SELL_INFO_SERVICE_H_
#define _SELL_INFO_SERVICE_H_

#include "stdafx.h"
#include "domain/do/SellInfoDO.h"
class SellInfoService
{
public:
    // 这里预留典型的增删改查接口，后续可接入对应DAO
    bool create(const PtrSellInfoDO& /*infoDO*/);
    bool update(const PtrSellInfoDO& /*infoDO*/);
    bool removeById(const std::string& /*id*/);
    PtrSellInfoDO queryById(const std::string& /*id*/);
    PtrSellInfoDO queryByPid(const std::string& pid);

};

#endif // _SELL_INFO_SERVICE_H_
