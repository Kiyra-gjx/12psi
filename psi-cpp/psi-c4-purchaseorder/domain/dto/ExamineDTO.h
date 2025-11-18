#pragma once
#ifndef _EXAMINE_DTO_H_
#define _EXAMINE_DTO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购单审核数据传输模型
 */
class ExamineDTO : public oatpp::DTO {
	DTO_INIT(ExamineDTO, DTO);

	// 主键ID
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("reviewRetrunOrder.field.id"), true);
	// 关联单据
	API_DTO_FIELD_REQUIRE(String, source, ZH_WORDS_GETTER("reviewRetrunOrder.field.source"), true);

	// 订单ID列表（支持批量审核）
	//API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("order.examine.ids"));

	// 审核状态[0:未审核|1:已审核]
	//API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("order.examine.status"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_EXAMINE_DTO_H_