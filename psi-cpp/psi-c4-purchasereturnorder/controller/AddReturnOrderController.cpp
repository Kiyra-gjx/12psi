#include <stdafx.h>

#include "AddReturnOrderController.h"
#include "service/AddReturnOrderService.h"

StringJsonVO::Wrapper AddReturnOrderController::executeAddReturnOrder(const AddReturnOrderDTO::Wrapper& dto) {
	AddReturnOrderService aos;
	auto jvo = StringJsonVO::createShared();
	auto id = aos.addReturnOrder(dto);
	if (id == "") {
		jvo->fail(id);
	}
	else {
		jvo->success(id);
	}
	return jvo;
}