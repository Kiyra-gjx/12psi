/*
	负责人：绿皮怪
	时间：2025.10.20
*/
#ifndef _INOUTCATEGORY_DTO_
#define _INOUTCATEGORY_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//================================================================================
// 1. 响应 DTO (Response DTOs) - 用于从服务器返回给前端
//================================================================================

//简单DTO（id+名称）
class InoutCategorySimpleDTO : public oatpp::DTO
{
	DTO_INIT(InoutCategorySimpleDTO, DTO);
	// 编号
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("inout-category.field.id"));
	// 类别名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("inout-category.field.name"));
};

//普通DTO(id+名称+类别+排序)
class InoutCategoryDTO:public InoutCategorySimpleDTO
{
	DTO_INIT(InoutCategoryDTO, InoutCategorySimpleDTO);
	// 收支类型
	API_DTO_FIELD_DEFAULT(Int32, type, ZH_WORDS_GETTER("inout-category.field.type"));
	// 类别排序
	API_DTO_FIELD_DEFAULT(Int32, sort, ZH_WORDS_GETTER("inout-category.field.sort"));
};

//详细DTO(id+名称+类别+排序+备注)
class InoutCategoryDetailDTO : public InoutCategoryDTO
{
	DTO_INIT(InoutCategoryDetailDTO, InoutCategoryDTO);
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("inout-category.field.data"));
};

//分页 DTO
class InoutCategoryPageDTO : public PageDTO<InoutCategoryDTO::Wrapper>
{
	DTO_INIT(InoutCategoryPageDTO, PageDTO<InoutCategoryDTO::Wrapper>);
};

//================================================================================
// 2. 请求 DTO (Request DTOs) - 用于前端发送给服务器
//================================================================================

// 新增 DTO
class InoutCategoryAddDTO : public oatpp::DTO
{
	DTO_INIT(InoutCategoryAddDTO, DTO);
	// 类别名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("inout-category.field.dto-name"), true);
	// 收支类型
	API_DTO_FIELD_REQUIRE(Int32, type, ZH_WORDS_GETTER("inout-category.field.dto-type"), true);
	// 类别排序
	API_DTO_FIELD_DEFAULT(Int32, sort, ZH_WORDS_GETTER("inout-category.field.dto-sort"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("inout-category.field.dto-data"));
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 修改 DTO
class InoutCategoryUpdateDTO : public oatpp::DTO
{
	DTO_INIT(InoutCategoryUpdateDTO, DTO);
	// 编号
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("inout-category.field.id"), true);
	// 类别名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("inout-category.field.dto-name"), true);
	// 收支类型
	API_DTO_FIELD_REQUIRE(Int32, type, ZH_WORDS_GETTER("inout-category.field.dto-type"), true);
	// 类别排序
	API_DTO_FIELD_DEFAULT(Int32, sort, ZH_WORDS_GETTER("inout-category.field.dto-sort"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("inout-category.field.dto-data"));
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INOUTCATEGORY_DTO_