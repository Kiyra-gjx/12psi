#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _EXREPORTSIM_MAPPER_
#define _EXREPORTSIM_MAPPER_

#include "Mapper.h"
#include "../domain/do/BuyDO.h"

// BuyDO 映射器（值对象版本）
class ExReportSimMapper : public Mapper<BuyDO>
{
public:
    BuyDO mapper(ResultSet* resultSet) const override
    {
        BuyDO data;
        // 字段映射：与SQL查询列顺序严格对齐
        data.setId(resultSet->getString(1));          // id
        data.setSource(resultSet->getString(2));      // source
        data.setFrame(resultSet->getString(3));       // frame
        data.setSupplier(resultSet->getString(4));    // supplier
        data.setTime(resultSet->getString(5));        // time
        data.setNumber(resultSet->getString(6));      // number
        data.setTotal(resultSet->getDouble(7));       // total (decimal→double)
        data.setActual(resultSet->getDouble(8));      // actual (decimal→double)
        data.setMoney(resultSet->getDouble(9));       // money (decimal→double)
        data.setCost(resultSet->getDouble(10));       // cost (decimal→double)
        data.setAccount(resultSet->getString(11));    // account
        data.setPeople(resultSet->getString(12));     // people
        data.setLogistics(resultSet->getString(13));  // logistics
        data.setFile(resultSet->getString(14));       // file
        data.setData(resultSet->getString(15));       // data
        data.setMore(resultSet->getString(16));       // more
        data.setExamine(resultSet->getInt(17));       // examine (tinyint→int)
        data.setNucleus(resultSet->getInt(18));       // nucleus (tinyint→int)
        data.setCse(resultSet->getInt(19));           // cse (tinyint→int)
        data.setInvoice(resultSet->getInt(20));       // invoice (tinyint→int)
        data.setCheck(resultSet->getInt(21));         // check (tinyint→int)
        data.setUser(resultSet->getString(22));       // user

        return data;
    }
};

// BuyDO 映射器（智能指针版本）
class PtrExReportSimMapper : public Mapper<PtrBuyDO>
{
public:
    PtrBuyDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<BuyDO>();
        // 字段映射：与SQL查询列顺序严格对齐
        data->setId(resultSet->getString(1));          // id
        data->setSource(resultSet->getString(2));      // source
        data->setFrame(resultSet->getString(3));       // frame
        data->setSupplier(resultSet->getString(4));    // supplier
        data->setTime(resultSet->getString(5));        // time
        data->setNumber(resultSet->getString(6));      // number
        data->setTotal(resultSet->getDouble(7));       // total (decimal→double)
        data->setActual(resultSet->getDouble(8));      // actual (decimal→double)
        data->setMoney(resultSet->getDouble(9));       // money (decimal→double)
        data->setCost(resultSet->getDouble(10));       // cost (decimal→double)
        data->setAccount(resultSet->getString(11));    // account
        data->setPeople(resultSet->getString(12));     // people
        data->setLogistics(resultSet->getString(13));  // logistics
        data->setFile(resultSet->getString(14));       // file
        data->setData(resultSet->getString(15));       // data
        data->setMore(resultSet->getString(16));       // more
        data->setExamine(resultSet->getInt(17));       // examine (tinyint→int)
        data->setNucleus(resultSet->getInt(18));       // nucleus (tinyint→int)
        data->setCse(resultSet->getInt(19));           // cse (tinyint→int)
        data->setInvoice(resultSet->getInt(20));       // invoice (tinyint→int)
        data->setCheck(resultSet->getInt(21));         // check (tinyint→int)
        data->setUser(resultSet->getString(22));       // user

        return data;
    }
};

#endif // !_EXREPORTSIM_MAPPER_