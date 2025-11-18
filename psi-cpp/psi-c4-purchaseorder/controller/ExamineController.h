#pragma once
#ifndef _EXAMINE_CONTROLLER_H_
#define _EXAMINE_CONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/ExamineDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

class ExamineController : public oatpp::web::server::api::ApiController {

	// 定义控制器访问接口
	API_ACCESS_DECLARE(ExamineController);
public: // 定义接口
	// 审核/反审核采购单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("order.examine.summary"), examineorder, StringJsonVO::Wrapper, API_TAG);
	// 审核/反审核采购单接口端点                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchaseorder/examine", examineorder, BODY_DTO(ExamineDTO::Wrapper, dto), execExamine(dto));
private:
	// 审核/反审核采购单
	StringJsonVO::Wrapper execExamine(const ExamineDTO::Wrapper& dto);
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_EXAMINE_CONTROLLER_H_

