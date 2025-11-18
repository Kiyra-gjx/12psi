#pragma once

#ifndef _ExReportDe_QUERY_
#define _ExReportDe_QUERY_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class ExReportDeQuery :public oatpp::DTO
{
	DTO_INIT(ExReportDeQuery, DTO);
    // 商品名称
    DTO_FIELD(String, goodsName);
    DTO_FIELD_INFO(goodsName) {
        info->description = ZH_WORDS_GETTER("bor_info.good");
    }

    // 规格型号
    DTO_FIELD(Int32, spec);
    DTO_FIELD_INFO(spec) {
        info->description = ZH_WORDS_GETTER("bor_info.spec");
    }

    // 辅助属性
    DTO_FIELD(String, attr);
    DTO_FIELD_INFO(attr) {
        info->description = ZH_WORDS_GETTER("bor_info.attr");
    }

    // 单位
    DTO_FIELD(String, unit);
    DTO_FIELD_INFO(unit) {
        info->description = ZH_WORDS_GETTER("bor_info.unit");
    }

    // 仓库
    DTO_FIELD(Int32, warehouse);
    DTO_FIELD_INFO(warehouse) {
        info->description = ZH_WORDS_GETTER("bor_info.warehouse");
    }

    // 单价
    DTO_FIELD(Float64, price);
    DTO_FIELD_INFO(price) {
        info->description = ZH_WORDS_GETTER("bor_info.price");
    }

    // 数量
    DTO_FIELD(Int32, nums);
    DTO_FIELD_INFO(nums) {
        info->description = ZH_WORDS_GETTER("bor_info.nums");
    }

    // 入库数量
    DTO_FIELD(Int32, handle);
    DTO_FIELD_INFO(handle) {
        info->description = ZH_WORDS_GETTER("bor_info.handle");
    }

    // 折扣率
    DTO_FIELD(Float64, discount);
    DTO_FIELD_INFO(discount) {
        info->description = ZH_WORDS_GETTER("bor_info.discount");
    }

    // 折扣额
    DTO_FIELD(Int32, dsc);
    DTO_FIELD_INFO(dsc) {
        info->description = ZH_WORDS_GETTER("bor_info.dsc");
    }

    // 金额
    DTO_FIELD(Int32, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bor_info.total");
    }

    // 税率
    DTO_FIELD(Float64, tax);
    DTO_FIELD_INFO(tax) {
        info->description = ZH_WORDS_GETTER("bor_info.tax");
    }

    // 税额
    DTO_FIELD(Int32, tat);
    DTO_FIELD_INFO(tat) {
        info->description = ZH_WORDS_GETTER("bor_info.tat");
    }

    // 价税合计
    DTO_FIELD(Int32, tpt);
    DTO_FIELD_INFO(tpt) {
        info->description = ZH_WORDS_GETTER("bor_info.tpt");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bor_info.data");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_

