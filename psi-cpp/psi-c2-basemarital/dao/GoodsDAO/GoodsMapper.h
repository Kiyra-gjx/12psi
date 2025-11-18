#ifndef GOODSMAPPER_H
#define GOODSMAPPER_H
#include "Mapper.h"
#include "../../domain/do/GoodsDO.h"
#include "memory"
class GoodsMapper : public Mapper<GoodsDO>
{
public:
	GoodsDO mapper(ResultSet* resultSet) const override
	{
		GoodsDO data;

		data.setName(resultSet->getString("name"));
		data.setNumber(resultSet->getString("number"));
		data.setSpec(resultSet->getString("spec"));
		data.setCategory(resultSet->getString("category"));
		data.setBrand(resultSet->getString("brand"));
		data.setUnit(resultSet->getString("unit"));
		data.setCode(resultSet->getString("code"));
		data.setType(resultSet->getDouble("type"));
		data.setData(resultSet->getString("data"));

		return data;
	}
};

/**
 * 示例表字段匹配映射-创建智能指针对象
 */
class PtrGoodsMapper : public Mapper<PtrGoodsDO>
{
public:
	PtrGoodsDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<GoodsDO>();

		data->setName(resultSet->getString("name"));
		data->setNumber(resultSet->getString("number"));
		data->setSpec(resultSet->getString("spec"));
		data->setCategory(resultSet->getString("category"));
		data->setBrand(resultSet->getString("brand"));
		data->setUnit(resultSet->getString("unit"));
		data->setCode(resultSet->getString("code"));
		data->setType(resultSet->getDouble("type"));
		data->setData(resultSet->getString("data"));

		return data;
	}
};
#endif // !GOODSMAPPER_HUSERMAPPER_H_