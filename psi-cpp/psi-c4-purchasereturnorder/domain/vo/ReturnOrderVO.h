#pragma once
#ifndef _RETURNOrderVO_H_
#define _RETURNOrderVO_H_

#include "../GlobalInclude.h"
#include "../dto/ReturnOrderDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购退货单详情显示JsonVO
 */
class returnorderDetailJsonVO : public JsonVO<returnorderDetailDTO::Wrapper> {
	DTO_INIT(returnorderDetailJsonVO, JsonVO<returnorderDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANVO_H_
