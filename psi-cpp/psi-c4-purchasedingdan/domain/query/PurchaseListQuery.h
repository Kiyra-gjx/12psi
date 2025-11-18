#ifndef _PURCHASELISTQUERY_H_
#define _PURCHASELISTQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
 * 采购订单详情查询对象
 *
 */

class PurchaseListQuery : public PageQuery
{
    DTO_INIT(PurchaseListQuery, PageQuery); 
    // 单据编号
    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("purchase.list.number"));
    // 供应商
    API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("purchase.list.supplier"));
    // 关联人员
    API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("purchase.list.people"));
    // 制单人
    API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("purchase.list.user"));
    // 审核状态
    API_DTO_FIELD_DEFAULT(Int32, examine, ZH_WORDS_GETTER("purchase.list.examine"));
    // 入库状态
    API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("purchase.list.state"));
    // 备注信息
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("purchase.list.data"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASELISTQUERY_H_