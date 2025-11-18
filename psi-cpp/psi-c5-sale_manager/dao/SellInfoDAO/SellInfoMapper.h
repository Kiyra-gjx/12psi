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

#include "Mapper.h"
#include "../../domain/do/SellInfoDO.h"

/**
 * 示例表字段匹配映射
 */
class SellInfoMapper : public Mapper<SellInfoDO>
{
public:
    SellInfoDO mapper(ResultSet* resultSet) const override
    {
        SellInfoDO data;

        // 按照表中字段顺序依次赋值
        data.setId(resultSet->getString(1));
        data.setPid(resultSet->getString(2));
        data.setSource(resultSet->getString(3));
        data.setGoods(resultSet->getString(4));
        data.setAttr(resultSet->getString(5));     
        data.setUnit(resultSet->getString(6));     
        data.setWarehouse(resultSet->getString(7));
        data.setBatch(resultSet->getString(8));    
        data.setMfd(resultSet->getString(9));
        data.setPrice(resultSet->getDouble(10));   
        data.setNums(resultSet->getDouble(11));    
        data.setSerial(resultSet->getString(12));  
        data.setDiscount(resultSet->getDouble(13));
        data.setDsc(resultSet->getDouble(14));     
        data.setTotal(resultSet->getDouble(15));   
        data.setTax(resultSet->getDouble(16));     
        data.setTat(resultSet->getDouble(17));     
        data.setTpt(resultSet->getDouble(18));     
        data.setData(resultSet->getString(19));    
        data.setRetreat(resultSet->getDouble(20)); 

        return data;
    }
};

/**
 * 示例表字段匹配映射-创建智能指针对象
 */
class PtrSellInfoMapper : public Mapper<PtrSellInfoDO>

{
public:
	PtrSellInfoDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SellInfoDO>();
        // 按照表中字段顺序依次赋值
        //data->setId(resultSet->getString(1));           
        //data->setPid(resultSet->getString(2));          
        //data->setSource(resultSet->getString(3));       
        //data->setGoods(resultSet->getString(4));        
        //data->setAttr(resultSet->getString(5));         
        //data->setUnit(resultSet->getString(6));         
        //data->setWarehouse(resultSet->getString(7));    
        //data->setBatch(resultSet->getString(8));        
        //data->setMfd(resultSet->getString(9));          
        //data->setPrice(resultSet->getDouble(10));       
        //data->setNums(resultSet->getDouble(11));        
        //data->setSerial(resultSet->getString(12));      
        //data->setDiscount(resultSet->getDouble(13));    
        //data->setDsc(resultSet->getDouble(14));         
        //data->setTotal(resultSet->getDouble(15));       
        //data->setTax(resultSet->getDouble(16));         
        //data->setTat(resultSet->getDouble(17));         
        //data->setTpt(resultSet->getDouble(18));         
        //data->setData(resultSet->getString(19));        
        //data->setRetreat(resultSet->getDouble(20));    
		data->setId(resultSet->getString("id"));
		data->setPid(resultSet->getString("pid"));
		data->setSource(resultSet->getString("source"));
		data->setGoods(resultSet->getString("goods"));
		data->setAttr(resultSet->getString("attr"));
		data->setUnit(resultSet->getString("unit"));
		data->setWarehouse(resultSet->getString("warehouse"));
		data->setBatch(resultSet->getString("batch"));
		data->setMfd(resultSet->getString("mfd"));
		data->setPrice(resultSet->getDouble("price"));
		data->setNums(resultSet->getDouble("nums"));
		data->setSerial(resultSet->getString("serial"));
		data->setDiscount(resultSet->getDouble("discount"));
		data->setDsc(resultSet->getDouble("dsc"));
		data->setTotal(resultSet->getDouble("total"));
		data->setTax(resultSet->getDouble("tax"));
		data->setTat(resultSet->getDouble("tat"));
		data->setTpt(resultSet->getDouble("tpt"));
		data->setData(resultSet->getString("data"));
		data->setRetreat(resultSet->getDouble("retreat"));
		return data;
	}
};

class PtrSellInfoViewMapper : public Mapper<PtrSellInfoViewDO> {
public:
    PtrSellInfoViewDO mapper(ResultSet* res) const override {
        auto info = make_shared<SellInfoViewDO>();
        info->setGoodsName(res->getString("goods_name"));
        info->setGoodsNumber(res->getString("goods_number"));
        info->setGoodsSpec(res->getString("goods_spec"));
        info->setAttr(res->getString("attr"));
        info->setUnit(res->getString("unit"));
        info->setWarehouse(res->getString("warehouse"));
        info->setBatch(res->getString("batch"));
        info->setMfd(res->getString("mfd"));
        info->setPrice(res->getDouble("price"));
        info->setNums(res->getDouble("nums"));
        info->setDiscount(res->getDouble("discount"));
        info->setDsc(res->getDouble("dsc"));
        info->setTotal(res->getDouble("total"));
        info->setData(res->getString("data"));
        info->setRetreat(res->getDouble("retreat"));
        return info;
    }
};
