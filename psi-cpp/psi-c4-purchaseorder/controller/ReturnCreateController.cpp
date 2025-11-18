#include "stdafx.h"
#include "./ReturnCreateController.h"
#include "ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "../service/PotableInfoService.h"

PotableInfoJsonVO::Wrapper ReturnCreateController::execQueryPotableInfo(const PotableInfoQuery::Wrapper& query)
{
	PotableInfoService service;
	auto result = service.tableInfo(query);
	auto jvo = PotableInfoJsonVO::createShared();
	jvo->success(result);
	return jvo;
}