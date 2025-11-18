#pragma once

//销售退货单
#ifndef _SALERETURNORDERQUERY_H_
#define _SALERETURNORDERQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 获取销售退货单列表（条件+分页）
class SreListQuery : public PageQuery {

	DTO_INIT(SreListQuery, PageQuery);

	//商品名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("goods.field.name"), false);
	//单据编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("saleReturnOrder.field.number"), false);
	//客户
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleReturnOrder.field.customer"), false);
	//关联人员
	API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("saleReturnOrder.field.people"), false);
	//搜索开始时间
	API_DTO_FIELD_REQUIRE(String, begintime, ZH_WORDS_GETTER("saleReturnOrder.field.begintime"), false);
	//搜索结束时间
	API_DTO_FIELD_REQUIRE(String, endtime, ZH_WORDS_GETTER("saleReturnOrder.field.endtime"), false);
	//制单人
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("saleReturnOrder.field.user"), false);
	//审核状态[0:未审核|1:已审核]
	API_DTO_FIELD_REQUIRE(Int8, examine, ZH_WORDS_GETTER("saleReturnOrder.field.examine"), false);
	//核销状态[0:未核销|1:部分核销|2:已核销]
	API_DTO_FIELD_REQUIRE(Int8, nucleus, ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"), false);
	//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
	API_DTO_FIELD_REQUIRE(Int8, cse, ZH_WORDS_GETTER("saleReturnOrder.field.cse"), false);
	//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
	API_DTO_FIELD_REQUIRE(Int8, invoice, ZH_WORDS_GETTER("saleReturnOrder.field.invoice"), false);
	//核对状态[0:未核对|1:已核对]
	API_DTO_FIELD_REQUIRE(Int8, check, ZH_WORDS_GETTER("saleReturnOrder.field.check"), false);
	//备注信息
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("saleReturnOrder.field.data"), false);
	//查询结果的排序
	//时间排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, timeSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.time"), false);
	//单据编号排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, numberSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.number"), false);
	//单据金额排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, totalSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.total"), false);
	//实际金额排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, actualSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.actual"), false);
	//单据付款(实付金额)排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, moneySortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.money"), false);
	//单据费用排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, costSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.cost"), false);
};

// 获取退货单详情
class SreDetailQuery : public oatpp::DTO {

	DTO_INIT(SreDetailQuery, DTO);

	// 退货单id
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("saleReturnOrder.field.listid"), true);
};

// 销售退货单更新记录查询
class UpdateSreQuery : public PageQuery {
	DTO_INIT(UpdateSreQuery, PageQuery)

	// 这里放置您之前在 SreQuery 中自己负责的代码部分
	// 例如：
	DTO_FIELD(String, orderNo) = "";               // 退货单号（模糊查询）
	DTO_FIELD(String, customerName) = "";          // 客户名称（模糊查询）
	DTO_FIELD(String, productName) = "";           // 产品名称（模糊查询）

	// 时间范围
	DTO_FIELD(String, startDate) = "";             // 开始日期（YYYY-MM-DD）
	DTO_FIELD(String, endDate) = "";               // 结束日期（YYYY-MM-DD）

	// 状态筛选
	DTO_FIELD(Int32, auditStatus) = -1;            // 审核状态：-1-全部 0-未审核 1-已审核
};

#include OATPP_CODEGEN_END(DTO)

#endif