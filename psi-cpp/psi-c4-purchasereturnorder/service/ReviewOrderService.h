#pragma once


#ifndef _REVIEWORDER_SERVICE_
#define _REVIEWORDER_SERVICE_
#include "domain/dto/ReviewDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"

/**
 * 审核订单服务实现，演示基础的审核订单服务实现
 */
class ReviewOrderService
{

public:

	// 根据ID修改采购退货单的审核状态
	vector<pair<bool, string>> reviewOrder(const List<ReviewDTO::Wrapper>& dtos);

};

#endif // !_REVIEWORDER_SERVICE_