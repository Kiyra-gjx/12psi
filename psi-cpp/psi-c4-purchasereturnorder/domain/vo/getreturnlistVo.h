#pragma once

#ifndef _GETRETURNLISTVO_H_
#define _GETRETURNLISTVO_H_

#include "GlobalInclude.h"
#include "domain/dto/getreturnlistDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个采购退货单信息显示JsonVO对象，用于响应给客户端
 */
class getreturnlistJsonVO : public JsonVO<getreturnlistDTO::Wrapper>
{
    DTO_INIT(getreturnlistJsonVO, JsonVO<getreturnlistDTO::Wrapper>);
};

/**
 * 定义一个采购退货单信息分页显示JsonVO对象，用于响应给客户端
 */
class getreturnlistPageJsonVO : public JsonVO<getreturnlistPageDTO::Wrapper>
{
    DTO_INIT(getreturnlistPageJsonVO, JsonVO<getreturnlistPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_GETRETURNLISTVO_H_