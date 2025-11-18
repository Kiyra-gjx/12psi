#pragma once
#ifndef BARCODE_VO_H
#define BARCODE_VO_H 
#include"../../GlobalInclude.h"
#include"../../dto/barcode/BarcodeDTO.h"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)
/*
 条码显示JsonVO，用于响应给客户端的Json对象
*/
class BarcodeJsonVO : public JsonVO<BarcodeDTO::Wrapper> {
	DTO_INIT(BarcodeJsonVO, JsonVO<BarcodeDTO::Wrapper>);
};

/*
 条码分页显示JsonVO，用于响应给客户端的Json对象
*/
class BarcodePageJsonVO : public JsonVO<BarcodePageDTO::Wrapper> {
	DTO_INIT(BarcodePageJsonVO, JsonVO<BarcodePageDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif

