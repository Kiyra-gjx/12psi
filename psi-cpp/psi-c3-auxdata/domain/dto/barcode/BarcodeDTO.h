#pragma once
#ifndef __BARCODE_DTO_H__
#define __BARCODE_DTO_H__
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class BarcodeAddDTO : public oatpp::DTO {
	DTO_INIT(BarcodeAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("barcode.field.type"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("barcode.field.name"));
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("barcode.field.content"));
	API_DTO_FIELD_DEFAULT(String, notes, ZH_WORDS_GETTER("barcode.field.notes"));
};
class BarcodeDTO : public BarcodeAddDTO
{
	DTO_INIT(BarcodeDTO, BarcodeAddDTO);
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("barcode.field.id"), true);
};
class BarcodePageDTO : public PageDTO<BarcodeDTO::Wrapper>
{
	DTO_INIT(BarcodePageDTO, PageDTO<BarcodeDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif