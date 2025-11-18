#pragma once
#ifndef _GET_PO_TABLE_CT_
#define _GET_PO_TABLE_CT_
#include"domain/query/PotableQuery.h"
#include"domain/vo/BaseJsonVO.h"
#include"domain/vo/PotaleVO.h"
#include"domain/dto/PotableDTO.h"
// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

//获取采购单报表控制器
class PotableController :public oatpp::web::server::api::ApiController // 继承控制器
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(PotableController);
	// 定义接口
public:
	//定义接口描述
	ENDPOINT_INFO(queryPotable)
	{
		//定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("potable.is_buy.summary"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(PotableJsonVO);
		//定义标签
		API_DEF_ADD_TAG(API_TAG);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("potable.is_goods.name"), "yi fu", false);
		API_DEF_ADD_QUERY_PARAMS(String, "number", ZH_WORDS_GETTER("potable.is_buy.number"), "1av3344aad", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "supplier", ZH_WORDS_GETTER("potable.is_buy.supplier"),1, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "user", ZH_WORDS_GETTER("potable.is_buy.user"),1, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "s_time", ZH_WORDS_GETTER("potable.is_buy.s_time"),1760803200, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "e_time", ZH_WORDS_GETTER("potable.is_buy.e_time"),1760889600, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "people", ZH_WORDS_GETTER("potable.is_buy.people"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "examine", ZH_WORDS_GETTER("potable.is_buy.examine"),0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "nucleus", ZH_WORDS_GETTER("potable.is_buy.nucleus"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "cse", ZH_WORDS_GETTER("potable.is_buy.cse"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "invoice", ZH_WORDS_GETTER("potable.is_buy.invoice"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "check", ZH_WORDS_GETTER("potable.is_buy.check"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(String, "data", ZH_WORDS_GETTER("potable.is_buy.data"), "hello", false);
	}

	//定义查询接口处理
	ENDPOINT(API_M_GET, "/purchaseorder/potable", queryPotable, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(potableQuery, PotableQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryPotable(potableQuery));
	}

private:
	PotableJsonVO::Wrapper execQueryPotable(const PotableQuery::Wrapper &query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif