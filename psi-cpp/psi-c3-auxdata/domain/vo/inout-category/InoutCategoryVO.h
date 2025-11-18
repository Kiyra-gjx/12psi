#pragma once
/*
	负责人：绿皮怪
	时间：2025.10.20
*/
#ifndef _INOUTCATEGORY_VO_
#define _INOUTCATEGORY_VO_

#include "../../GlobalInclude.h"
#include "../../dto/inout-category/InoutCategoryDTO.h"
#include <domain/vo/JsonVO.h>
#include <domain/vo/BaseJsonVO.h>


#include OATPP_CODEGEN_BEGIN(DTO)

//简单列表VO（id+名称）
class InoutCategorySimpleListVO : public ListJsonVO<InoutCategorySimpleDTO::Wrapper> {
	DTO_INIT(InoutCategorySimpleListVO, ListJsonVO<InoutCategorySimpleDTO::Wrapper>);
};

//普通VO(id+名称+类别+排序)
class InoutCategoryVO : public JsonVO<InoutCategoryDTO::Wrapper> {
	DTO_INIT(InoutCategoryVO, JsonVO<InoutCategoryDTO::Wrapper>);
};

//详细VO(id+名称+类别+排序+备注)
class InoutCategoryDetailVO : public JsonVO<InoutCategoryDetailDTO::Wrapper> {
	DTO_INIT(InoutCategoryDetailVO, JsonVO<InoutCategoryDetailDTO::Wrapper>);
};

//分页VO
class InoutCategoryPageVO : public JsonVO<InoutCategoryPageDTO::Wrapper> {
	DTO_INIT(InoutCategoryPageVO, JsonVO<InoutCategoryPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INOUTCATEGORY_VO_