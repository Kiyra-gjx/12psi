#pragma once
#ifndef POTABLE_DTO
#define POTABLE_DTO
#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
//采购单列表查询类
class PotableDTO :public oatpp::DTO
{
	DTO_INIT(PotableDTO, oatpp::DTO);

	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = "id";
	}

	//所属组织
	DTO_FIELD(String, frame);
	DTO_FIELD_INFO(frame) {
		info->description = ZH_WORDS_GETTER("potable.is_goods.frame");
	}

	//单据编号
	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.number");
	}

	//供应商
	DTO_FIELD(String, supplier);
	DTO_FIELD_INFO(supplier) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.supplier");
	}

	//制单人
	DTO_FIELD(String, user);
	DTO_FIELD_INFO(user) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.user");
	}

	//单据时间
	DTO_FIELD(String, time);
	DTO_FIELD_INFO(time) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.time");
	}

	//单据金额
	DTO_FIELD(Float64, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.total");
	}

	//实际金额
	DTO_FIELD(Float64, actual);
	DTO_FIELD_INFO(actual) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.actual");
	}

	//实付金额
	DTO_FIELD(Float64, money);
	DTO_FIELD_INFO(money) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.money");
	}

	//单据费用
	DTO_FIELD(Float64, cost);
	DTO_FIELD_INFO(cost) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.cost");
	}

	//关联人员
	DTO_FIELD(String, people);
	DTO_FIELD_INFO(people) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.people");
	}

	//审核状态(0:未审核,1:已审核)
	DTO_FIELD(Int32, examine);
	DTO_FIELD_INFO(examine) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.examine");
	}

	//核销状态(0:未核销,1:部分核销,2：已核销)
	DTO_FIELD(Int32, nucleus);
	DTO_FIELD_INFO(nucleus) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.nucleus");
	}

	//费用状态(0:未结算,1:部分核算,2：已结算,3:无需核算)
	DTO_FIELD(Int32, cse);
	DTO_FIELD_INFO(cse) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.cse");
	}

	//发票状态(0:未开票,1:部分开票,2：已开票,3:无需开票)
	DTO_FIELD(Int32, invoice);
	DTO_FIELD_INFO(invoice) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.invoice");
	}

	//核对状态(0:未核对,1:已核对)
	DTO_FIELD(Int32, check);
	DTO_FIELD_INFO(check) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.check");
	}

	//备注信息
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.data");
	}

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};
//采购单列表分页查询类
class PotablePageDTO :public PageDTO<PotableDTO::Wrapper>
{
	DTO_INIT(PotablePageDTO, PageDTO<PotableDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif
