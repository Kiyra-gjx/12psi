#pragma once
#ifndef  _ADDRETURNORDERSERVICE_H_
#define  _ADDRETURNORDERSERVICE_H_

#include "../domain/dto/AddReturnOrderDTO.h"

class AddReturnOrderService {
public:
	std::string addReturnOrder(const AddReturnOrderDTO::Wrapper& dto);
};

#endif // ! _ADDRETURNORDERSERVICE_H_
