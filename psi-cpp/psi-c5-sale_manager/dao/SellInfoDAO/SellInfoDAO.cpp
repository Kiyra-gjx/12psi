/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:26:52

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
#include "stdafx.h"
#include "SellInfoDAO.h"
#include "SellInfoMapper.h"

uint64_t SellInfoDAO::count(const std::string &pid) {
	string sql = "SELECT COUNT(*) FROM sell_info WHERE pid = ?";
	return sqlSession->executeQueryNumerical(sql, "%s", pid);
}

std::list<PtrSellInfoViewDO> SellInfoDAO::select(const std::string& pid) {
	string sql = R"(
	SELECT 
		g.name goods_name,
		g.number goods_number,
		g.spec goods_spec,
		inf.attr `attr`,
		inf.unit `unit`,
		inf.warehouse warehouse,
		inf.batch batch,
		inf.mfd mfd,
		inf.price price,
		inf.nums `nums`,
		inf.discount discount,
		inf.dsc dsc,
		inf.nums * inf.price total,
		inf.data `data`,
		inf.retreat `retreat`
	FROM sell_info inf
	INNER JOIN (SELECT id,name,number,spec FROM goods) g
	ON g.id = inf.goods
	WHERE inf.pid=?
	)";
	return sqlSession->executeQuery<PtrSellInfoViewDO>(sql, PtrSellInfoViewMapper(), "%s", pid);
}

std::list<SellInfoDO> SellInfoDAO::selectByPid(const std::string& pid)
{
    // 构建查询SQL
    std::string sql = "SELECT * FROM `sell_info` WHERE `pid` = ?";

    // 设置参数
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, pid);

    // 执行查询
    //auto resultSet = sqlSession->executeQuery(sql, params);
    SellInfoMapper mapper;
    return sqlSession->executeQuery<SellInfoDO>(sql, mapper, params);
}
PtrSellInfoDO SellInfoDAO::selectSellInfoById(const string& id)
{
	string sql = "select id,pid,source,goods,attr,unit,warehouse,batch,mfd,price,nums,serial,discount,\
				dsc,total,tax,tat,tpt,data,retreat from sell_info where id = ?";
	return sqlSession->executeQueryOne<PtrSellInfoDO>(sql, PtrSellInfoMapper(), "%s", id);
	}

PtrSellInfoDO SellInfoDAO::selectSellInfoByPid(const string& pid)
{
	string sql = "select id,pid,source,goods,attr,unit,warehouse,batch,mfd,price,nums,serial,discount,\
				dsc,total,tax,tat,tpt,data,retreat from sell_info where pid = ?";
	return sqlSession->executeQueryOne<PtrSellInfoDO>(sql, PtrSellInfoMapper(), "%s", pid);
}
