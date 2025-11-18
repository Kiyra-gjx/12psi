#ifndef _PURCHASELISTVO_H_
#define _PURCHASELISTVO_H_

#include "../GlobalInclude.h"
#include "../dto/PurchaseListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单分页显示JJsonVO，用于响应给客户端的Json对象
 */
class PurchseListJsonVO : public JsonVO<PurchaseListPageDTO::Wrapper> {
	DTO_INIT(PurchseListJsonVO, JsonVO<PurchaseListPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)



#endif // !_PURCHASELISTVO_H_