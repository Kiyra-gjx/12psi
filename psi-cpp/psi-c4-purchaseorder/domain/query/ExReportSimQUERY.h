#pragma once

#ifndef _USERQUERY_H_
#define _USERQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 报表模拟查询条件ExReportSimQUERY字段说明
 * 用于报表导出场景的模拟查询参数，包含组织、供应商、时间等筛选条件
 */
class ExReportSimQUERY : public PageQuery
{
    DTO_INIT(ExReportSimQUERY, PageQuery);

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

    // 订单时间
    DTO_FIELD(Int32, time);
    DTO_FIELD_INFO(time) {
        info->description = ZH_WORDS_GETTER("bor.field.time");
    }

    // 订单编号
    DTO_FIELD(String, number);
    DTO_FIELD_INFO(number) {
        info->description = ZH_WORDS_GETTER("bor.field.number");
    }

    // 订单总额
    DTO_FIELD(String, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bor.field.total");
    }

    // 实际数量
    DTO_FIELD(String, actual);
    DTO_FIELD_INFO(actual) {
        info->description = ZH_WORDS_GETTER("bor.field.actual");
    }

    // 实际金额
    DTO_FIELD(String, money);
    DTO_FIELD_INFO(money) {
        info->description = ZH_WORDS_GETTER("bor.field.money");
    }

    // 订单成本
    DTO_FIELD(String, cost);
    DTO_FIELD_INFO(cost) {
        info->description = ZH_WORDS_GETTER("bor.field.cost");
    }

    // 采购人员
    DTO_FIELD(Int32, people);
    DTO_FIELD_INFO(people) {
        info->description = ZH_WORDS_GETTER("bor.field.people");
    }

    // 审核状态[0:未审核|1:已审核]
    DTO_FIELD(Int8, examine);
    DTO_FIELD_INFO(examine) {
        info->description = ZH_WORDS_GETTER("bor.field.examine");
    }

    // 核价状态[0:未核价|1:待核价|2:已核价]
    DTO_FIELD(Int8, nucleus);
    DTO_FIELD_INFO(nucleus) {
        info->description = ZH_WORDS_GETTER("bor.field.nucleus");
    }

    // 验收状态[0:未验收|1:待验收|2:已验收|3:验收合格]
    DTO_FIELD(Int8, cse);
    DTO_FIELD_INFO(cse) {
        info->description = ZH_WORDS_GETTER("bor.field.cse");
    }

    // 发票状态[0:未开票|1:待开票|2:已开票|3:开票完成]
    DTO_FIELD(Int8, invoice);
    DTO_FIELD_INFO(invoice) {
        info->description = ZH_WORDS_GETTER("bor.field.invoice");
    }

    // 付款状态[0:未付款|1:已付款]
    DTO_FIELD(Int8, check);
    DTO_FIELD_INFO(check) {
        info->description = ZH_WORDS_GETTER("bor.field.check");
    }

    // 归属人
    DTO_FIELD(Int32, user);
    DTO_FIELD_INFO(user) {
        info->description = ZH_WORDS_GETTER("bor.field.user");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bor.field.data");
    }

    // 关联PayloadDTO对象（用于负载数据传递）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_EX_REPORT_SIM_QUERY_H_