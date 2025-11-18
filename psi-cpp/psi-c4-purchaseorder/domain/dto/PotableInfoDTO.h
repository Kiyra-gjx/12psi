#pragma once
#ifndef POTABLE_INFO__DTO
#define POTABLE_INFO__DTO
#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Potable_InfoDTO :public oatpp::DTO
{
	DTO_INIT(Potable_InfoDTO, oatpp::DTO);

	//商品名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("potable.is_goods.name");
	}

	//辅助属性
	DTO_FIELD(String,attr);
	DTO_FIELD_INFO(attr) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.attr");
	}

	//单位
	DTO_FIELD(String, unit);
	DTO_FIELD_INFO(unit) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.unit");
	}

	//仓库
	DTO_FIELD(String, warehouse);
	DTO_FIELD_INFO(warehouse) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.warehouse");
	}

	//单价
	DTO_FIELD(Float64, price);
	DTO_FIELD_INFO(price) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.price");
	}

	//数量
	DTO_FIELD(Float64, nums);
	DTO_FIELD_INFO(nums) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.nums");
	}

	//折扣率
	DTO_FIELD(Float64, discount);
	DTO_FIELD_INFO(discount) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.discount");
	}

	//折扣额
	DTO_FIELD(Float64, dsc);
	DTO_FIELD_INFO(dsc) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.dsc");
	}

	//金额
	DTO_FIELD(Float64, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.total");
	}
	//备注
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("potable.is_buy_info.data");
	}
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};
class PotableInfoDTO :public oatpp::DTO
{
	DTO_INIT(PotableInfoDTO, oatpp::DTO);
	DTO_FIELD(List<Potable_InfoDTO::Wrapper>,rows);
	void addData(Potable_InfoDTO::Wrapper one) {
		this->rows->push_back(one);
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif