#ifndef _InoutCategory_MAPPER_
#define _InoutCategory_MAPPER_

#include "Mapper.h"
#include "../../domain/do/inout-category/InoutCategoryDO.h"

/**
 * 简化字段映射 (1-2列) 
 * 用于: selectNames
 * SQL 必须: SELECT id, name  (并且顺序一致)
 */
class InoutCategorySimpleMapper : public Mapper<InoutCategoryDO>
{
public:
    InoutCategoryDO mapper(ResultSet* resultSet) const override
    {
        InoutCategoryDO data;

        // 1. id
        data.setId(resultSet->getString(1));
        // 2. name
        data.setName(resultSet->getString(2));

        // (type, sort, data 字段将保持默认值 nullptr)

        return data;
    }
};

/**
 * 收支类别 (iet) 表字段匹配映射
 * (返回 InoutCategoryDO 对象)
 * [!] 使用此 Mapper 的 SQL 查询必须按顺序 SELECT:
 * 1. id, 2. name, 3. type, 4. sort
 */
class InoutCategoryMapper : public Mapper<InoutCategoryDO>
{
public:
    InoutCategoryDO mapper(ResultSet* resultSet) const override
    {
        InoutCategoryDO data;

        // 1. id (varchar, NOT NULL)
        data.setId(resultSet->getString(1));

        // 2. name (varchar, NOT NULL)
        data.setName(resultSet->getString(2));

        // 3. type (tinyint, NOT NULL) - DO 中映射为 int
        data.setType(resultSet->getInt(3));

        // 4. sort (int, NOT NULL)
        data.setSort(resultSet->getInt(4));

        return data;
    }
};


/**
 * 收支类别 (iet) 表字段匹配映射
 * (返回 PtrInoutCategoryDO 智能指针对象)
 * [!] 使用此 Mapper 的 SQL 查询必须按顺序 SELECT:
 * 1. id, 2. name, 3. type, 4. sort, 5. data
 */
class PtrInoutCategoryMapper : public Mapper<PtrInoutCategoryDO>
{
public:
    PtrInoutCategoryDO mapper(ResultSet* resultSet) const override
    {
        // [!] 模仿 PtrSampleMapper，使用 make_shared
        auto data = std::make_shared<InoutCategoryDO>();

        // 1. id (varchar, NOT NULL)
        data->setId(resultSet->getString(1));

        // 2. name (varchar, NOT NULL)
        data->setName(resultSet->getString(2));

        // 3. type (tinyint, NOT NULL)
        data->setType(resultSet->getInt(3));

        // 4. sort (int, NOT NULL)
        data->setSort(resultSet->getInt(4));

        // 5. data (varchar, NULLABLE)
        if (!resultSet->isNull(5))
        {
            // 数据库中有值，才调用 setData
            data->setData(resultSet->getString(5));
        }

        return data;
    }
};

#endif // !_INOUTCATEGORY_MAPPER_