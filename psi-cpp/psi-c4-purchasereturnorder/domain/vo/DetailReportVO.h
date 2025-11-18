#pragma once
#ifndef _DETAILREPORT_VO_H_
#define _DETAILREPORT_VO_H_

#include "../GlobalInclude.h"
#include "domain/dto/DetailReportDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class DetailReportJsonVO : public JsonVO<DetailReportDTO::Wrapper> {
	DTO_INIT(DetailReportJsonVO, JsonVO<DetailReportDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEVO_H_