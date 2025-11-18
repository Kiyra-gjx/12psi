#pragma once

#ifndef _BUY_INFO_MAPPER_
#define _BUY_INFO_MAPPER_

#include "Mapper.h"

/**
 * 采购单详情表字段匹配映射
 */
// class BuyInfoMapper : public Mapper<PotableInfoDO>
// {
// public:
//     PotableInfoDO mapper(ResultSet* resultSet) const override
//     {
//         PotableInfoDO data;
//         data.setId(resultSet->getString(1));
//         data.setPid(resultSet->getString(2));
//         data.setSource(resultSet->getString(3));
//         data.setGoods(resultSet->getString(4));
//         data.setAttr(resultSet->getString(5));
//         data.setUnit(resultSet->getString(6));
//         data.setWarehouse(resultSet->getString(7));
//         data.setBatch(resultSet->getString(8));
//         data.setMfd(resultSet->getString(9));
//         data.setPrice(resultSet->getDouble(10));
//         data.setNums(resultSet->getDouble(11));
//         data.setSerial(resultSet->getString(12));
//         data.setDiscount(resultSet->getDouble(13));
//         data.setDsc(resultSet->getDouble(14));
//         data.setTotal(resultSet->getDouble(15));
//         data.setTax(resultSet->getDouble(16));
//         data.setTat(resultSet->getDouble(17));
//         data.setTpt(resultSet->getDouble(18));
//         data.setData(resultSet->getString(19));
//         data.setRetreat(resultSet->getDouble(20));
//         return data;
//     }
// };
//
// /**
//  * 采购单详情表字段匹配映射-创建智能指针对象
//  */
// class PtrBuyInfoDoMapper : public Mapper<PtrBuyInfoDo>
// {
// public:
//     PtrBuyInfoDo mapper(ResultSet* resultSet) const override
//     {
//         auto data = std::make_shared<PotableInfoDO>();
//         data->setId(resultSet->getString(1));
//         data->setPid(resultSet->getString(2));
//         data->setSource(resultSet->getString(3));
//         data->setGoods(resultSet->getString(4));
//         data->setAttr(resultSet->getString(5));
//         data->setUnit(resultSet->getString(6));
//         data->setWarehouse(resultSet->getString(7));
//         data->setBatch(resultSet->getString(8));
//         data->setMfd(resultSet->getString(9));
//         data->setPrice(resultSet->getDouble(10));
//         data->setNums(resultSet->getDouble(11));
//         data->setSerial(resultSet->getString(12));
//         data->setDiscount(resultSet->getDouble(13));
//         data->setDsc(resultSet->getDouble(14));
//         data->setTotal(resultSet->getDouble(15));
//         data->setTax(resultSet->getDouble(16));
//         data->setTat(resultSet->getDouble(17));
//         data->setTpt(resultSet->getDouble(18));
//         data->setData(resultSet->getString(19));
//         data->setRetreat(resultSet->getDouble(20));
//         return data;
//     }
// };

#endif // !_BUY_INFO_MAPPER_