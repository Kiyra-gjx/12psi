#include "stdafx.h"
#include "PotableInfoController.h"
#include "ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "../service/PotableInfoService.h"

PotableInfoJsonVO::Wrapper PotableInfoController::execQueryPotableInfo(const PotableInfoQuery::Wrapper& query)
{
	PotableInfoService service;
	auto result = service.tableInfo(query);
	auto jvo = PotableInfoJsonVO::createShared();
	jvo->success(result);
	return jvo;
}