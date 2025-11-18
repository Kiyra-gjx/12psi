#pragma once
#ifndef _OrderVO_H_
#define _OrderVO_H_

#include "../GlobalInclude.h"
#include "../dto/OrderDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单列表分页显示JsonVO
 */
class OrderListPageJsonVO : public JsonVO<OrderListPageDTO::Wrapper> {
	DTO_INIT(OrderListPageJsonVO, JsonVO<OrderListPageDTO::Wrapper>);
};

/**
 * 采购订单详情显示JsonVO
 */
class OrderDetailJsonVO : public JsonVO<OrderDetailDTO::Wrapper> {
	DTO_INIT(OrderDetailJsonVO, JsonVO<OrderDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OrderVO_H_
