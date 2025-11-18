#pragma once


#ifndef _IMPORTDATADTO_H_
#define _IMPORTDATADTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 添加文件表单数据
 */
class ImportDataAddFormDTO : public oatpp::DTO
{
	DTO_INIT(ImportDataAddFormDTO, DTO);
	// 文件名
	API_DTO_FIELD_DEFAULT(String, filename, ZH_WORDS_GETTER("file.field.filename"));
	// 文件类型编码
	API_DTO_FIELD_REQUIRE(String, fileType, ZH_WORDS_GETTER("file.field.ft"), true);
	// 文件存储类型编码
	API_DTO_FIELD_REQUIRE(String, saveType, ZH_WORDS_GETTER("file.field.st"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("file.field.remark"));
};

/**
 * 添加文件数据模型
 */
class ImportDataAddDTO : public ImportDataAddFormDTO
{
	DTO_INIT(ImportDataAddDTO, ImportDataAddFormDTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
};

/**
 * 文件数据模型
 */

class ImportDataDTO : public ImportDataAddFormDTO
{
	DTO_INIT(ImportDataDTO, ImportDataAddFormDTO);
	// 唯一标识
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("file.field.id"), true);
	// 保存路径
	API_DTO_FIELD_REQUIRE(String, savePath, ZH_WORDS_GETTER("file.field.path"), true);
	// 数据状态
	API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("file.field.status"));
	// 文件类型名称
	API_DTO_FIELD_DEFAULT(String, fileTypeName, ZH_WORDS_GETTER("file.field.ftn"));
	// 文件存储类型名称
	API_DTO_FIELD_DEFAULT(String, saveTypeName, ZH_WORDS_GETTER("file.field.stn"));
};


/**
 * 单文件上传数据模型
 */
class ImportDataOnlyDTO : public oatpp::DTO
{
	DTO_INIT(ImportDataOnlyDTO, DTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_

