#pragma once
#ifndef  _DELETERETURNORDERSERVICE_H_
#define  _DELETERETURNORDERSERVICE_H_

#include "domain/dto/DeleteReturnOrdersDTO.h"

class DeleteReturnOrderService {
public:
	bool deleteReturnOrders(const DeleteReturnOrdersDTO::Wrapper& dto);
};

#endif // ! _ADDRETURNORDERSERVICE_H_

