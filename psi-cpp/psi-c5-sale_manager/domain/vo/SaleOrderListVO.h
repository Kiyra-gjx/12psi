#pragma once

#include "../GlobalInclude.h"
#include "domain/dto/SaleOrderListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class SaleOrderListPageJsonVO :public JsonVO<SaleOrderListPageDTO::Wrapper>{
	DTO_INIT(SaleOrderListPageJsonVO, JsonVO<SaleOrderListPageDTO::Wrapper>);
};

class SaleOrderDetailJsonVO :public JsonVO<SaleOrderDetailDTO::Wrapper> {
	DTO_INIT(SaleOrderDetailJsonVO, JsonVO<SaleOrderDetailDTO::Wrapper>);
};

/*
	将生成的销售单响应给客户端的JSON对象
*/
class SO_by_saleJsonVO : public JsonVO<SellGenerateDTO::Wrapper> {
	DTO_INIT(SO_by_saleJsonVO, JsonVO<SellGenerateDTO::Wrapper>);

    DTO_FIELD(String, pid);
    DTO_FIELD(String, goods);
    DTO_FIELD(String, unit);
    DTO_FIELD(String, warehouse);
    DTO_FIELD(Float64, price);
    DTO_FIELD(Float64, nums);
    DTO_FIELD(Float64, total);
    DTO_FIELD(Float64, tax);
    DTO_FIELD(Float64, tat);
    DTO_FIELD(Float64, tpt);
};

/*
	将生成的采购订单响应给客户端的JSON对象
*/
class PO_by_saleJsonVO : public JsonVO<PurchaseGenerateDTO::Wrapper> {
	DTO_INIT(PO_by_saleJsonVO, JsonVO<PurchaseGenerateDTO::Wrapper>);

    DTO_FIELD(String, pid);
    DTO_FIELD(String, goods);
    DTO_FIELD(String, unit);
    DTO_FIELD(String, warehouse);
    DTO_FIELD(Float64, price);
    DTO_FIELD(Float64, nums);
    DTO_FIELD(Float64, total);
    DTO_FIELD(Float64, tax);
    DTO_FIELD(Float64, tat);
    DTO_FIELD(Float64, tpt);
};

// 批量删除销售订单返回结果
class SorDeleteResultVO : public oatpp::DTO {
    
    DTO_INIT(SorDeleteResultVO, DTO);
    DTO_FIELD(Int32, successCount);
    DTO_FIELD(Int32, failureCount);
    // 删除失败的订单ID列表
    DTO_FIELD(List<String>, failedOrderIds) = {};
};

// 批量审核/反审核销售订单返回结果
class SorAuditResultVO : public oatpp::DTO {
    DTO_INIT(SorAuditResultVO, DTO);

    // 成功审核/反审核的订单数量
    DTO_FIELD(Int32, successCount);

    // 失败的订单数量
    DTO_FIELD(Int32, failureCount);
    // 失败的订单ID列表
    DTO_FIELD(List<String>, failedOrderIds) = {};
   

};
class SorDeleteJsonVO : public JsonVO<SorDeleteResultVO::Wrapper> {
    DTO_INIT(SorDeleteJsonVO, JsonVO<SorDeleteResultVO::Wrapper>);
};

class SorAuditJsonVO : public JsonVO<SorAuditResultVO::Wrapper> {
    DTO_INIT(SorAuditJsonVO, JsonVO<SorAuditResultVO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
