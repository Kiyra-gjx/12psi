#include "stdafx.h"
#include "PurchaseDetailController.h"
#include "../service/PurchaseDetailService.h"
#include "ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

PurchaseDetailJsonVO::Wrapper PurchaseDetailController::executeQueryAll(const PurchaseDetailQuery::Wrapper& query)
{
	PurchaseDetailService service;
	// 查询数据
	auto result = service.PurchaseDetail(query);
	// 响应结果
	auto jvo = PurchaseDetailJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
