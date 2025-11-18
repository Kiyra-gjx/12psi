#pragma once
#ifndef _attachment_VO_
#define _attachment_VO_

#include "../../GlobalInclude.h"
#include "../../dto/attachment/AttachmentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 表示修改JsonVO，用于响应客户端的修改Json
 */
class ModifyJsonVO : public JsonVO<AttachmentDTO::Wrapper> {
	DTO_INIT(ModifyJsonVO, JsonVO<AttachmentDTO::Wrapper>);
};

/**
 * 表示删除JsonVO，用于响应客户端的删除Json
 */
class RemoveJsonVO : public JsonVO<AttachmentRemoveDTO::Wrapper> {
	DTO_INIT(RemoveJsonVO, JsonVO<AttachmentRemoveDTO::Wrapper>);
};

/**
 * 表示查询JsonVO，用于响应客户端的查询Json
 */
class QueryJsonVO : public JsonVO<oatpp::List<AttachmentDTO::Wrapper>> {
public:
	DTO_INIT(QueryJsonVO, JsonVO<oatpp::List<AttachmentDTO::Wrapper>>);
};

/**
 * 表示添加JsonVO，用于响应客户端的添加Json
 */
class AddJsonVO : public JsonVO<AttachmentAddDTO::Wrapper> {
	DTO_INIT(AddJsonVO, JsonVO<AttachmentAddDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_VO_