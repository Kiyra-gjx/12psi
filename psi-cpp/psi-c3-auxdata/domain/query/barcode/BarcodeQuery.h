#pragma once
#ifndef BARCODEQUERY_H
#define BARCODEQUERY_H 
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class BarcodeClassPageQuery : public PageQuery
{
	DTO_INIT(BarcodeClassPageQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("barcode.field.type"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("barcode.field.name"));
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("barcode.field.content"));
	API_DTO_FIELD_DEFAULT(String, notes, ZH_WORDS_GETTER("barcode.field.notes"));
};
#include OATPP_CODEGEN_END(DTO)
#endif