#pragma once
#ifndef _ORDERQUERY_H_
#define _ORDERQUERY_H_

#include "domain/query/PageQuery.h"
#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class OrderQuery : public	PageQuery
{
	DTO_INIT(OrderQuery, PageQuery);
	// 关联单据
	API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("dingdan.field.source"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("dingdan.field.frame"));
	// 供应商
	API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("dingdan.field.supplier"));
	// 单据时间
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("dingdan.field.time"));
	// 单据编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("dingdan.field.number"));
	// 单据金额
	API_DTO_FIELD_DEFAULT(String, total, ZH_WORDS_GETTER("dingdan.field.total"));
	// 实际金额
	API_DTO_FIELD_DEFAULT(String, actual, ZH_WORDS_GETTER("dingdan.field.actual"));
	// 实付金额
	API_DTO_FIELD_DEFAULT(String, money, ZH_WORDS_GETTER("dingdan.field.money"));
	// 单据费用
	API_DTO_FIELD_DEFAULT(String, cost, ZH_WORDS_GETTER("dingdan.field.cost"));
	// 结算账户
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("dingdan.field.account"));
	// 关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("dingdan.field.people"));
	// 物流信息
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("dingdan.field.logistics"));
	// 单据附件
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("dingdan.field.file"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("dingdan.field.data"));
	// 扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("dingdan.field.more"));
	// 审核状态
	API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("dingdan.field.examine"));
	// 核销状态
	API_DTO_FIELD_DEFAULT(Int32, nucleus, ZH_WORDS_GETTER("dingdan.field.nucleus"));
	// 费用状态
	API_DTO_FIELD_DEFAULT(Int32, cse, ZH_WORDS_GETTER("dingdan.field.cse"));
	// 发票状态
	API_DTO_FIELD_DEFAULT(Int32, invoice, ZH_WORDS_GETTER("dingdan.field.invoice"));
	// 核对状态
	API_DTO_FIELD_DEFAULT(Int32, check, ZH_WORDS_GETTER("dingdan.field.check"));
	// 制单人
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("dingdan.field.user"));


};

#include OATPP_CODEGEN_END(DTO)

#endif  // _ORDERQUERY_H_

