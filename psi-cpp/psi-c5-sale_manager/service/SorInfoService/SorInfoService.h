#pragma once


#ifndef _SORINFOSERVICE_H_
#define _SORINFOSERVICE_H_

#include "domain/query/SorInfoQuery.h"
#include "domain/dto/SorInfoDTO.h"
#include "domain/dto/SaleOrderListDTO.h"
#include "domain/query/SaleOrderListQuery.h"

class SorInfoService {
public:
	SaleOrderDetailDTO::Wrapper getSaleOrderDetail(const oatpp::String& id);

	//获取文件服务器地址
	std::string getDfsServerAddrssUrl();
};

#endif

