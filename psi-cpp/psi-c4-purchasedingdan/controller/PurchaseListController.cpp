#include "stdafx.h"
#include "PurchaseListController.h"
#include "../service/PurchaseListService.h"
#include "ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

PurchseListJsonVO::Wrapper PurchaseListController::executeQueryAll(const PurchaseListQuery::Wrapper& query)
{
	PurchaseListService service;
	// 查询数据
	auto result = service.listAll(query);
	// 响应结果
	auto jvo = PurchseListJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
