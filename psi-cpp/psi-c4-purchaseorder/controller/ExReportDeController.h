#pragma once

#ifndef _EXREPORTDE_CONTROLLER_H_
#define _EXREPORTDE_CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/ExReportDeJsonVO.h"
#include "domain/dto/ExReportDeDTO.h"
#include "domain/query/ExReportDeQUERY.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

/**
 * 采购订单报表明细接口控制器
 */
class ExReportDeController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ExReportDeController);
public:

	// 3.1 定义导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("order.file.DeEx"), exportSample, ExReportDeQUERY, Void, API_TAG);
	// 3.2 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/purchaseorder/exportDe", exportSample, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, ExReportDeQUERY, queryParams); return execExportDe(userQuery););
		
	
private:
	// 3.3 演示导出数据
	std::shared_ptr<OutgoingResponse> execExportDe(const ExReportDeQUERY::Wrapper& query);
	


};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif