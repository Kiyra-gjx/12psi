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

#ifndef _SAMPLE_MAPPER_
#define _SAMPLE_MAPPER_
#include "Mapper.h"
#include "../../domain/do/SellDO.h"

/**
 * 销售表字段匹配映射
 */
 //class SellMapper : public Mapper<SellDO>
 //{
 //public:
 //    SellDO mapper(ResultSet* resultSet) const override
 //    {
 //        SellDO data;
 //
 //        // 按照表中字段顺序依次赋值
 //        data.setId(resultSet->getString(1));              // id - varchar -> getString
 //        data.setSource(resultSet->getString(2));          // source - varchar -> getString
 //        data.setFrame(resultSet->getString(3));           // frame - varchar -> getString
 //        data.setCustomer(resultSet->getString(4));        // customer - varchar -> getString
 //        data.setTime(resultSet->getString(5));            // time - datetime -> getString
 //        data.setNumber(resultSet->getString(6));          // number - varchar -> getString
 //        data.setTotal(resultSet->getDouble(7));           // total - decimal -> getDouble
 //        data.setActual(resultSet->getDouble(8));          // actual - decimal -> getDouble
 //        data.setMoney(resultSet->getDouble(9));           // money - decimal -> getDouble
 //        data.setCost(resultSet->getDouble(10));           // cost - decimal -> getDouble
 //        data.setAccount(resultSet->getString(11));        // account - varchar -> getString
 //        data.setPeople(resultSet->getString(12));         // people - varchar -> getString
 //        data.setLogistics(resultSet->getString(13));      // logistics - text -> getString
 //        data.setFile(resultSet->getString(14));           // file - text -> getString
 //        data.setData(resultSet->getString(15));           // data - varchar -> getString
 //        data.setMore(resultSet->getString(16));           // more - text -> getString
 //        data.setExamine(resultSet->getInt(17));           // examine - tinyint -> getInt
 //        data.setNucleus(resultSet->getInt(18));           // nucleus - tinyint -> getInt
 //        data.setCse(resultSet->getInt(19));               // cse - tinyint -> getInt
 //        data.setInvoice(resultSet->getInt(20));           // invoice - tinyint -> getInt
 //        data.setCheck(resultSet->getInt(21));             // check - tinyint -> getInt
 //        data.setUser(resultSet->getString(22));           // user - varchar -> getString
 //
 //        return data;
 //    }
 //};
 /*
  * 示例表字段匹配映射
  */
class SellMapper : public Mapper<SellDO> {
public:
	SellDO mapper(ResultSet* resultSet) const override {
		SellDO data;
		data.setId(resultSet->getString("id"));//
		data.setFrame(resultSet->getString("frame"));//
		data.setCustomer(resultSet->getString("customer"));//
		data.setTotal(resultSet->getDouble("total"));//
		data.setTime(resultSet->getString("time"));//
		data.setNumber(resultSet->getString("number"));//
		data.setUser(resultSet->getString("user"));//
		data.setActual(resultSet->getDouble("actual"));//
		data.setMoney(resultSet->getDouble("money"));//
		data.setCost(resultSet->getDouble("cost"));//
		data.setExamine(resultSet->getInt("examine"));//
		data.setNucleus(resultSet->getInt("nucleus"));//
		data.setCse(resultSet->getInt("cse"));//
		data.setInvoice(resultSet->getInt("invoice"));//
		data.setCheck(resultSet->getInt("check"));//
		return data;
	}
};

/**
 * 示例表字段匹配映射-创建智能指针对象
 */
class PtrSellMapper : public Mapper<PtrSellDO>
{
public:
	PtrSellDO mapper(ResultSet* resultSet) const override
	{
		PtrSellDO data = std::make_shared<SellDO>();
		data->setId(resultSet->getString("id"));//
		data->setFrame(resultSet->getString("frame"));//
		data->setCustomer(resultSet->getString("customer"));//
		data->setTotal(resultSet->getDouble("total"));//
		data->setTime(resultSet->getString("time"));//
		data->setNumber(resultSet->getString("number"));//
		data->setUser(resultSet->getString("user"));//
		data->setActual(resultSet->getDouble("actual"));//
		data->setMoney(resultSet->getDouble("money"));//
		data->setCost(resultSet->getDouble("cost"));//
		data->setExamine(resultSet->getInt("examine"));//
		data->setNucleus(resultSet->getInt("nucleus"));//
		data->setCse(resultSet->getInt("cse"));//
		data->setInvoice(resultSet->getInt("invoice"));//
		data->setCheck(resultSet->getInt("check"));//
		return data;
	}
};

class PtrSellViewMapper : public Mapper<PtrSellViewDO> {
public:
	/**
	 * 实现 Mapper 的核心方法：从 ResultSet 提取字段并构建 SellDO 对象
	 * @param resultSet 数据库查询结果集
	 * @return 映射后的销售单智能指针对象
	 */
	PtrSellViewDO mapper(ResultSet* resultSet) const override {
		auto sellDO = std::make_shared<SellViewDO>();
		//DO本身的数据
		//属性
		sellDO->setId(resultSet->getString("id"));
		sellDO->setFrame(resultSet->getString("frame"));
		sellDO->setCustomer(resultSet->getString("customer"));
		sellDO->setTime(resultSet->getString("time"));
		sellDO->setNumber(resultSet->getString("number"));
		sellDO->setPeople(resultSet->getString("people"));
		sellDO->setData(resultSet->getString("data"));
		sellDO->setUser(resultSet->getString("user"));

		//费用相关
		sellDO->setTotal(resultSet->getDouble("total"));
		sellDO->setActual(resultSet->getDouble("actual"));
		sellDO->setMoney(resultSet->getDouble("sell_money"));
		sellDO->setCost(resultSet->getDouble("cost"));

		//状态
		sellDO->setExamine(resultSet->getInt("examine"));
		sellDO->setNucleus(resultSet->getInt("nucleus"));
		sellDO->setCse(resultSet->getInt("cse"));
		sellDO->setInvoice(resultSet->getInt("invoice"));
		sellDO->setCheck(resultSet->getInt("check"));

		//联表数据
		sellDO->setWriteOffMoney(resultSet->getDouble("bill_money"));
		return sellDO;
	}
};

#endif
