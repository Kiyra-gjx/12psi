#pragma once
#ifndef _GET_PO_TABLE_QUERY_
#define _GET_PO_TABLE_QUERY_
#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)


//分页条件获取采购单列表对象
class PotableQuery: public PageQuery
{
	DTO_INIT(PotableQuery,PageQuery);
	
	//商品名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name){
		info->description = ZH_WORDS_GETTER("potable.is_goods.name");
	}

	//单据编号
	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number){
		info->description = ZH_WORDS_GETTER("potable.is_buy.number");
	}

	//供应商
	DTO_FIELD(String, supplier);
	DTO_FIELD_INFO(supplier) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.supplier");
	}

	//制单人
	DTO_FIELD(String, user);
	DTO_FIELD_INFO(user){
		info->description = ZH_WORDS_GETTER("potable.is_buy.user");
	}

	//开始时间
	DTO_FIELD(String, s_time);
	DTO_FIELD_INFO(s_time) {
		info->description = ZH_WORDS_GETTER("potable.is_buy.s_time");
	}

	//结束时间
	DTO_FIELD(String, e_time);
	DTO_FIELD_INFO(e_time){
		info->description = ZH_WORDS_GETTER("potable.is_buy.e_time");
	}

	//关联人员
	DTO_FIELD(String, people);
	DTO_FIELD_INFO(people){
		info->description = ZH_WORDS_GETTER("potable.is_buy.people");
	}

	//审核状态(0:未审核,1:已审核)
	DTO_FIELD(Int32, examine);
	DTO_FIELD_INFO(examine){
		info->description = ZH_WORDS_GETTER("potable.is_buy.examine");
	}

	//核销状态(0:未核销,1:部分核销,2：已核销)
	DTO_FIELD(Int32, nucleus);
	DTO_FIELD_INFO(nucleus){
		info->description = ZH_WORDS_GETTER("potable.is_buy.nucleus");
	}

	//费用状态(0:未结算,1:部分核算,2：已结算,3:无需核算)
	DTO_FIELD(Int32, cse);
	DTO_FIELD_INFO(cse){
		info->description = ZH_WORDS_GETTER("potable.is_buy.cse");
	}

	//发票状态(0:未开票,1:部分开票,2：已开票,3:无需开票)
	DTO_FIELD(Int32, invoice);
	DTO_FIELD_INFO(invoice){
		info->description = ZH_WORDS_GETTER("potable.is_buy.invoice");
	}

	//核对状态(0:未核对,1:已核对)
	DTO_FIELD(Int32, check);
	DTO_FIELD_INFO(check){
		info->description = ZH_WORDS_GETTER("potable.is_buy.check");
	}

	//备注信息
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data){
		info->description = ZH_WORDS_GETTER("potable.is_buy.data");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PURCHASEORDER_QUERY_
