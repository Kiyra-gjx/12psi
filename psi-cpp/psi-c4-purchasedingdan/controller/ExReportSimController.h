#pragma once

#ifndef _EXREPORTSIM_CONTROLLER_H_
#define _EXREPORTSIM_CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/ExReportSimVO.h"
#include "domain/dto/ExReportSimDTO.h"
#include "domain/query/ExReportSimQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("purchase.tag")

/**
 * 采购订单报表明细接口控制器
 */
class ExReportSimController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ExReportSimController);
public:

	// 3.1 定义导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("file.SimEx"), exportSample, ExReportSimQuery, Void, API_TAG);
	// 3.2 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/purchasedingdan/reportSimExport", exportSample, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, ExReportSimQuery, queryParams); return execExportSim(userQuery););
private:
	// 3.3 演示导出数据
	std::shared_ptr<OutgoingResponse> execExportSim(const ExReportSimQuery::Wrapper& query);
	


};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif