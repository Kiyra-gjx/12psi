#pragma once
#ifndef _ORDERCONTROLLER_H_
#define _ORDERCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/query/OrderQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/OrderVO.h"
#include "domain/dto/OrderExamineDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

class OrderController : public oatpp::web::server::api::ApiController {

	// 定义控制器访问接口
	API_ACCESS_DECLARE(OrderController);
public: // 定义接口

	// 修改订单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dingdan.modify.summary"), modifyDingdan, StringJsonVO::Wrapper, API_TAG);
	// 修改订单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchaseorder/modify", modifyDingdan, BODY_DTO(OrderDetailDTO::Wrapper, dto), executeModifyDingdan(dto));
	// 核对/反核对订单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dingdan.examine.summary"), examineDingdan, StringJsonVO::Wrapper, API_TAG);
	// 核对/反核对订单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchaseorder/examine", examineDingdan, BODY_DTO(OrderExamineDTO::Wrapper, dto), execExamine(dto));

private: // 定义接口执行函数

	// 修改订单
	StringJsonVO::Wrapper executeModifyDingdan(const OrderDetailDTO::Wrapper& dto);
	// 核对/反核对订单
	StringJsonVO::Wrapper execExamine(const OrderExamineDTO::Wrapper& dto);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_DINGDANCONTROLLER_H_


