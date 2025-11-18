#pragma once
#ifndef _EXREPORTDEVO_H_
#define _EXREPORTDEVO_H_

#include "../GlobalInclude.h"
#include "../dto/ExReportDeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class ExReportDePageJsonVO : public JsonVO<ExReportDeDTO::Wrapper> {
	DTO_INIT(ExReportDePageJsonVO, JsonVO<ExReportDeDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEVO_H_