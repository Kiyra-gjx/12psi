#pragma once
#ifndef _EXREPORTSIMVO_H_
#define _EXREPORTSIMVO_H_

#include "../GlobalInclude.h"
#include "../dto/ExReportSimDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class ExReportSimPageJsonVO : public JsonVO<ExReportSimPageDTO::Wrapper> {
	DTO_INIT(ExReportSimPageJsonVO, JsonVO<ExReportSimPageDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEVO_H_