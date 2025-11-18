#pragma once
#ifndef _GET_PO_TABLE__INFO_QUERY_
#define _GET_PO_TABLE__INFO_QUERY_
#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//获取采购单详情
class PotableInfoQuery : public PageQuery
{
	//定义初始化
	DTO_INIT(PotableInfoQuery, PageQuery);

	//所属组id(采购单id)
	DTO_FIELD(Int32, pid);
	DTO_FIELD_INFO(pid) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.pid");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif
