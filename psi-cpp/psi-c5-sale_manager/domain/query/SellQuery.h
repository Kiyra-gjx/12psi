#pragma once

//销售单

#ifndef _SELLQUERY_H_
#define _SELLQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h" 

#include OATPP_CODEGEN_BEGIN(DTO)

// 获取销售单列表（条件+分页）
class SellListQuery : public PageQuery
{

    DTO_INIT(SellListQuery, PageQuery);

    // 商品名称
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("goods.field.name"), false);

    // 单据编号
    API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("sell.field.number"), false);

    // 客户名称
    API_DTO_FIELD_REQUIRE(String, customer, ZH_WORDS_GETTER("sell.field.customer"), false);

    // 销售人员
    API_DTO_FIELD_REQUIRE(String, people, ZH_WORDS_GETTER("sell.field.people"), false);

    // 搜索开始时间
    API_DTO_FIELD_REQUIRE(String, begintime, ZH_WORDS_GETTER("sell.field.begintime"), false);

    // 搜索结束时间
    API_DTO_FIELD_REQUIRE(String, endtime, ZH_WORDS_GETTER("sell.field.endtime"), false);

    // 制单人
    API_DTO_FIELD_REQUIRE(String, user, ZH_WORDS_GETTER("sell.field.user"), false);

    // 审核状态 [0:未审核|1:已审核]
    API_DTO_FIELD_REQUIRE(Int32, examine, ZH_WORDS_GETTER("sell.field.examine"), false);

    // 核销状态 [0:未核销|1:部分核销|2:已核销]
    API_DTO_FIELD_REQUIRE(Int32, nucleus, ZH_WORDS_GETTER("sell.field.nucleus"), false);

    // 费用状态 [0:未结算|1:部分结算|2:已结算|3:无需结算]
    API_DTO_FIELD_REQUIRE(Int32, cse, ZH_WORDS_GETTER("sell.field.cse"), false);

    // 发票状态 [0:未开票|1:部分开票|2:已开票|3:无需开票]
    API_DTO_FIELD_REQUIRE(Int32, invoice, ZH_WORDS_GETTER("sell.field.invoice"), false);

    // 核对状态 [0:未核对|1:已核对]
    API_DTO_FIELD_REQUIRE(Int32, check, ZH_WORDS_GETTER("sell.field.check"), false);

    // 备注信息
    API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("sell.field.data"), false);

    // 时间排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, timeSortOrder, ZH_WORDS_GETTER("sell.sortOrder.time"), false);

    // 单据编号排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, numberSortOrder, ZH_WORDS_GETTER("sell.sortOrder.number"), false);

    // 单据金额排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, totalSortOrder, ZH_WORDS_GETTER("sell.sortOrder.total"), false);

    // 实际金额排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, actualSortOrder, ZH_WORDS_GETTER("sell.sortOrder.actual"), false);

    // 单据付款(实付金额)排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, moneySortOrder, ZH_WORDS_GETTER("sell.sortOrder.money"), false);

    // 单据费用排序方式[空:不排序|0:降序|1:升序]
    API_DTO_FIELD_REQUIRE(Boolean, costSortOrder, ZH_WORDS_GETTER("saleReturnOrder.sortOrder.cost"), false);
};

// 获取销售单详情
class SellDetailQuery : public oatpp::DTO
{

    DTO_INIT(SellDetailQuery, DTO);

    // 销售单 ID
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("sell.field.listid"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SELLQUERY_H_