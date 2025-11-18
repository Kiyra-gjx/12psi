#pragma once
#ifndef _PURCHASEDETAIL_SERVICE_
#define _PURCHASEDETAIL_SERVICE_

#include "domain/query/PurchaseDetailQuery.h"
#include "domain/dto/PurchaseDetailDTO.h"         

class PurchaseDetailService
{
public:
    //查询指定的数据
    PurchaseDetailDTO::Wrapper PurchaseDetail(const PurchaseDetailQuery::Wrapper& query);
};

#endif // !_PURCHASEDETAIL_SERVICE_