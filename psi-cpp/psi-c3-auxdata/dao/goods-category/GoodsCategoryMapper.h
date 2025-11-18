#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 */
#ifndef _GOODS_CATEGORY_MAPPER_
#define _GOODS_CATEGORY_MAPPER_


#include "Mapper.h"
#include "../../domain/do/goods-category/GoodsCategoryDO.h"
#include <iostream>


/**
 * 智能指针映射器
 */
class GoodsCategoryMapper : public Mapper<GoodsCategoryDO>
{
public:
    GoodsCategoryDO mapper(ResultSet* rs) const override
    {
        GoodsCategoryDO data;
        // 按照GoodsCategoryDO的字段顺序从结果集获取数据并设置
        data.setId(rs->getString(1));       // ID主键
        data.setPid(rs->getString(2));      // 所属类别ID
        data.setName(rs->getString(3));     // 类别名称
        data.setSort(rs->getInt(4));        // 类别排序
        data.setData(rs->getString(5));     // 备注信息
        return data;
    }
};

/**
 * 商品类别智能指针映射器
 */
class PtrGoodsCategoryMapper : public Mapper<PtrGoodsCategoryDO>
{
public:

	PtrGoodsCategoryDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<GoodsCategoryDO>();
		data->setId(resultSet->getString(1));
		data->setPid(resultSet->getString(2));
		data->setName(resultSet->getString(3));
		data->setSort(resultSet->getInt(4));
		data->setData(resultSet->getString(5));
		return data;
	}
};
class StringMapper : public Mapper<std::string> {
public:
    std::string mapper(ResultSet* rs) const override {
        return rs->getString(1); // 只映射第一列
    }
};
#endif // !_GOODS_CATEGORY_MAPPER_
