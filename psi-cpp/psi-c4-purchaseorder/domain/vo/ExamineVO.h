#pragma once

#ifndef _EXAMINE_VO_H_
#define _EXAMINE_VO_H_

#include "../GlobalInclude.h"
#include "../dto/ExamineDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
*	采购单审核响应数据
*/	
class ExamineJsonVO : public JsonVO<ExamineDTO::Wrapper>
{
	DTO_INIT(ExamineJsonVO, JsonVO<ExamineDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_EXAMINE_VO_H_
