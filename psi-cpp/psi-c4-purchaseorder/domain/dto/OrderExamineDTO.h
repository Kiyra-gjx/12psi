#pragma once
#ifndef _ORDEREXAMINEDTO_H_
#define _ORDEREXAMINEDTO_H_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 订单核对数据传输模型
 */
class OrderExamineDTO : public oatpp::DTO {
	DTO_INIT(OrderExamineDTO, DTO);

	// 订单ID列表（支持批量核对）
	API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("dingdan.examine.ids"));

	// 核对状态 [1:核对通过|2:核对拒绝]
	API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("dingdan.examine.status"));

	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANEXAMINEDTO_H_