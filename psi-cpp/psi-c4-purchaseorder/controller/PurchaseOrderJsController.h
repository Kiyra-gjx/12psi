#pragma once
#ifndef _PURCHASEORDERJSCONTROLLER_H_
#define _PURCHASEORDERJSCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/PurchaseOrderJsDTO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
#define API_TAG ZH_WORDS_GETTER("purchaseorder.tag")

class PurchaseOrderJsController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(PurchaseOrderJsController);
public://定义接口

	// 新增采购单接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("js.buy.add.name"), addOrder, StringJsonVO::Wrapper, API_TAG);
	// 新增采购单接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/purchaseorder/add", addOrder, BODY_DTO(OrderAddDTO::Wrapper, dto), executeAddJsOrder(dto));

	//删除采购单接口描述
	ENDPOINT_INFO(removeOrder) {
		API_DEF_ADD_COMMON_AUTH(ZH_WORDS_GETTER("js.buy.delete.name"), StringJsonVO::Wrapper, API_TAG);
		info->addConsumes<Object<OrderDeleteDTO>>("application/json");
	}
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/purchaseorder/remove", removeOrder,
		BODY_DTO(OrderDeleteDTO::Wrapper, dto), execRemoveJsOrder(dto));

private://定义接口执行函数
	
	// 新增采购单
	StringJsonVO::Wrapper executeAddJsOrder(const OrderAddDTO::Wrapper& dto);

	// 删除采购单
	StringJsonVO::Wrapper execRemoveJsOrder(const OrderDeleteDTO::Wrapper& dto);
};

#undef API_TAG

// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _PURCHASEORDERJSCONTROLLER_H_