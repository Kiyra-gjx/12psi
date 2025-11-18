#pragma once
#ifndef _RETURNORDERCONTROLLER_H_
#define _RETURNORDERCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/ReturnOrderVO.h"
#include "domain/dto/ReturnOrderCheckDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchasereturnorder.tag")

class returnorderController : public oatpp::web::server::api::ApiController {

	// 定义控制器访问接口
	API_ACCESS_DECLARE(returnorderController);
public:

	// 修改采购退货单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("returnorder.modify.summary"), modifyreturnorder, StringJsonVO::Wrapper, API_TAG);
	// 修改采购退货单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchasereturnorder/modify", modifyreturnorder, BODY_DTO(returnorderDetailDTO::Wrapper, dto), Modifyreturnorder(dto));

	// 核对/反核对采购退货单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("returnorder.check.summary"), checkreturnorder, StringJsonVO::Wrapper, API_TAG);
	// 核对/反核对采购退货单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchasereturnorder/check", checkreturnorder, BODY_DTO(returnordercheckDTO::Wrapper, dto), Modifycheck(dto));


private:

	// 修改采购退货单
	StringJsonVO::Wrapper Modifyreturnorder(const returnorderDetailDTO::Wrapper& dto);
	// 核对/反核对采购退货单
	StringJsonVO::Wrapper Modifycheck(const returnordercheckDTO::Wrapper& dto);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_DINGDANCONTROLLER_H_


