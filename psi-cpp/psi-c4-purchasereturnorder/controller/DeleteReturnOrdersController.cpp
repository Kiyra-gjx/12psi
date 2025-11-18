#include <stdafx.h>

#include "DeleteReturnOrdersController.h"
#include "service/DeleteReturnOrderService.h"

StringJsonVO::Wrapper DeleteReturnOrdersController::executeDeleteReturnOrders(const DeleteReturnOrdersDTO::Wrapper& dto) {
	DeleteReturnOrderService aos;
	auto jvo = StringJsonVO::createShared();
	bool res = aos.deleteReturnOrders(dto);
	if (res == false) {
		jvo->fail("fail");
	}
	else {
		jvo->success("success");
	}
	return jvo;
}