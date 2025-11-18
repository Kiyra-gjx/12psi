#pragma once
#ifndef _POTABLE_INFO_VO_
#define _POTABLE_INFO_VO_

#include "../GlobalInclude.h"
#include "../query/PotableInfoQuery.h"
#include"../dto/PotableInfoDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//显示JsonVO，用于响应给客户端的Json对象
class PotableInfoJsonVO : public JsonVO<PotableInfoDTO::Wrapper> {
	DTO_INIT(PotableInfoJsonVO, JsonVO<PotableInfoDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif //_POTABLE_INFO_VO_
