#pragma once

#ifndef _REVIEWRETRUNORDER_CONTROLLER_
#define _REVIEWRETRUNORDER_CONTROLLER_

#include "domain/dto/ReviewDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchasereturnorder.tag")


class ReviewOrderController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(ReviewOrderController);
public: // 定义接口

	// 审核/反审核接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("reviewRetrunOrder.review.summary"), reviewOrder, ListJsonVO<String>::Wrapper, API_TAG);
	// 审核反审核接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/purchasereturnorder/review", reviewOrder, BODY_DTO(List<ReviewDTO::Wrapper>, dtos), execReviewOrder(dtos));


private: // 定义接口执行函数


	// 审核/反审核函数实现
	ListJsonVO<String>::Wrapper execReviewOrder(const List<ReviewDTO::Wrapper>& dtos);

};


#undef API_TAG


#include OATPP_CODEGEN_END(ApiController)

#endif // !_IMPORTEXCELCONTROLLER_H_