#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

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

#ifndef _SELL_DAO_
#define _SELL_DAO_

#include "BaseDAO.h"
#include "../../domain/do/SellDO.h"
#include "../../domain/dto/SellDTO.h"
#include "../../domain/query/SellQuery.h"
#include"id/UuidFacade.h"
/**
 * 示例表数据库操作实现
 */
class SellDAO : public BaseDAO
{
private:
public:
	//根据订单编号获取Sell
	std::list<SellDO> selectByNumber(const std::string& number);
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
	 // 条件构建器：拼接销售单列表的查询条件
	std::string queryConditionBuilder(const SellListQuery::Wrapper& query, SqlParams& params);

	std::string queryOrderBuilder(const SellListQuery::Wrapper& query, SqlParams& params);
public:
	// 统计符合条件的销售单数量
	uint64_t count(const SellListQuery::Wrapper& query);
	uint64_t countById(const std::string& id);

	// 分页查询销售单列表
	std::list<PtrSellViewDO> selectWithPage(const SellListQuery::Wrapper& query);

	// 按ID查询销售单详情
	PtrSellViewDO selectById(const std::string& id);

	// 按ID删除销售单
	bool deleteById(const std::string& id);
	//导入数据
	bool importData(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto, std::string& sell_uuid);

	bool approveById(const std::string& id);    // examine = 1
	bool unapproveById(const std::string& id);  // examine = 0
	bool isOrderApproved(const std::string& id);
};

#endif
//SELL_DAO
