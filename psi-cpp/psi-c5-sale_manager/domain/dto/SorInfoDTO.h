#pragma once

#ifndef _SorInfo_DTO_
#define _SorInfo_DTO_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/*
	销售订单详情列表数据传输模型
*/
class SorInfoListDTO : public oatpp::DTO
{
	DTO_INIT(SorInfoListDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, id,		ZH_WORDS_GETTER("SorInfo.field.id"));
	API_DTO_FIELD_DEFAULT(String, pid,		ZH_WORDS_GETTER("SorInfo.field.pid"));
	API_DTO_FIELD_DEFAULT(String, goods,	ZH_WORDS_GETTER("SorInfo.field.goods"));
	API_DTO_FIELD_DEFAULT(String, attr,		ZH_WORDS_GETTER("SorInfo.field.attr"));
	API_DTO_FIELD_DEFAULT(String, unit,		ZH_WORDS_GETTER("SorInfo.field.unit"));
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("SorInfo.field.warehouse"));
	API_DTO_FIELD_DEFAULT(Int32, price,		ZH_WORDS_GETTER("SorInfo.field.price"));
	API_DTO_FIELD_DEFAULT(Int32, nums,		ZH_WORDS_GETTER("SorInfo.field.nums"));
	API_DTO_FIELD_DEFAULT(Int32, discount,	ZH_WORDS_GETTER("SorInfo.field.discount"));
	API_DTO_FIELD_DEFAULT(Int32, dsc,		ZH_WORDS_GETTER("SorInfo.field.dsc"));
	API_DTO_FIELD_DEFAULT(Int32, total,		ZH_WORDS_GETTER("SorInfo.field.total"));
	API_DTO_FIELD_DEFAULT(Int32, tax,		ZH_WORDS_GETTER("SorInfo.field.tax"));
	API_DTO_FIELD_DEFAULT(Int32, tat,		ZH_WORDS_GETTER("SorInfo.field.tat"));
	API_DTO_FIELD_DEFAULT(Int32, tpt,		ZH_WORDS_GETTER("SorInfo.field.tpt"));
	API_DTO_FIELD_DEFAULT(String, data,		ZH_WORDS_GETTER("SorInfo.field.data"));
	API_DTO_FIELD_DEFAULT(Int32, handle,	ZH_WORDS_GETTER("SorInfo.field.handle"));

};

class SorInfoListPageDTO : public PageDTO<SorInfoListDTO::Wrapper>
{
	DTO_INIT(SorInfoListPageDTO, PageDTO< SorInfoListDTO::Wrapper>)
};

class SorInfoAddDTO : public oatpp::DTO
{
	DTO_INIT(SorInfoAddDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("SorInfo.field.id"),true);
	API_DTO_FIELD_REQUIRE(String, pid, ZH_WORDS_GETTER("SorInfo.field.pid"), true);
	API_DTO_FIELD_REQUIRE(String, goods, ZH_WORDS_GETTER("SorInfo.field.goods"), true);
	API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("SorInfo.field.attr"));
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("SorInfo.field.unit"));
	API_DTO_FIELD_REQUIRE(String, warehouse, ZH_WORDS_GETTER("SorInfo.field.warehouse"), true);
	API_DTO_FIELD_DEFAULT(Int32, price, ZH_WORDS_GETTER("SorInfo.field.price"));
	API_DTO_FIELD_DEFAULT(Int32, nums, ZH_WORDS_GETTER("SorInfo.field.nums"));
	API_DTO_FIELD_DEFAULT(Int32, discount, ZH_WORDS_GETTER("SorInfo.field.discount"));
	API_DTO_FIELD_DEFAULT(Int32, dsc, ZH_WORDS_GETTER("SorInfo.field.dsc"));
	API_DTO_FIELD_DEFAULT(Int32, total, ZH_WORDS_GETTER("SorInfo.field.total"));
	API_DTO_FIELD_DEFAULT(Int32, tax, ZH_WORDS_GETTER("SorInfo.field.tax"));
	API_DTO_FIELD_DEFAULT(Int32, tat, ZH_WORDS_GETTER("SorInfo.field.tat"));
	API_DTO_FIELD_DEFAULT(Int32, tpt, ZH_WORDS_GETTER("SorInfo.field.tpt"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("SorInfo.field.data"));
	API_DTO_FIELD_DEFAULT(Int32, handle, ZH_WORDS_GETTER("SorInfo.field.handle"));

};

class SorInfoDeleteDTO : public oatpp::DTO
{
	DTO_INIT(SorInfoDeleteDTO, DTO);

	// 仿销售订单写法，不保证正确
	// 订单ID列表
	DTO_FIELD(List<String>, orderIds);
	DTO_FIELD_INFO(orderIds) {
		//	info->description = "要删除的订单ID列表";
		info->required = true;
	}
};

#include OATPP_CODEGEN_END(DTO)


#endif // !_SorInfo_DTO_
