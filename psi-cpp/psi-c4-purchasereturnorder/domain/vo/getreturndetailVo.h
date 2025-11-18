#include "GlobalInclude.h"
#include "domain/dto/getreturndetailDTO.h"

#ifndef _GETRETURNDETAILVO_H_
#define _GETRETURNDETAILVO_H_
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个采购退货单详情信息响应JsonVO，用于响应给客户端
 */
class getreturndetailJsonVO : public JsonVO<getreturndetailDTO::Wrapper>
{
    DTO_INIT(getreturndetailJsonVO, JsonVO<getreturndetailDTO::Wrapper>);
};

/**
 * 定义一个采购退货单详情信息分页响应JsonVO，用于响应给客户端
 */
class getreturndetailPageJsonVO : public JsonVO<getreturndetailPageDTO::Wrapper>
{
    DTO_INIT(getreturndetailPageJsonVO, JsonVO<getreturndetailPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif