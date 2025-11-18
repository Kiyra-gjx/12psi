#pragma once

//销售退货单
#ifndef _SALERETURNORDERVO_H_
#define _SALERETURNORDERVO_H_

#include "../GlobalInclude.h"
#include "../dto/SaleReturnOrderDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 获取销售退货单列表（条件+分页）
class SreListJsonVO : public JsonVO<SrePageDTO::Wrapper> {

	DTO_INIT(SreListJsonVO, JsonVO <SrePageDTO::Wrapper>);
};

// 获取指定销售退货单详情
class SreDetailJsonVO : public JsonVO<SreDetailDTO::Wrapper> {
    DTO_INIT(SreDetailJsonVO, JsonVO<SreDetailDTO::Wrapper>);
};

// 获取指定销售退货单详情
class SreAddJsonVO : public StringJsonVO {

	DTO_INIT(SreAddJsonVO, StringJsonVO);

	//退货单id
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("saleReturnOrder.field.listid"), false);
};

// 基础响应VO
class BaseResponseVO : public oatpp::DTO {
    DTO_INIT(BaseResponseVO, DTO)
    DTO_FIELD(Int32, code) = 0;                    // 响应码
    DTO_FIELD(String, message) = "";               // 响应消息
};

// 批量操作响应VO
class BatchOperationVO : public BaseResponseVO {
    DTO_INIT(BatchOperationVO, BaseResponseVO)
    DTO_FIELD(Int32, successCount) = 0;            // 成功数量
    DTO_FIELD(Int32, failureCount) = 0;            // 失败数量
    DTO_FIELD(Vector<String>, failureIds) = {};    // 失败的ID列表
};

// 导入响应VO
class ImportResponseVO : public BaseResponseVO {
    DTO_INIT(ImportResponseVO, BaseResponseVO)
    DTO_FIELD(Int32, totalCount) = 0;              // 总记录数
    DTO_FIELD(Int32, successCount) = 0;            // 成功数量
    DTO_FIELD(Int32, failureCount) = 0;            // 失败数量
    DTO_FIELD(String, errorFileUrl) = "";          // 错误报告文件URL
};

// 删除销售退货单结果 VO
class DelSaleReturnResultVO : public oatpp::DTO {
    DTO_INIT(DelSaleReturnResultVO, DTO);

    DTO_FIELD(Int32, successCount) = 0;
    DTO_FIELD(Int32, failureCount) = 0;
    DTO_FIELD(List<String>, failedReturnIds) = {};
};

class DelSaleReturnJsonVO : public JsonVO<DelSaleReturnResultVO::Wrapper> {
    DTO_INIT(DelSaleReturnJsonVO, JsonVO<DelSaleReturnResultVO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SREVO_H_