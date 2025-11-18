#pragma once
#ifndef _FILEVO_H_
#define _FILEVO_H_

#include "../GlobalInclude.h"
#include "../dto/FileDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * editor响应图片上传结果数据
 */
class EditorImageVO : public JsonVO<EditorImageDTO::Wrapper>
{
	DTO_INIT(EditorImageVO, JsonVO<EditorImageDTO::Wrapper>);
};

/**
 * 文件信息响应数据
 */
class FileJsonVO : public JsonVO<FileDTO::Wrapper>
{
	DTO_INIT(FileJsonVO, JsonVO<FileDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEVO_H_