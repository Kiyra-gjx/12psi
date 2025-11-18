#pragma once

//销售单
#ifndef _SELLVO_H_
#define _SELLVO_H_

#include "../GlobalInclude.h"
#include "../dto/SellDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)
 
// 获取销售单列表（条件+分页）
class SellListJsonVO : public JsonVO<SellPageDTO::Wrapper>
{

    DTO_INIT(SellListJsonVO, JsonVO<SellPageDTO::Wrapper>);
};

// 获取单条商品信息（与销售单详情关联）
class SellSingleInfoJsonVO : public JsonVO<Object<SellSingleInfoDTO>>
{

    DTO_INIT(SellSingleInfoJsonVO, JsonVO<Object<SellSingleInfoDTO>>);
};

// 获取指定销售单详情
class SellDetailJsonVO : public JsonVO<SellDetailDTO::Wrapper>
{

    DTO_INIT(SellDetailJsonVO, JsonVO<SellDetailDTO::Wrapper>);

};

// 新增销售单后返回信息
class SellAddJsonVO : public JsonVO<String>
{

    DTO_INIT(SellAddJsonVO, JsonVO<String>);

    // 销售单 id
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("sell.field.listid"), false);
};

// 批量删除销售单返回结果
class SalenoteDeleteResultVO : public oatpp::DTO {
    DTO_INIT(SalenoteDeleteResultVO, DTO);

    // 成功删除的订单数量
    DTO_FIELD(Int32, successCount) = 0;
    DTO_FIELD_INFO(successCount) {
        //info->description = "成功删除的订单数量";
    }

    // 删除失败的订单数量
    DTO_FIELD(Int32, failureCount) = 0;
    DTO_FIELD_INFO(failureCount) {
        //info->description = "删除失败的订单数量";
    }

    // 删除失败的订单ID列表
    DTO_FIELD(List<String>, failedOrderIds) = {};
    DTO_FIELD_INFO(failedOrderIds) {
        //info->description = "删除失败的订单ID列表";
    }
};

// 批量审核/反审核销售单返回结果
class SellAuditResultVO : public oatpp::DTO {
    DTO_INIT(SellAuditResultVO, DTO);
    DTO_FIELD(Int32, successCount);
    DTO_FIELD(Int32, failureCount);
    DTO_FIELD(List<oatpp::String>, failedOrderIds);
};
class SalenoteDeleteJsonVO : public JsonVO<SalenoteDeleteResultVO::Wrapper> {
    DTO_INIT(SalenoteDeleteJsonVO, JsonVO<SalenoteDeleteResultVO::Wrapper>);
};

class SellAuditJsonVO : public JsonVO<SellAuditResultVO::Wrapper> {
    DTO_INIT(SellAuditJsonVO, JsonVO<SellAuditResultVO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SELLVO_H_