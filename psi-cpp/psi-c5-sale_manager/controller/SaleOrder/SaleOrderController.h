#pragma once

#ifndef _SALEORDERCONTROLLER_H_
#define _SALEORDERCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "../../Macros.h"
#include "ServerInfo.h"
#include "domain/dto/SaleOrderListDTO.h"
#include "domain/query/SaleOrderListQuery.h"
#include "domain/vo/SaleOrderListVO.h"
#include"service/SorService/SorService.h"
#include "domain/vo/SellVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG_SALE_ORDER ZH_WORDS_GETTER("saleOrder.tag")

class SaleOrderController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(SaleOrderController);
public:
	//获取销售订单列表（条件+分页）描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.queryall"),
		queryAllSaleOrderList,
		SaleOrderListQuery,
		SaleOrderListPageJsonVO::Wrapper,
		API_TAG_SALE_ORDER
	);

	//获取销售订单列表（条件+分页）端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"/sor/List",
		queryAllSaleOrderList,
		SaleOrderListQuery,
		executeQueryAllSaleOrder(query)
	);

	//获取指定销售订单详情描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.querydetail"),
		queryOneSaleOrder,
		SaleOrderDetailJsonVO::Wrapper,
		API_TAG_SALE_ORDER
	);

	//获取指定销售订单详情端点
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/sor/detail",
		queryOneSaleOrder,
		QUERY(String, id),
		executeQuerySaleOrderDetail(id)
	);

	//定义描述：获得生成销售单数据
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.saleOrder.addSO_by_sale"),
		addSO_by_sale, StringJsonVO::Wrapper, API_TAG_SALE_ORDER);

	//定义端点：获得生成销售单数据
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sor/addSO-by-sale",
		addSO_by_sale, BODY_DTO(SellGenerateDTO::Wrapper, dto), executeAddSO(dto));


	//定义描述：获得生成采购订单数据
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.saleOrder.addPO_by_sale"),
		addPO_by_sale, StringJsonVO::Wrapper, API_TAG_SALE_ORDER);

	//定义端点：获得生成采购订单数据
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sor/addPO-by-sale",
		addPO_by_sale, BODY_DTO(PurchaseGenerateDTO::Wrapper, dto), executeAddPO(dto));

	//新增销售订单描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.addsaleorder"),
		addSaleOrder,
		StringJsonVO::Wrapper,
		API_TAG_SALE_ORDER,
		API_DEF_ADD_QUERY_PARAMS(
			String,
			"id",
			ZH_WORDS_GETTER("saleOrder.field.id"),
			"ae65c714d48d4f34b52479f5482c0edd",
			true
		);
	);

	//新增销售订单端点
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/sor/add",
		addSaleOrder,
		BODY_DTO(SaleOrderAddDTO::Wrapper, dto),
		executeAddSaleOrder(dto)
	);

	// 批量删除销售订单 - 描述
	ENDPOINT_INFO(batchDelete) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.saleOrder.delsaleorder");
		info->addTag(API_TAG_SALE_ORDER);
		info->addResponse<Object<SorDeleteResultVO>>(Status::CODE_200, "application/json");
	}
	// 批量删除销售订单 - 端点
	ENDPOINT(API_M_POST, "/sor/api/batch-delete", batchDelete,
		BODY_DTO(SorDeleteDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		// 调用模拟执行函数，并用 API_HANDLER_RESP_VO 包装返回
		API_HANDLER_RESP_VO(executeBatchDelete(dto));
	}

	// 批量审核销售订单
	ENDPOINT_INFO(batchApprove) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.saleOrder.review");
		info->addTag(API_TAG_SALE_ORDER);
		info->addResponse<Object<SorAuditResultVO>>(Status::CODE_200, "application/json");
	}
	ENDPOINT(API_M_POST, "/sor/api/batch-approve", batchApprove,
		BODY_DTO(SorAuditDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeBatchApprove(dto));
	}

	// 批量反审核销售订单
	ENDPOINT_INFO(batchUnapprove) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.saleOrder.counterreview");
		info->addTag(API_TAG_SALE_ORDER);
		info->addResponse<Object<SorAuditResultVO>>(Status::CODE_200, "application/json");
	}
	ENDPOINT(API_M_POST, "/sor/api/batch-unapprove", batchUnapprove,
		BODY_DTO(SorAuditDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeBatchUnapprove(dto));
	}

	// 修改销售订单描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.modifysaleorder"),
		updateSor,
		StringJsonVO::Wrapper,
		API_TAG_SALE_ORDER,
		);
	// 修改销售订单端点
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"/sor/update",
		updateSor,
		BODY_DTO(SorUpdateDTO::Wrapper, dto),
		executeUpdateSor(dto)
	);
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.exportsimple"),
		exportSimpleReport,
		SorExportSimpleQuery,
		ListJsonVO<SorExportSimpleQuery::Wrapper>::Wrapper,
		API_TAG_SALE_ORDER
	);
	// 导出简单报表端点
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/sor/export/simple",
		exportSimpleReport,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(usrQuery, SorExportSimpleQuery, queryParams);
		return executeExportSimple(usrQuery);
	);
	// 导出详细报表描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("summary.saleOrder.exportdetail"),
		exportDetailReport,
		SorExportDetailQuery,
		ListJsonVO<SorExportDetailQuery::Wrapper>::Wrapper,
		API_TAG_SALE_ORDER
	);
	// 导出详细报表端点
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,
		"/sor/export/detail",
		exportDetailReport,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(usrQuery, SorExportDetailQuery, queryParams);
	return executeExportDetail(usrQuery);
		);

	//导入数据，前端解析表格后发给后端
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("summary.sell.import"), modifySorImport, Boolean, API_TAG_SALE_ORDER);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sor/modifySorImport", modifySorImport, BODY_DTO(SorImportDTO::Wrapper, dto), execSorImport(authObject->getPayload(), dto));

private:
	//获取销售订单列表（条件+分页）执行函数
	SaleOrderListPageJsonVO::Wrapper executeQueryAllSaleOrder(const SaleOrderListQuery::Wrapper& query);
	//获取指定销售订单详情执行函数
	SaleOrderDetailJsonVO::Wrapper executeQuerySaleOrderDetail(const String& id);
	//获得生成销售单执行函数
	SO_by_saleJsonVO::Wrapper executeAddSO(const SellGenerateDTO::Wrapper& dto);
	//获得生成采购订单执行函数(待修改)
	PO_by_saleJsonVO::Wrapper executeAddPO(const PurchaseGenerateDTO::Wrapper& dto);
	//新增销售订单执行函数
	StringJsonVO::Wrapper executeAddSaleOrder(const SaleOrderAddDTO::Wrapper& dto);
	// 删除销售订单（支持批量）
	SorDeleteJsonVO::Wrapper executeBatchDelete(const SorDeleteDTO::Wrapper& dto);

	// 审核（支持批量）
	SorAuditJsonVO::Wrapper executeBatchApprove(const SorAuditDTO::Wrapper& dto);

	// 反审核（支持批量）
	SorAuditJsonVO::Wrapper executeBatchUnapprove(const SorAuditDTO::Wrapper& dto);
	// 修改销售订单执行函数
	StringJsonVO::Wrapper executeUpdateSor(const SorUpdateDTO::Wrapper& dto);
// 导出简单报表执行函数
	std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> executeExportSimple(const SorExportSimpleQuery::Wrapper& query);
	// 导出详细报表执行函数
	std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> executeExportDetail(const SorExportDetailQuery::Wrapper& query);
	//导入
	Boolean execSorImport(const PayloadDTO& payload,const SorImportDTO::Wrapper& dto);
};

#undef API_TAG_SALE_ORDER

#include OATPP_CODEGEN_END(ApiController)

#endif