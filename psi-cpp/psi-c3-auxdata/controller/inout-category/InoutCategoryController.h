// 收支类别管理控制器
#ifndef _INOUTCATEGORY_CONTROLLER_
#define _INOUTCATEGORY_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/inout-category/InoutCategoryQuery.h"
#include "domain/dto/inout-category/InoutCategoryDTO.h"
#include "domain/vo/inout-category/InoutCategoryVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("inout-category.api-tag")
class InoutCategoryController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(InoutCategoryController);

public:
	// 获取收支类别名称列表（条件）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("inout-category.get-names.summary"),
		queryCategoryNames, InoutCategoryQuery, InoutCategorySimpleListVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/inoutCategory/queryNames", queryCategoryNames,
		InoutCategoryQuery, execQueryCategoryNames(query));

	// 获取收支类别列表（条件+分页）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("inout-category.get-page.summary"),
		queryPage, InoutCategoryPageQuery, InoutCategoryPageVO::Wrapper, API_TAG
	);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/inoutCategory/queryPage", queryPage,
		InoutCategoryPageQuery, execQueryPage(query));

	// 根据ID查询类别详情
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("inout-category.get-by-id.summary"),
		queryById, InoutCategoryDetailVO::Wrapper, API_TAG,
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("inout-category.field.id"), "d934050a...", true);
	);
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/inoutCategory/queryById/{id}", queryById,
		PATH(String, id), execQueryById(id));

	// 新增类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("inout-category.create"),
		addInoutCategory, InoutCategoryDetailVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/inoutCategory/add", addInoutCategory,
		BODY_DTO(InoutCategoryAddDTO::Wrapper, dto), execAddInoutCategory(dto));

	// 修改类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("inout-category.update"),
		modifyInoutCategory, InoutCategoryDetailVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/inoutCategory/modify", modifyInoutCategory,
		BODY_DTO(InoutCategoryUpdateDTO::Wrapper, dto), execModifyInoutCategory(dto));

	// 删除类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("inout-category.delete"),
		removeInoutCategory, BooleanJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("inout-category.field.id"), "d934050a...", true);
	);
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/inoutCategory/remove/{id}", removeInoutCategory,
		PATH(String, id), execRemoveInoutCategory(id));

private:
	InoutCategorySimpleListVO::Wrapper execQueryCategoryNames(const InoutCategoryQuery::Wrapper& query);
	InoutCategoryPageVO::Wrapper execQueryPage(const InoutCategoryPageQuery::Wrapper& query);
	InoutCategoryDetailVO::Wrapper execQueryById(const String& id);
	InoutCategoryDetailVO::Wrapper execAddInoutCategory(const InoutCategoryAddDTO::Wrapper& dto);
	InoutCategoryDetailVO::Wrapper execModifyInoutCategory(const InoutCategoryUpdateDTO::Wrapper& dto);
	BooleanJsonVO::Wrapper execRemoveInoutCategory(const String& id);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // !_INOUTCATEGORY_CONTROLLER_