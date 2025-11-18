#pragma once
#ifndef _GET_PO_TABLE_INFO_CT_
#define _GET_PO_TABLE_INFO_CT_
#include"domain/query/PotableInfoQuery.h"
#include"domain/vo/BaseJsonVO.h"
#include"domain/vo/PotableInfoVO.h"
#include"domain/dto/PotableInfoDTO.h"
// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

//获取采购单报表控制器
class PotableInfoController :public oatpp::web::server::api::ApiController // 继承控制器
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(PotableInfoController);
	// 定义接口
public:
	//定义接口描述
	ENDPOINT_INFO(queryPotableInfo)
	{
		//定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("potable.is_buy_info.summary"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(PotableInfoJsonVO);
		//定义标签
		API_DEF_ADD_TAG(API_TAG);
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(Int32, "pid", ZH_WORDS_GETTER("potable.is_buy_info.pid"),1,true);
	}

	//定义查询接口处理
	ENDPOINT(API_M_GET, "/purchaseorder/potableinfo", queryPotableInfo, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(potableinfoQuery, PotableInfoQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryPotableInfo(potableinfoQuery));
	}

private:
	PotableInfoJsonVO::Wrapper execQueryPotableInfo(const PotableInfoQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif
