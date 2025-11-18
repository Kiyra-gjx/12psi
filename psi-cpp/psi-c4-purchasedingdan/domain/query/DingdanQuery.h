#pragma once
#ifndef _DINGDANQUERY_H_
#define _DINGDANQUERY_H_

#include "domain/query/PageQuery.h"
#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class DingdanQuery : public	PageQuery
{
	DTO_INIT(DingdanQuery, PageQuery);
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
	// 关联人员
	API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("dingdan.field.people"));
	// 到货时间
	API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("dingdan.field.arrival"));
	// 物流信息
	API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("dingdan.field.logistics"));
	// 单据附件
	API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("dingdan.field.file"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("dingdan.field.data"));
	// 审核状态
	API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("dingdan.field.examine"));
	// 入库状态
	API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("dingdan.field.state"));
	// 制单人
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("dingdan.field.user"));

};

#include OATPP_CODEGEN_END(DTO)

#endif //_DINGDANQUERY_H_
