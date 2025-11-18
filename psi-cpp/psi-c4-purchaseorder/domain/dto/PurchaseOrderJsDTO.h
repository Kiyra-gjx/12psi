#pragma once
#ifndef _PURCHASEORDERJDTO_H_
#define _PURCHASEORDERJDTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购单中的"一行商品"数据模型
 */
class PurchaseInfoDTO : public oatpp::DTO {
	DTO_INIT(PurchaseInfoDTO, DTO);

	// 商品id
	API_DTO_FIELD_REQUIRE(String, goods_id, ZH_WORDS_GETTER("js.goods.id"), true);
	// 仓库id
	API_DTO_FIELD_REQUIRE(String, warehouse_id, ZH_WORDS_GETTER("js.warehouse.id"), true);
	// 单价 (对应 BuyInfoDO.price)
	API_DTO_FIELD_REQUIRE(Float64, unit_price, ZH_WORDS_GETTER("js.goods.buy"), true);
	// 数量 (对应 BuyInfoDO.nums)
	API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("js.goods.number"), true);
};

/**
 * 新增采购单数据传输模型 (主DTO)
 */
class OrderAddDTO : public oatpp::DTO
{
	DTO_INIT(OrderAddDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, buy_supplier, ZH_WORDS_GETTER("js.buy.supplier"), true);
	API_DTO_FIELD_REQUIRE(String, buy_time, ZH_WORDS_GETTER("js.buy.time"), true); 
	API_DTO_FIELD_REQUIRE(String, buy_number, ZH_WORDS_GETTER("js.buy.number"), true);
	API_DTO_FIELD_REQUIRE(Float64, buy_total, ZH_WORDS_GETTER("js.buy.total"), true);
	API_DTO_FIELD_REQUIRE(Float64, buy_actual, ZH_WORDS_GETTER("js.buy.actual"), true);
	API_DTO_FIELD_REQUIRE(Float64, buy_money, ZH_WORDS_GETTER("js.buy.money"), true);
	API_DTO_FIELD_REQUIRE(Float64, buy_cost, ZH_WORDS_GETTER("js.buy.cost"), true);
	API_DTO_FIELD_REQUIRE(String, buy_account, ZH_WORDS_GETTER("js.buy.account"), true);
	API_DTO_FIELD_REQUIRE(String, buy_people, ZH_WORDS_GETTER("js.buy.people"), false);
	API_DTO_FIELD_REQUIRE(String, buy_logistics, ZH_WORDS_GETTER("js.buy.logistics"), false);
	API_DTO_FIELD_REQUIRE(String, buy_data, ZH_WORDS_GETTER("js.buy.data"), false);
	API_DTO_FIELD_REQUIRE(String, buy_user, ZH_WORDS_GETTER("js.buy.user"), true);
	API_DTO_FIELD_REQUIRE(Vector<Object<PurchaseInfoDTO>>, items, "商品明细列表", true);

public:
	// 给单据时间添加一个构造函数来设置默认值
	OrderAddDTO() {
		buy_time = "YYYY-MM-DD";
	}
};

/**
 * 删除采购单，支持批量删除
 */
class OrderDeleteDTO : public oatpp::DTO {
	DTO_INIT(OrderDeleteDTO, DTO);
	// 使用 OATPP 列表类型
	DTO_FIELD(oatpp::List<oatpp::String>::ObjectWrapper, ids);
	DTO_FIELD_INFO(ids) {
		info->description = ZH_WORDS_GETTER("js.buy.delete.ids");
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASEORDERJDTO_H_