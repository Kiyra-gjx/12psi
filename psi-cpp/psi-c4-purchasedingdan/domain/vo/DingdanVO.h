#pragma once
#ifndef _DINGDANVO_H_
#define _DINGDANVO_H_

#include "../GlobalInclude.h"
#include "../dto/DingdanDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单列表分页显示JsonVO
 */
class DingdanListPageJsonVO : public JsonVO<DingdanListPageDTO::Wrapper> {
	DTO_INIT(DingdanListPageJsonVO, JsonVO<DingdanListPageDTO::Wrapper>);
};

/**
 * 采购订单详情显示JsonVO
 */
class DingdanDetailJsonVO : public JsonVO<DingdanDetailDTO::Wrapper> {
	DTO_INIT(DingdanDetailJsonVO, JsonVO<DingdanDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANVO_H_
