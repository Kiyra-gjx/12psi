/*
	负责人：绿皮怪
	时间：2025.10.20
*/
#ifndef _INOUTCATEGORY_QUERY_
#define _INOUTCATEGORY_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//分页查询对象
class InoutCategoryPageQuery : public PageQuery
{
	DTO_INIT(InoutCategoryPageQuery, PageQuery);
	// 类别名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("inout-category.field.query-name");
	}
	// 收支类型
	DTO_FIELD(Int32, type);
	DTO_FIELD_INFO(type) {
		info->description = ZH_WORDS_GETTER("inout-category.field.query-type");
	}
};

// 普通查询对象
class InoutCategoryQuery :public oatpp::DTO {
	DTO_INIT(InoutCategoryQuery, DTO);
	//收支类型
	DTO_FIELD(Int32, type);
	DTO_FIELD_INFO(type) {
		info->description = ZH_WORDS_GETTER("inout-category.field.query-type");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INOUTCATEGORY_QUERY_