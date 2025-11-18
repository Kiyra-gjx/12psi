#pragma once

#ifndef _IMPORTDATAVO_H_
#define _IMPORTDATAVO_H_

#include "../GlobalInclude.h"
#include "../dto/ImportDataDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 文件信息响应数据
 */
class ImportDataJsonVO : public JsonVO<ImportDataDTO::Wrapper>
{
	DTO_INIT(ImportDataJsonVO, JsonVO<ImportDataDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEVO_H_