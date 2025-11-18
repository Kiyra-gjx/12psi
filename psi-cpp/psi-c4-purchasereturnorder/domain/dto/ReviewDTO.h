#pragma once

#ifndef _REVIEWRETRUN_DTO_
#define _REVIEWRETRUN_DTO_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 审核操作请求DTO
 * 和BreDO要对应
 */
class ReviewDTO : public oatpp::DTO {
    DTO_INIT(ReviewDTO, DTO);

    // 主键ID
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("reviewRetrunOrder.field.id"), true);
    // 单据ID
    API_DTO_FIELD_REQUIRE(String, source, ZH_WORDS_GETTER("reviewRetrunOrder.field.source"), true);

};



#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_