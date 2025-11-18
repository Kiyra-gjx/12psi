#pragma once
#ifndef _EXREPORTSIMQUERY_QUERY_
#define _EXREPORTSIMQUERY_QUERY_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class ExReportSimQuery : public PageQuery
{
    DTO_INIT(ExReportSimQuery, PageQuery);
    // 所属组织
    DTO_FIELD(Int32, frame);
    DTO_FIELD_INFO(frame) {
        info->description = ZH_WORDS_GETTER("bor.field.frame");
    }

    // 供应商
    DTO_FIELD(Int32, supplier);
    DTO_FIELD_INFO(supplier) {
        info->description = ZH_WORDS_GETTER("bor.field.supplier");
    }

    // 单据时间
    DTO_FIELD(Int32, time);
    DTO_FIELD_INFO(time) {
        info->description = ZH_WORDS_GETTER("bor.field.time");
    }

    // 单据编号
    DTO_FIELD(String, number);
    DTO_FIELD_INFO(number) {
        info->description = ZH_WORDS_GETTER("bor.field.number");
    }

    // 单据金额
    DTO_FIELD(String, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bor.field.total");
    }

    // 实际金额
    DTO_FIELD(String, actual);
    DTO_FIELD_INFO(actual) {
        info->description = ZH_WORDS_GETTER("bor.field.actual");
    }

    // 到货日期
    DTO_FIELD(Int32, arrival);
    DTO_FIELD_INFO(arrival) {
        info->description = ZH_WORDS_GETTER("bor.field.arrival");
    }

    // 审核状态
    DTO_FIELD(Int8, examine);
    DTO_FIELD_INFO(examine) {
        info->description = ZH_WORDS_GETTER("bor.field.examine");
    }

    // 入库状态
    DTO_FIELD(Int8, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("bor.field.state");
    }

    // 关联人员
    DTO_FIELD(Int32, people);
    DTO_FIELD_INFO(people) {
        info->description = ZH_WORDS_GETTER("bor.field.people");
    }

    // 制单人
    DTO_FIELD(Int32, user);
    DTO_FIELD_INFO(user) {
        info->description = ZH_WORDS_GETTER("bor.field.user");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bor.field.data");
    }
};



#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_

