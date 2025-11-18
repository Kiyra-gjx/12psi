#pragma once
#ifndef _RETURNORDERCHECKDTO_H_
#define _RETURNORDERCHECKDTO_H_
#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购退货单核对/反核对传输模型
 */
class returnordercheckDTO : public oatpp::DTO {
	DTO_INIT(returnordercheckDTO, DTO);

	// id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("returnorder.check.ids"));

	// 核对状态 0-反核对 1-核对
	API_DTO_FIELD_DEFAULT(Int32, check, ZH_WORDS_GETTER("returnorder.check.status"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_DINGDANEXAMINEDTO_H_