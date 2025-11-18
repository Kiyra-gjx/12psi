#pragma once
#ifndef _POTABLE_VO_
#define _POTABLE_VO_

#include "../GlobalInclude.h"
#include "../query/PotableQuery.h"
#include"../dto/PotableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//分页显示JsonVO，用于响应给客户端的Json对象/
class PotableJsonVO : public JsonVO<PotablePageDTO::Wrapper> {
	DTO_INIT(PotableJsonVO, JsonVO<PotablePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif