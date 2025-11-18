#pragma once

#ifndef _REVIEWORDER_MAPPER_
#define _REVIEWORDER_MAPPER_

#include "Mapper.h"
#include "../domain/do/getreturnlistDO.h"
#include "../domain/do/BreInfoDO.h"
#include "domain/do/RoomDO.h"
#include "domain/do/AccountInfoDO.h"
#include "domain/do/GoodsDO.h"
#include"domain/do/RoomInfoDO.h"
#include"domain/do/WarehouseDO.h"
#include"domain/do/SupplierDO.h"
#include"domain/do/AccountDO.h"

/**
 * 采购退货单
 * 查看整个单据的信息
 */
class ReviewBreMapper : public Mapper<BreDO>
{
public:
    BreDO mapper(ResultSet* resultSet) const override
    {
        BreDO data;

        data.setId(resultSet->getString("id"));
        data.setSource(resultSet->getString("source"));
        data.setMoney(resultSet->getDouble("money"));
        data.setAccount(resultSet->getString("account"));
        data.setExamine(resultSet->getInt("examine"));
        data.setUser(resultSet->getString("user"));
        data.setNumber(resultSet->getString("number"));
        return data;
    }
};

/**
 * 审核订单表字段匹配映射-创建智能指针对象
 */
class PtrReviewBreMapper : public Mapper<PtrBreDO>
{
public:
    PtrBreDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<BreDO>();


        data->setId(resultSet->getString("id"));
        data->setSource(resultSet->getString("source"));
        data->setMoney(resultSet->getDouble("money"));
        data->setAccount(resultSet->getString("account"));
        data->setExamine(resultSet->getInt("examine"));
        data->setUser(resultSet->getString("user"));
        data->setNumber(resultSet->getString("number"));
        return data;
    }
};

/**
 * 采购退货单详情
 * 查看单据中每个商品的详细信息
 */
class ReviewBreInfoMapper : public Mapper<BreInfoDO>
{
public:
    BreInfoDO mapper(ResultSet* resultSet) const override
    {
        BreInfoDO data;

        data.setId(resultSet->getString("id"));
        data.setPid(resultSet->getString("pid"));
        data.setGoods(resultSet->getString("goods"));
        data.setWarehouse(resultSet->getString("warehouse"));
        data.setNums(resultSet->getDouble("nums"));
        data.setPrice(resultSet->getDouble("price"));
        return data;
    }
};

/**
 * 采购退货单详情智能指针映射
 */
class PtrReviewBreInfoMapper : public Mapper<PtrBreInfoDO>
{
public:
    PtrBreInfoDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<BreInfoDO>();

        data->setId(resultSet->getString("id"));
        data->setPid(resultSet->getString("pid"));
        data->setGoods(resultSet->getString("goods"));
        data->setWarehouse(resultSet->getString("warehouse"));
        data->setNums(resultSet->getDouble("nums"));
        return data;
    }
};

/**
 * 仓库信息
 */
class ReviewRoomMapper : public Mapper<RoomDO>
{
public:
    RoomDO mapper(ResultSet* resultSet) const override
    {
        RoomDO data;

        data.setId(resultSet->getString("id"));
        data.setGoods(resultSet->getString("goods"));
        data.setWarehouse(resultSet->getString("warehouse"));
        data.setNums(resultSet->getDouble("nums"));

        return data;
    }
};

/**
 * 仓库信息智能指针映射
 */
class PtrReviewRoomMapper : public Mapper<PtrRoomDO>
{
public:
    PtrRoomDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<RoomDO>();

        data->setId(resultSet->getString("id"));
        data->setGoods(resultSet->getString("goods"));
        data->setWarehouse(resultSet->getString("warehouse"));
        data->setNums(resultSet->getDouble("nums"));
        return data;
    }
};

/**
 * 仓库详情
 */
class ReviewRoomInfoMapper : public Mapper<RoomInfoDO>
{
public:
    RoomInfoDO mapper(ResultSet* resultSet) const override
    {
        RoomInfoDO data;

        data.setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 仓库详情智能指针映射
 */
class PtrReviewRoomInfoMapper : public Mapper<PtrRoomInfoDO>
{
public:
    PtrRoomInfoDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<RoomInfoDO>();

        data->setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 资金详情
 */
class ReviewAccountInfoMapper : public Mapper<AccountInfoDO>
{
public:
    AccountInfoDO mapper(ResultSet* resultSet) const override
    {
        AccountInfoDO data;


        data.setId(resultSet->getString("id"));

        return data;
    }
};

/**
 * 资金详情智能指针映射
 */
class PtrReviewAccountInfoMapper : public Mapper<PtrAccountInfoDO>
{
public:
    PtrAccountInfoDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<AccountInfoDO>();


        data->setId(resultSet->getString("id"));

        return data;
    }
};


/**
 * 商品详情
 */
class ImportGoodsMapper : public Mapper<GoodsDO>
{
public:
    GoodsDO mapper(ResultSet* resultSet) const override
    {
        GoodsDO data;


        data.setId(resultSet->getString("id"));
        data.setName(resultSet->getString("name"));
        data.setPy(resultSet->getString("py"));
        data.setUnit(resultSet->getString("unit"));

        return data;
    }
};

/**
 * 商品详情智能指针映射
 */
class PtrImportGoodsMapper : public Mapper<PtrGoodsDO>
{
public:
    PtrGoodsDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<GoodsDO>();


        data->setId(resultSet->getString("id"));
        data->setName(resultSet->getString("name"));
        data->setPy(resultSet->getString("py"));
        data->setUnit(resultSet->getString("unit"));

        return data;
    }
};


/**
 * 仓库
 */
class ImportWarehouseMapper : public Mapper<WarehouseDO>
{
public:
    WarehouseDO mapper(ResultSet* resultSet) const override
    {
        WarehouseDO data;

        data.setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 仓库智能指针映射
 */
class PtrImportWarehouseMapper : public Mapper<PtrWarehouseDO>
{
public:
    PtrWarehouseDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<WarehouseDO>();

        data->setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 供应商
 */
class ImportSupplierMapper : public Mapper<SupplierDO>
{
public:
    SupplierDO mapper(ResultSet* resultSet) const override
    {
        SupplierDO data;

        data.setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 供应商智能指针映射
 */
class PtrImportSupplierMapper : public Mapper<PtrSupplierDO>
{
public:
    PtrSupplierDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<SupplierDO>();

        data->setId(resultSet->getString("id"));
        return data;
    }
};


/**
 * 供应商
 */
class ImportAccountMapper : public Mapper<AccountDO>
{
public:
    AccountDO mapper(ResultSet* resultSet) const override
    {
        AccountDO data;

        data.setId(resultSet->getString("id"));
        return data;
    }
};

/**
 * 供应商智能指针映射
 */
class PtrImportAccountMapper : public Mapper<PtrAccountDO>
{
public:
    PtrAccountDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<AccountDO>();

        data->setId(resultSet->getString("id"));
        return data;
    }
};


#endif // !_REVIEWORDER_MAPPER_