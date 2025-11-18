#ifndef _PURCHASEDATAQUERY_H_
#define _PURCHASEDATAQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 采购订单详情查询对象
 *
 */

class PurchaseDataQuery : public PageQuery
{
    DTO_INIT(PurchaseDataQuery, PageQuery);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASEDATAQUERY_H_