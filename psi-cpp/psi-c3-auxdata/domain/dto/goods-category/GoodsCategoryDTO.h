#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 */
#ifndef _GOODS_CATEGORY_DTO_
#define _GOODS_CATEGORY_DTO_
#include "../../GlobalInclude.h"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

 /**
  * 商品类别新增传输对象
  */
class GoodsCategoryAddDTO : public oatpp::DTO
{
	DTO_INIT(GoodsCategoryAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("goodsCategory.field.pid"));    // 所属类别
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goodsCategory.field.name"));  // 类别名称
	API_DTO_FIELD_DEFAULT(Int32, sort, ZH_WORDS_GETTER("goodsCategory.field.sort")); // 类别排序
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("goodsCategory.field.data")); // 备注信息

};


 /**
  * 商品类别基本传输对象
  */
class GoodsCategoryDTO : public oatpp::DTO
{
	DTO_INIT(GoodsCategoryDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("goodsCategory.field.id"), true); // 主键ID,必须传输
	API_DTO_FIELD_DEFAULT(String, pid, ZH_WORDS_GETTER("goodsCategory.field.pid"));    // 所属类别
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goodsCategory.field.name"));  // 类别名称
	API_DTO_FIELD_DEFAULT(Int32, sort, ZH_WORDS_GETTER("goodsCategory.field.sort")); // 类别排序
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("goodsCategory.field.data")); // 备注信息
};


// 商品类别删除传输对象
class GoodsCategoryDeleteDTO : public oatpp::DTO
{
	DTO_INIT(GoodsCategoryDeleteDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("goodsCategory.field.id"), true); // 主键ID值,必须传输
};

// 商品分类分页DTO（继承PageDTO）
class GoodsCategoryPageDTO : public PageDTO<GoodsCategoryDTO::Wrapper>
{
	DTO_INIT(GoodsCategoryPageDTO, PageDTO<GoodsCategoryDTO::Wrapper>);
	// 只继承父类的 pageIndex/pageSize/total/pages/rows，不添加任何字段！
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_GOODS_CATEGORY_DTO_
