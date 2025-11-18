#pragma once

#include "domain/GlobalInclude.h"
#ifndef _LIST_DTO_
#define _LIST_DTO_

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 采购退货单列表数据传输模型
 */
class getreturnlistDTO : public oatpp::DTO {
    DTO_INIT(getreturnlistDTO, DTO);
    // 编号
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("purchasereturnorder.main-field.id"));
    // 关联单据
    API_DTO_FIELD_DEFAULT(String, source, ZH_WORDS_GETTER("purchasereturnorder.main-field.source"));
    // 所属组织
    API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("purchasereturnorder.main-field.frame"));
    // 供应商
    API_DTO_FIELD_DEFAULT(String, supplier, ZH_WORDS_GETTER("purchasereturnorder.main-field.supplier"));
    // 单据时间
    API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("purchasereturnorder.main-field.time"));
    // 单据编号
    API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("purchasereturnorder.main-field.number"));
    // 单据金额
    API_DTO_FIELD_DEFAULT(String, total, ZH_WORDS_GETTER("purchasereturnorder.main-field.total"));
    // 实际金额
    API_DTO_FIELD_DEFAULT(String, actual, ZH_WORDS_GETTER("purchasereturnorder.main-field.actual"));
    // 实收金额
    API_DTO_FIELD_DEFAULT(String, money, ZH_WORDS_GETTER("purchasereturnorder.main-field.money"));
    // 单据费用
    API_DTO_FIELD_DEFAULT(String, cost, ZH_WORDS_GETTER("purchasereturnorder.main-field.cost"));
    // 结算账户
    API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("purchasereturnorder.main-field.account"));
    // 关联人员
    API_DTO_FIELD_DEFAULT(String, people, ZH_WORDS_GETTER("purchasereturnorder.main-field.people"));
    // 物流信息
    API_DTO_FIELD_DEFAULT(String, logistics, ZH_WORDS_GETTER("purchasereturnorder.main-field.logistics"));
    // 单据附件
    API_DTO_FIELD_DEFAULT(String, file, ZH_WORDS_GETTER("purchasereturnorder.main-field.file"));
    // 备注信息
    API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("purchasereturnorder.main-field.data"));
    // 扩展信息
    API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("purchasereturnorder.main-field.more"));
    // 审核状态
    API_DTO_FIELD_DEFAULT(String, examine, ZH_WORDS_GETTER("purchasereturnorder.main-field.examine"));
    // 核销状态
    API_DTO_FIELD_DEFAULT(String, nucleus, ZH_WORDS_GETTER("purchasereturnorder.main-field.nucleus"));
    // 费用状态
    API_DTO_FIELD_DEFAULT(String, cse, ZH_WORDS_GETTER("purchasereturnorder.main-field.cse"));
    // 发票状态
    API_DTO_FIELD_DEFAULT(String, invoice, ZH_WORDS_GETTER("purchasereturnorder.main-field.invoice"));
    // 核对状态
    API_DTO_FIELD_DEFAULT(String, check, ZH_WORDS_GETTER("purchasereturnorder.main-field.check"));
    // 制单人
    API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("purchasereturnorder.main-field.user"));
};

/**
 * 采购退货单列表分页数据传输模型
 */
class getreturnlistPageDTO : public PageDTO<getreturnlistDTO::Wrapper> {
    DTO_INIT(getreturnlistPageDTO, PageDTO<getreturnlistDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_LIST_DTO_