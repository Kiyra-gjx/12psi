#include "stdafx.h"
#include "PotableController.h"
#include "ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "../service/PotableService.h"

PotableJsonVO::Wrapper PotableController::execQueryPotable(const PotableQuery::Wrapper& query)
{
	PotableService service;
	auto result = service.table_odds(query);
	auto jvo=PotableJsonVO::createShared();
	jvo->success(result);
	return jvo;
}