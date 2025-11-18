#pragma once
#ifndef _DINGDANEXAMINEDTO_H_
#define _DINGDANEXAMINEDTO_H_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 订单审核数据传输模型
 */
class DingdanExamineDTO : public oatpp::DTO {
	DTO_INIT(DingdanExamineDTO, oatpp::DTO);

	// 订单ID列表（支持批量审核）
	API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("dingdan.examine.ids"));

	// 审核状态[1:审核通过|2:审核拒绝]
	API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("dingdan.examine.status"));

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANEXAMINEDTO_H_