#pragma once
#include "domain/do/Receipt/ReceiptDO.h"
#include"Mapper.h"
#include <iostream>


//ReceiptMapper映射分页查询数据
class ReceiptMapper : public Mapper<numberDO>
{
public:
	/**
	* 重写虚函数
	*/
	numberDO mapper(ResultSet* resultSet)const override
	{
		numberDO data;
		if (!resultSet)
		{
			throw std::invalid_argument("ResultSet is null");
		}
		/**
		* 映射字段
		*/
		try
		{
			
			if (!resultSet->isNull("number_type"))data.setNumber_type(resultSet->getString("number_type"));
			if (!resultSet->isNull("create_time"))data.setCreate_time(resultSet->getString("create_time"));
			if (!resultSet->isNull("number"))data.setNumber(resultSet->getInt("number"));
			//拼接单据编号
			string receipts = data.getNumber_type()  + data.getCreate_time() + std::to_string(data.getNumber());
			data.setReceipts(receipts);

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		return data;
	}
};

//CountMapper映射查询总数据数的数据映射
class CountMapper : public Mapper<int>
{
public:
	/**
	* 重写虚函数
	*/
	int mapper(ResultSet* rs)const override
	{
		if (rs)
		{
			return rs->getInt(1);
		}
		return 0;
	}
};