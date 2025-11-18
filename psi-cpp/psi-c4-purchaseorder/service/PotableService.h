#pragma once
#ifndef _POTABLE_SERVICE_
#define _POTABLE_SERVICE_
#include "domain/query/PotableQuery.h"
#include "domain/vo/PotaleVO.h"
#include "domain/dto//PotableDTO.h"

//采购单服务实现
class PotableService
{
public:
	//分页查询指定的数据
	PotablePageDTO::Wrapper table_odds(const PotableQuery::Wrapper &query);
};

#endif