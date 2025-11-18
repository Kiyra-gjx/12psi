#pragma once
#ifndef _POTABLE_INFO_DAO_
#define _POTABLE_INFO_DAO_
#include "BaseDAO.h"
#include"../domain/query/PotableInfoQuery.h"
#include"../domain/do/PotableInfoDO.h"
//分页条件获取采购单列表的数据库操作
class PotableInfoDAO :public BaseDAO
{
public:
	// 查询数据
	std::list<PotableInfoDO> selectPotableInfoPID(const PotableInfoQuery::Wrapper& query);
};

#endif