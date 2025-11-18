#pragma once


#ifndef _IMPORT_QUERY_
#define _IMPORT_QUERY_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class ImportQuery : public PageQuery
{
	DTO_INIT(ImportQuery, PageQuery);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_