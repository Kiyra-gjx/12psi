#ifndef _PURCHASEDETAILVO_H_
#define _PURCHASEDETAILVO_H_

#include "../GlobalInclude.h"
#include "../dto/PurchaseDetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单详情显示JsonVO，用于响应给客户端的Json对象
 */
class PurchaseDetailJsonVO : public JsonVO<PurchaseDetailDTO::Wrapper> {
	DTO_INIT(PurchaseDetailJsonVO, JsonVO<PurchaseDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASEDETAILVO_H_