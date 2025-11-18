#pragma once

#ifndef _SALEORDERLISTQUERY_H_
#define _SALEORDERLISTQUERY_H_

#include"../GlobalInclude.h"
#include"domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class SaleOrderListQuery : public PageQuery{
	DTO_INIT(SaleOrderListQuery, PageQuery);
	
	//商品名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("goods.field.name"), false);
	//单据编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("saleOrder.field.number"), false);
	//客户
	API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("saleOrder.field.customer"), false);
	//关联人员
	API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("saleOrder.field.people"), false);
	//搜索开始时间
	API_DTO_FIELD_REQUIRE(String, begintime, ZH_WORDS_GETTER("saleOrder.field.begintime"), false);
	//搜索结束时间
	API_DTO_FIELD_REQUIRE(String, endtime, ZH_WORDS_GETTER("salenOrder.field.endtime"), false);
	//制单人
	API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("saleOrder.field.user"), false);
	//审核状态[0:未审核|1:已审核]
	API_DTO_FIELD_REQUIRE(Int8, examine, ZH_WORDS_GETTER("saleOrder.field.examine"), false);
	//核销状态[0:未核销|1:部分核销|2:已核销]
	API_DTO_FIELD_REQUIRE(Int8, nucleus, ZH_WORDS_GETTER("saleOrder.field.nucleus"), false);
	//费用状态[0:未结算|1:部分解释|2:已结算|3:无需结算]
	API_DTO_FIELD_REQUIRE(Int8, cse, ZH_WORDS_GETTER("saleOrder.field.cse"), false);
	//发票状态[0:未开票|1:部分开票|2:已开票|3:无需开票]
	API_DTO_FIELD_REQUIRE(Int8, invoice, ZH_WORDS_GETTER("saleOrder.field.invoice"), false);
	//核对状态[0:未核对|1:已核对]
	API_DTO_FIELD_REQUIRE(Int8, check, ZH_WORDS_GETTER("saleOrder.field.check"), false);
	//备注信息
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("saleOrder.field.data"), false);
	//查询结果的排序
	//时间排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, timeSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.time"), false);
	//单据编号排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, numberSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.number"), false);
	//单据金额排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, totalSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.total"), false);
	//实际金额排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, actualSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.actual"), false);
	//单据付款(实付金额)排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, moneySortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.money"), false);
	//单据费用排序方式(空:不排序|0:降序|1:升序)
	API_DTO_FIELD_REQUIRE(Boolean, costSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.cost"), false);
	//到货日期排序方式
	API_DTO_FIELD_REQUIRE(Boolean, arrivalSortOrder, ZH_WORDS_GETTER("saleOrder.sortOrder.arrival"), false);
};

class SellGenerateQuery : PageQuery
{
	DTO_INIT(SellGenerateQuery, PageQuery);

	/*
		这个功能并不需要输入完整的销售订单，因为生成的也不是完整销售单
		输入的是销售订单详情表数据（在前端展示的数据）
	*/
	// PID
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("SorInfo.field.id"));
	// 所属商品
	API_DTO_FIELD_DEFAULT(String, goods, ZH_WORDS_GETTER("SorInfo.field.goods"));
	// 单位
	API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("SorInfo.field.unit"));
	// 仓库
	API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("SorInfo.field.warehouse"));
	// 单价
	API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("SorInfo.field.price"));
	// 数量
	API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("SorInfo.field.nums"));
	// 金额
	API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("SorInfo.field.total"));

};


#include OATPP_CODEGEN_END(DTO)

#endif