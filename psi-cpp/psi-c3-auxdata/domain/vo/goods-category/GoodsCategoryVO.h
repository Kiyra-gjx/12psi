#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 */
#ifndef _GOODS_CATEGORY_VO_
#define _GOODS_CATEGORY_VO_

#include "../../GlobalInclude.h"
#include "../../dto/goods-category/GoodsCategoryDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

 /**
  * 商品类别单条数据视图对象
  */
class GoodsCategoryJsonVO : public JsonVO<GoodsCategoryDTO::Wrapper> {
	DTO_INIT(GoodsCategoryJsonVO, JsonVO<GoodsCategoryDTO::Wrapper>);
};

/**
 * 商品类别分页数据视图对象
 */
class GoodsCategoryPageJsonVO : public JsonVO<GoodsCategoryPageDTO::Wrapper> {
	DTO_INIT(GoodsCategoryPageJsonVO, JsonVO<GoodsCategoryPageDTO::Wrapper>);
};

class GoodsCategoryListJsonVO : public JsonVO<oatpp::Vector<GoodsCategoryDTO::Wrapper>> {
	DTO_INIT(GoodsCategoryListJsonVO, JsonVO<oatpp::Vector<GoodsCategoryDTO::Wrapper>>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_GOODS_CATEGORY_VO_
//