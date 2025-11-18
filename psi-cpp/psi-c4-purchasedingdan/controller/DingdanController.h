#pragma once
#ifndef _DINGDANCONTROLLER_H_
#define _DINGDANCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/DingdanVO.h"
#include "domain/dto/DingdanExamineDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchase.tag")

class DingdanController : public oatpp::web::server::api::ApiController {

	// 定义控制器访问接口
	API_ACCESS_DECLARE(DingdanController);
public: // 定义接口
	// 修改订单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dingdan.modify.summary"), modifyDingdan, StringJsonVO::Wrapper, API_TAG);
	// 修改订单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchasedingdan/modify", modifyDingdan, BODY_DTO(DingdanDetailDTO::Wrapper, dto), executeModifyDingdan(dto, authObject->getPayload()));
	// 审核和反审核订单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dingdan.examine.summary"), examineDingdan, StringJsonVO::Wrapper, API_TAG);
	// 审核和反审核订单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchasedingdan/examine", examineDingdan, BODY_DTO(DingdanExamineDTO::Wrapper, dto), execExamine(dto, authObject->getPayload()));
private: // 定义接口执行函数
	// 修改订单
	StringJsonVO::Wrapper executeModifyDingdan(const DingdanDetailDTO::Wrapper& dto, const PayloadDTO& payload);
	// 审核订单
	StringJsonVO::Wrapper execExamine(const DingdanExamineDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_DINGDANCONTROLLER_H_


