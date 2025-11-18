#pragma once
#ifndef _FILEDTO_H_
#define _FILEDTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 添加文件数据模型
 */
class FileAddDTO : public oatpp::DTO
{
	DTO_INIT(FileAddDTO, DTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("file.field.remark"));
};


class FileDownDTO : public oatpp::DTO
{
	DTO_INIT(FileDownDTO, DTO);

	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("file.field.remark"));
};




#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_