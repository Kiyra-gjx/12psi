#pragma once

#ifndef _SorInfo_QUERY_
#define _SorInfo_QUERY_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	销售订单详情查询对象
*/
class SorInfoQuery : public PageQuery
{
	DTO_INIT(SorInfoQuery, PageQuery);
	// ID
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.id");
	}
	// ID
	DTO_FIELD(String, pid);
	DTO_FIELD_INFO(pid) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.pid");
	}
	// ID
	DTO_FIELD(String, goods);
	DTO_FIELD_INFO(goods) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.goods");
	}
	// ID
	DTO_FIELD(String, addr);
	DTO_FIELD_INFO(addr) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.addr");
	}
	// ID
	DTO_FIELD(String, unit);
	DTO_FIELD_INFO(unit) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.unit");
	}
	// ID
	DTO_FIELD(String, warehouse);
	DTO_FIELD_INFO(warehouse) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.warehouse");
	}
	// ID
	DTO_FIELD(String, price);
	DTO_FIELD_INFO(price) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.price");
	}
	// ID
	DTO_FIELD(String, nums);
	DTO_FIELD_INFO(nums) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.nums");
	}
	// ID
	DTO_FIELD(String, discount);
	DTO_FIELD_INFO(discount) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.discount");
	}
	// ID
	DTO_FIELD(String, dsc);
	DTO_FIELD_INFO(dsc) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.dsc");
	}
	// ID
	DTO_FIELD(String, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.total");
	}
	// ID
	DTO_FIELD(String, tax);
	DTO_FIELD_INFO(tax) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.tax");
	}
	// ID
	DTO_FIELD(String, tat);
	DTO_FIELD_INFO(tat) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.tat");
	}
	// ID
	DTO_FIELD(String, tpt);
	DTO_FIELD_INFO(tpt) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.tpt");
	}
	// ID
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.data");
	}
	// ID
	DTO_FIELD(String, handle);
	DTO_FIELD_INFO(handle) {
		info->description = ZH_WORDS_GETTER("SorInfo.field.handle");
	}
			
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SorInfo_QUERY_
