#pragma once

#ifndef _DETAILREPORT_QUERY_
#define _DETAILREPORT_QUERY_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class DetailReportQuery : public PageQuery
{
    DTO_INIT(DetailReportQuery, PageQuery);
    // 商品名称   是否多表一起查？？？
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("goods.name");
    }

    // 规格型号
    DTO_FIELD(String, spec);
    DTO_FIELD_INFO(spec) {
        info->description = ZH_WORDS_GETTER("goods.spec");
    }

    // 辅助属性
    DTO_FIELD(String, attr);
    DTO_FIELD_INFO(attr) {
        info->description = ZH_WORDS_GETTER("bre_info.attr");
    }

    // 单位
    DTO_FIELD(String, unit);
    DTO_FIELD_INFO(unit) {
        info->description = ZH_WORDS_GETTER("bre_info.unit");
    }

    // 仓库
    DTO_FIELD(String, warehouse);
    DTO_FIELD_INFO(warehouse) {
        info->description = ZH_WORDS_GETTER("bre_info.warehouse");
    }

    // 单价
    DTO_FIELD(Float64, price);
    DTO_FIELD_INFO(price) {
        info->description = ZH_WORDS_GETTER("bre_info.price");
    }

    // 数量
    DTO_FIELD(Float64, nums);
    DTO_FIELD_INFO(nums) {
        info->description = ZH_WORDS_GETTER("bre_info.nums");
    }

    // 折扣率
    DTO_FIELD(Float64, discount);
    DTO_FIELD_INFO(discount) {
        info->description = ZH_WORDS_GETTER("bre_info.discount");
    }

    // 折扣额
    DTO_FIELD(Float64, dsc);
    DTO_FIELD_INFO(dsc) {
        info->description = ZH_WORDS_GETTER("bre_info.dsc");
    }

    // 金额
    DTO_FIELD(Float64, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bre_info.total");
    }

    // 税率
    DTO_FIELD(Float64, tax);
    DTO_FIELD_INFO(tax) {
        info->description = ZH_WORDS_GETTER("bre_info.tax");
    }

    // 税额
    DTO_FIELD(Float64, tat);
    DTO_FIELD_INFO(tat) {
        info->description = ZH_WORDS_GETTER("bre_info.tat");
    }

    // 价税合计
    DTO_FIELD(Float64, tpt);
    DTO_FIELD_INFO(tpt) {
        info->description = ZH_WORDS_GETTER("bre_info.tpt");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bre_info.data");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_

