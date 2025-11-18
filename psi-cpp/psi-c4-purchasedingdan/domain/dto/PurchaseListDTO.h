#ifndef _PURCHASELISTDTO_
#define _PURCHASELISTDTO_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
*采购订单列表传输模型
*
*/

class PurchaseListDTO : public oatpp::DTO
{
    DTO_INIT(PurchaseListDTO, DTO);

    // 所属组织
    API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("purchase.list.frame"));
    // 供应商
    API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("purchase.list.supplier"));
    // 单据时间
    API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("purchase.list.time"));
    // 单据编号
    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("purchase.list.number"));
    // 单据金额
    API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("purchase.list.total"));
    // 关联单据
    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("purchase.list.source"));
    // 实际金额
    API_DTO_FIELD_DEFAULT(Float64, actual, ZH_WORDS_GETTER("purchase.list.actual"));
    // 到货时间
    API_DTO_FIELD_DEFAULT(String, arrival, ZH_WORDS_GETTER("purchase.list.arrival"));
    // 物流信息
    API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("purchase.list.logistics"));
    // 单据附件
    API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("purchase.list.file"));
    // 扩展信息
    API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("purchase.list.more"));
};


/*** 采购订单列表分页数据传输模型*/
class PurchaseListPageDTO : public PageDTO<PurchaseListDTO::Wrapper>
{
    DTO_INIT(PurchaseListPageDTO, PageDTO<PurchaseListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PURCHASELISTDTO_