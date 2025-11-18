#ifndef _PURCHASEDETAILQUERY_H_
#define _PURCHASEDETAILQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 采购订单详情查询对象
 *
 */

class PurchaseDetailQuery : public PageQuery
{
    DTO_INIT(PurchaseDetailQuery, PageQuery);
    // 供应商
    API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("purchase.detail.supplier"));
    // 单据时间
    API_DTO_FIELD_DEFAULT(String, docDate, ZH_WORDS_GETTER("purchase.detail.docDate"));
    // 单据编号
    API_DTO_FIELD_DEFAULT(String, docNo, ZH_WORDS_GETTER("purchase.detail.docNo"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASEDETAILQUERY_H_