#pragma once

//销售退货单
#ifndef _SRECONTROLLER_H_
#define _SRECONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/SaleReturnOrderQuery.h"
#include "domain/vo/SaleReturnOrderVO.h"
#include "domain/dto/SaleReturnOrderDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

//#define API_TAG ZH_WORDS_GETTER("saleReturnOrder.tag")
#define API_TAG_SALE_RETURN ZH_WORDS_GETTER("saleReturnOrder.tag")

//需求：需要定义两个GET，一个POST。
class SaleReturnOrderController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(SaleReturnOrderController);
	//1.定义接口描述
	// 1.1获取退货单列表
	ENDPOINT_INFO(querySreList) {
		//定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.saleReturnOrder.queryall"));
		//定义默认授权参数
		API_DEF_ADD_AUTH();
		//定义响应格式
		API_DEF_ADD_RSP_JSON_WRAPPER(SreListJsonVO);
		//定义标签
		API_DEF_ADD_TAG(API_TAG_SALE_RETURN);
		//定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		//定义其他查询参数描述
		//商品名称
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("goods.field.name"), "", false);
		//单据编号
		API_DEF_ADD_QUERY_PARAMS(String, "number", ZH_WORDS_GETTER("saleReturnOrder.field.number"), "", false);
		//客户
		API_DEF_ADD_QUERY_PARAMS(String, "customer", ZH_WORDS_GETTER("saleReturnOrder.field.customer"), "", false);
		//关联人员
		API_DEF_ADD_QUERY_PARAMS(String, "people", ZH_WORDS_GETTER("saleReturnOrder.field.people"), "", false);
		//搜索开始时间
		API_DEF_ADD_QUERY_PARAMS(String, "begintime", ZH_WORDS_GETTER("saleReturnOrder.field.begintime"), "2020-01-01", false);
		//搜索结束时间
		API_DEF_ADD_QUERY_PARAMS(String, "endtime", ZH_WORDS_GETTER("saleReturnOrder.field.endtime"), "2030-01-01", false);
		//制单人
		API_DEF_ADD_QUERY_PARAMS(String, "user", ZH_WORDS_GETTER("saleReturnOrder.field.user"), "", false);
		//审核状态[0:未审核|1:已审核]
		API_DEF_ADD_QUERY_PARAMS(Int8, "examine", ZH_WORDS_GETTER("saleReturnOrder.field.examine"), , false);
		//核销状态[0:未核销|1:部分核销|2:已核销]
		API_DEF_ADD_QUERY_PARAMS(Int8, "nucleus", ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"), , false);
		//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
		API_DEF_ADD_QUERY_PARAMS(Int8, "cse", ZH_WORDS_GETTER("saleReturnOrder.field.cse"), , false);
		//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
		API_DEF_ADD_QUERY_PARAMS(Int8, "invoice", ZH_WORDS_GETTER("saleReturnOrder.field.invoice"), , false);
		//核对状态[0:未核对|1:已核对]
		API_DEF_ADD_QUERY_PARAMS(Int8, "check", ZH_WORDS_GETTER("saleReturnOrder.field.check"), , false);
		//备注信息
		API_DEF_ADD_QUERY_PARAMS(String, "data", ZH_WORDS_GETTER("saleReturnOrder.field.data"), "", false);
		
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

	// 1.2获取退货单详情
	ENDPOINT_INFO(querySreDetail) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.saleReturnOrder.querydetail"));
		// 定义默认授权参数
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(SreDetailJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG_SALE_RETURN);
		// 定义查询参数-退货单id-listid
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("saleReturnOrder.field.listid"), "N", true);
	}

	// 1.3新增退货单
	ENDPOINT_INFO(sreAddList) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("summary.saleReturnOrder.addsalereturnorder"));
		// 定义默认授权参数
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(SreAddJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG_SALE_RETURN);
	}

public:// 2.定义查询接口

	// 2.1查询退货单列表
	ENDPOINT(API_M_GET, "/sre/list", querySreList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 将查询参数解析为SreListQuery
		API_HANDLER_QUERY_PARAM(sreListQuery, SreListQuery, queryParams);
		// 调用执行函数
		API_HANDLER_RESP_VO(execSreQueryList(sreListQuery));
	}

	// 2.2查询退货单详情
	ENDPOINT(API_M_GET, "/sre/detail", querySreDetail, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 将查询参数解析为SreDetailQuery
		API_HANDLER_QUERY_PARAM(sreDetailQuery, SreDetailQuery, queryParams);
		// 调用执行函数
		API_HANDLER_RESP_VO(execSreQueryDetail(sreDetailQuery));
	}

	// 2.3新增退货单
	ENDPOINT(API_M_POST, "/sre/add", sreAddList, BODY_DTO(SreAddDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		// 调用执行函数
		API_HANDLER_RESP_VO(execSreAddList(dto));
	}

	// 接口 1：修改销售退货单（POST 请求）
	// 接口描述（元信息定义：标题、端点名、返回值、标签）
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.modifysalereturnorder"),  // 多语言标题：“修改销售退货单”
		updateSre,                               // 端点函数唯一标识
		StringJsonVO::Wrapper,                   // 返回值类型：操作结果提示
		API_TAG_SALE_RETURN                                 // 模块标签
	);
	// 端点绑定（请求方法、路径、参数、执行逻辑）
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,                              // HTTP 方法：POST
		"/sre/update",                        // 接口路径
		updateSre,                               // 端点函数标识（与上面一致）
		BODY_DTO(SreUpdateDTO::Wrapper, sreUpdateDto),  // 请求体绑定 SreUpdateDTO
		executeUpdateSre(sreUpdateDto)           // 调用执行函数
	);

	// 接口 2：导出销售退货单简单报表（GET 请求）
// 接口描述（元信息定义：标题、端点名、查询DTO、返回值、标签）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.exportsimple"),  // 多语言标题：“导出简单报表”
		exportSreSimple,                               // 端点函数唯一标识
		SreExportSimpleQuery,                          // 查询参数 DTO 类型
		ListJsonVO<SreExportSimpleQuery::Wrapper>::Wrapper,  // 返回值类型：简单报表列表
		API_TAG_SALE_RETURN                                      // 模块标签
	);
	// 端点绑定（请求方法、路径、参数、执行逻辑）
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,                               // HTTP 方法：GET
		"/sre/export/simple",                 // 接口路径
		exportSreSimple,                         // 端点函数标识
		QUERIES(QueryParams, queryParams),       // 接收所有 URL 查询参数
		// 解析查询参数 + 调用执行函数
		API_HANDLER_QUERY_PARAM(userQuery, SreExportSimpleQuery, queryParams);
	return executeExportSreSimple(userQuery);
		);
	// 接口 3：导出销售退货单详细报表（GET 请求）
// 接口描述（元信息定义：标题、端点名、查询DTO、返回值、标签）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.exportdetail"),  // 多语言标题：“导出详细报表”
		exportSreDetail,                               // 端点函数唯一标识
		SreExportDetailQuery,                          // 查询参数 DTO 类型
		ListJsonVO<SreExportDetailQuery::Wrapper>::Wrapper,  // 返回值类型：详细报表列表
		API_TAG_SALE_RETURN                                      // 模块标签
	);
	// 端点绑定（请求方法、路径、参数、执行逻辑）
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_GET,                               // HTTP 方法：GET
		"/sre/export/detail",                 // 接口路径
		exportSreDetail,                         // 端点函数标识
		QUERIES(QueryParams, queryParams),       // 接收所有 URL 查询参数
		// 解析查询参数 + 调用执行函数
		API_HANDLER_QUERY_PARAM(userQuery, SreExportDetailQuery, queryParams);
	return executeExportSreDetail(userQuery);
		);

	// 核对/反核对销售退货单描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.check"),
		checkSre,
		BatchOperationVO::Wrapper,
		API_TAG_SALE_RETURN
	);
	// 核对/反核对销售退货单端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sre/check", checkSre, BODY_DTO(SreCheckDTO::Wrapper, dto), executeCheck(dto));

	// 批量审核销售退货单描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.review"),
		batchApprove,
		BatchOperationVO::Wrapper,
		API_TAG_SALE_RETURN
	);
	// 批量审核销售退货单端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sre/batch-approve", batchApprove,
		BODY_DTO(SaleReturnAuditDTO::Wrapper, dto),
		executeBatchApprove(dto)
	);

	// 批量反审核销售退货单描述  
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.counterreview"),
		batchUnapprove,
		BatchOperationVO::Wrapper,
		API_TAG_SALE_RETURN
	);
	// 批量反审核销售退货单端点  
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sre/batch-unapprove", batchUnapprove,
		BODY_DTO(SaleReturnAuditDTO::Wrapper, dto),
		executeBatchUnapprove(dto)
	);

	// 导入销售退货单数据描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("summary.saleReturnOrder.import"),
		importSre,
		ImportResultDTO::Wrapper,
		API_TAG_SALE_RETURN
	);
	// 导入销售退货单数据端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sre/import", importSre,
		BODY_DTO(SaleReturnBatchImportDTO::Wrapper, dto),
		executeImport(dto)
	);

	// 删除销售退货单
    //描述
	ENDPOINT_INFO(delSaleReturn) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("summary.saleReturnOrder.delsalereturnorder");
		info->addTag(API_TAG_SALE_RETURN);
		info->addResponse<Object<DelSaleReturnResultVO>>(Status::CODE_200, "application/json");
	}
	//实现
	ENDPOINT(API_M_POST, "/sre/delete", delSaleReturn,
		BODY_DTO(DelSaleReturnDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(DelSaleReturn(dto));
	}

private://3.定义接口执行函数

	//3.1退货单分页查询数据
	SreListJsonVO::Wrapper execSreQueryList(const SreListQuery::Wrapper& query);

	//3.2退货单详情查询数据
	SreDetailJsonVO::Wrapper execSreQueryDetail(const SreDetailQuery::Wrapper& query);

	//3.3新增退货单
	SreAddJsonVO::Wrapper execSreAddList(const SreAddDTO::Wrapper& dto);

	// 接口执行函数声明（空实现）返回“字符串类型”的响应
	StringJsonVO::Wrapper executeUpdateSre(const SreUpdateDTO::Wrapper& sreUpdateDto);

	std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> executeExportSreSimple(const SreExportSimpleQuery::Wrapper& query);

	std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> executeExportSreDetail(const  SreExportDetailQuery::Wrapper& query);

	//审核
	BatchOperationVO::Wrapper executeBatchApprove(const SaleReturnAuditDTO::Wrapper& dto);

	//反审核
	BatchOperationVO::Wrapper executeBatchUnapprove(const SaleReturnAuditDTO::Wrapper& dto);

	//数据导入
	ImportResultDTO::Wrapper executeImport(const SaleReturnBatchImportDTO::Wrapper& dto);

	BatchOperationVO::Wrapper executeCheck(const SreCheckDTO::Wrapper& dto);

	DelSaleReturnResultVO::Wrapper DelSaleReturn(const DelSaleReturnDTO::Wrapper& dto);
};

#undef API_TAG_SALE_RETURN

#include OATPP_CODEGEN_END(ApiController)

#endif