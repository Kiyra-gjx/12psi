#pragma once
#ifndef _ADDDELETESERVER_H_
#define _ADDDELETESERVER_H_

#include "domain/dto/AddDeleteOrderDTO.h"


class AddDeleteServer {

public:
	std::string saveData(const AddOrderDTO::Wrapper& dto);

	bool deleteData(const oatpp::List<oatpp::String> &ids);

};

#endif // !_ADDDELETESERVER_H_
