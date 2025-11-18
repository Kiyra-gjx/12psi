#ifndef _PURCHASEDETAILDTO_
#define _PURCHASEDETAILDTO_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *采购订单详情数据传输模型
 */

class Purchase_DetailDTO : public oatpp::DTO
{
    DTO_INIT(Purchase_DetailDTO, DTO);
    // 商品名称
    API_DTO_FIELD_DEFAULT(String, goodsName, ZH_WORDS_GETTER("purchase.detail.goodsName"));
    // 商品编号
    API_DTO_FIELD_DEFAULT(String, goodsNo, ZH_WORDS_GETTER("purchase.detail.goodsNo"));
    // 规格型号
    API_DTO_FIELD_DEFAULT(String, specModel, ZH_WORDS_GETTER("purchase.detail.specModel"));
    // 辅助属性
    API_DTO_FIELD_DEFAULT(String, attr, ZH_WORDS_GETTER("purchase.detail.attr"));
    // 单位
    API_DTO_FIELD_DEFAULT(String, unit, ZH_WORDS_GETTER("purchase.detail.unit"));
    // 仓库
    API_DTO_FIELD_DEFAULT(String, warehouse, ZH_WORDS_GETTER("purchase.detail.warehouse"));
    // 单价
    API_DTO_FIELD_DEFAULT(Float64, price, ZH_WORDS_GETTER("purchase.detail.price"));
    // 数量
    API_DTO_FIELD_DEFAULT(Float64, nums, ZH_WORDS_GETTER("purchase.detail.nums"));
    // 金额
    API_DTO_FIELD_DEFAULT(Float64, total, ZH_WORDS_GETTER("purchase.detail.total"));
    // 入库数量
    API_DTO_FIELD_DEFAULT(Float64, handle, ZH_WORDS_GETTER("purchase.detail.handle"));
    // 备注信息 
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("purchase.detail.remark"));
    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class PurchaseDetailDTO :public oatpp::DTO
{
    DTO_INIT(PurchaseDetailDTO, oatpp::DTO);
    DTO_FIELD(List<Purchase_DetailDTO::Wrapper>, rows);
    void addData(Purchase_DetailDTO::Wrapper one) {
        this->rows->push_back(one);
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif