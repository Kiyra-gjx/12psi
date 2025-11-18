#pragma once
#ifndef _EXAMINE_MAPPER_H
#define _EXAMINE_MAPPER_H

#include "Mapper.h"
#include "domain/do/BuyDO.h"

/**
 * 采购单审核/未审核数据映射
 */
class ExamineMapper : public Mapper<BuyDO>
{
public:
	BuyDO mapper(ResultSet* resultSet) const override
	{
		BuyDO data;

		cout << "in ExamineMapper resultSet: ";
		cout << resultSet->getString("id") << " ";
		cout << resultSet->getString("source") << " ";
		cout << resultSet->getInt("examine") << endl;

		data.setId(resultSet->getString("id"));
		data.setSource(resultSet->getString("source"));

		data.setExamine(resultSet->getInt("examine"));


		return data;
	}
};

/**
* 采购单审核/未审核数据映射-创建智能指针对象
*/
class PtrExamineMapper : public Mapper<PtrBuyDO> {
public:
	PtrBuyDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<BuyDO>();

		cout << "in Ptr ExamineMapper resultSet: ";
		cout << "id " << resultSet->getString("id") << endl;
		cout << "source " << resultSet->getString("source") << endl;
		cout << "examine " << resultSet->getInt("examine") << endl;

		data->setId(resultSet->getString("id"));
		data->setSource(resultSet->getString("source"));

		data->setExamine(resultSet->getInt("examine"));
		return data;
	}
};

#endif // !_EXAMINE_MAPPER_H
