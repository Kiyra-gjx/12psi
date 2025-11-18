#pragma once

#ifndef _SELLCONTROLLER_H_
#define _SELLCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "../../Macros.h"
#include "ServerInfo.h"
#include "domain/dto/SellDTO.h"
#include "domain/query/SellQuery.h"
#include "domain/vo/SellVO.h"
#include "../../service/SellService/SellService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG_SELL ZH_WORDS_GETTER("sell.tag")

class SellController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(SellController);
public://定义接口
	// 批量删除销售单 - 接口描述
	ENDPOINT_INFO(batchDelete) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.sell.delsell");
		info->addTag(API_TAG_SELL);
		info->addResponse<Object<SalenoteDeleteResultVO>>(Status::CODE_200, "application/json");
	}
	// 批量删除销售单 - 接口实现
	ENDPOINT(API_M_POST, "/sell/sales-note/batch-delete", batchDelete,
		BODY_DTO(SalenoteDeleteDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		// 调用模拟执行函数，并用 API_HANDLER_RESP_VO 包装返回
		API_HANDLER_RESP_VO(executeBatchDelete(dto));
	}

	// 批量审核
	ENDPOINT_INFO(sellBatchApprove) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.sell.review");   // 可在 zh-dict.yaml 增加该键
		info->addTag(API_TAG_SELL);
		info->addResponse<Object<SellAuditResultVO>>(Status::CODE_200, "application/json");
	}
	ENDPOINT(API_M_POST, "/sell/api/batch-approve", sellBatchApprove,
		BODY_DTO(SellAuditDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeBatchApprove(dto));
	}

	// 批量反审核
	ENDPOINT_INFO(sellBatchUnapprove) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.sell.counterreview"); // 同上，建议在字典里补
		info->addTag(API_TAG_SELL);
		info->addResponse<Object<SellAuditResultVO>>(Status::CODE_200, "application/json");
	}
	ENDPOINT(API_M_POST, "/sell/api/batch-unapprove", sellBatchUnapprove,
		BODY_DTO(SellAuditDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeBatchUnapprove(dto));
	}


	// 导入数据（前端解析表格后发给后端）
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.sell.import"),
		modifySellImport, Boolean, API_TAG_SELL);

	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sell/modifySellImport",
		modifySellImport,
		BODY_DTO(SellImportDTO::Wrapper, dto),
		execSellImport(authObject->getPayload(), dto));

	//接口描述部分3个
	ENDPOINT_INFO(querySellList)
	{
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.sell.queryall"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(SellListJsonVO);
		API_DEF_ADD_TAG(API_TAG_SELL);
		API_DEF_ADD_PAGE_PARAMS();

		// 查询条件参数
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("goods.field.name"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "number", ZH_WORDS_GETTER("sell.field.number"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "customer", ZH_WORDS_GETTER("sell.field.customer"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "people", ZH_WORDS_GETTER("sell.field.people"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "begintime", ZH_WORDS_GETTER("sell.field.begintime"), "2020-01-01", false);
		API_DEF_ADD_QUERY_PARAMS(String, "endtime", ZH_WORDS_GETTER("sell.field.endtime"), "2030-01-01", false);
		API_DEF_ADD_QUERY_PARAMS(String, "user", ZH_WORDS_GETTER("sell.field.user"), "", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "examine", ZH_WORDS_GETTER("sell.field.examine"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "nucleus", ZH_WORDS_GETTER("sell.field.nucleus"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "cse", ZH_WORDS_GETTER("sell.field.cse"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "invoice", ZH_WORDS_GETTER("sell.field.invoice"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "check", ZH_WORDS_GETTER("sell.field.check"), 0, false);
		API_DEF_ADD_QUERY_PARAMS(String, "data", ZH_WORDS_GETTER("sell.field.data"), "", false);
		// 时间排序方式(空:不排序|0:降序|1:升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "timeSortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.time"), , false);
		// 单据编号排序方式(空 : 不排序 | 0 : 降序 | 1 : 升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "numberSortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.number"), , false);
		// 单据金额排序方式(空 : 不排序 | 0 : 降序 | 1 : 升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "totalSortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.total"), , false);
		// 实际金额排序方式(空 : 不排序 | 0 : 降序 | 1 : 升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "actualSortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.actual"), , false);
		// 单据付款(实付金额)排序方式(空 : 不排序 | 0 : 降序 | 1 : 升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "moneySortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.money"), , false);
		// 单据费用排序方式(空 : 不排序 | 0 : 降序 | 1 : 升序)
		API_DEF_ADD_QUERY_PARAMS(Boolean, "costSortOrder", ZH_WORDS_GETTER("saleReturnOrder.sortOrder.cost"), , false);
	}

	ENDPOINT_INFO(querySellDetail)
	{
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.sell.querydetail"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(SellDetailJsonVO);
		API_DEF_ADD_TAG(API_TAG_SELL);
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("sell.field.listid"), "N", true);
	}

	ENDPOINT_INFO(sellAddList)
	{
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.sell.addsell"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(SellAddJsonVO);
		API_DEF_ADD_TAG(API_TAG_SELL);
	}

	// 查询销售单列表
	ENDPOINT(API_M_GET, "/sell/list", querySellList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		API_HANDLER_QUERY_PARAM(sellListQuery, SellListQuery, queryParams);
		API_HANDLER_RESP_VO(execSellQueryList(sellListQuery));
	}

	// 查询销售单详情
	ENDPOINT(API_M_GET, "/sell/detail", querySellDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		API_HANDLER_QUERY_PARAM(sellDetailQuery, SellDetailQuery, queryParams);
		API_HANDLER_RESP_VO(execSellQueryDetail(sellDetailQuery));
	}

	// 新增销售单
	ENDPOINT(API_M_POST, "/sell/add", sellAddList, BODY_DTO(SellCreateDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME)
	{
		API_HANDLER_RESP_VO(execSellAddList(dto));
	}


	//模块2--慵懒的汪负责
	//修改销售单描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.sell.modify"), modifySell, StringJsonVO::Wrapper, API_TAG_SELL);
	//修改销售单端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sell/modify", modifySell, BODY_DTO(SellUpdateDTO::Wrapper, dto), executeModify(dto, authObject->getPayload()));
	//导出简单报表描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("summary.sell.exportsimple"), exportsample, SellListQuery, Void, API_TAG_SELL);
	//导出简单报表端点
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/sell/simple", exportsample, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, SellListQuery, queryParams); return executequerysimple(userQuery););

	//导出详细报表描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("summary.sell.exportdetail"), querymore, SellListQuery, Void, API_TAG_SELL);
	//导出详细报表端点
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/sell/Detial", querymore, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, SellListQuery, queryParams); return executequerymore(userQuery););

	//获取生成销售退货单数据,根据单据编号返回
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.sell.modifySellGenerateReturn"), modifySellGenerateReturn, SellGenerateReturnDTO::Wrapper, API_TAG_SELL);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sell/modifySellGenerateReturn/{number}", modifySellGenerateReturn, PATH(String, number), execSellGenerateReturn(number));
private://定义接口执行函数
	// 模拟执行函数（返回 VO）
	SalenoteDeleteJsonVO::Wrapper executeBatchDelete(const SalenoteDeleteDTO::Wrapper& dto);



	// 导入数据
	Boolean execSellImport(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto);
	SellListJsonVO::Wrapper execSellQueryList(const SellListQuery::Wrapper& query);
	SellDetailJsonVO::Wrapper execSellQueryDetail(const SellDetailQuery::Wrapper& query);
	SellAddJsonVO::Wrapper execSellAddList(const SellCreateDTO::Wrapper& dto);

	//模块2--慵懒的汪负责
	StringJsonVO::Wrapper executeModify(const SellUpdateDTO::Wrapper& dto, const PayloadDTO& payload);
	std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> executequerysimple(const SellListQuery::Wrapper& query);
	std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> executequerymore(const SellListQuery::Wrapper& query);

	SellGenerateReturnDTO::Wrapper execSellGenerateReturn(const oatpp::String& code);

	SellAuditJsonVO::Wrapper executeBatchApprove(const SellAuditDTO::Wrapper& dto);
	SellAuditJsonVO::Wrapper executeBatchUnapprove(const SellAuditDTO::Wrapper& dto);
};

#undef API_TAG_SELL

#include OATPP_CODEGEN_END(ApiController)

#endif