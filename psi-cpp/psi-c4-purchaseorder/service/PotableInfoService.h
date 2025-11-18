#pragma once
#ifndef _POTABLE_SERVICE_
#define _POTABLE_SERVICE_
#include "domain/query/PotableInfoQuery.h"
#include "../domain/vo/PotableInfoVO.h"
#include "domain/dto//PotableInfoDTO.h"


//采购单详情服务实现
class PotableInfoService
{
public:
	//查询指定的数据
	PotableInfoDTO::Wrapper tableInfo(const PotableInfoQuery::Wrapper& query);
};

#endif
