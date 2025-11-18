#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/09/18 15:01:29

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _EXBUY_DTO_H_
#define _EXBUY_DTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单添加条件ExBuyQuery字段说明，不含id
 */

/**
 * 采购订单添加条件，不含id
 */
class ExReportSimAddDTO : public oatpp::DTO
{
    DTO_INIT(ExReportSimAddDTO, DTO);

    // 所属组织
    DTO_FIELD(String, frame);
    DTO_FIELD_INFO(frame) {
        info->description = ZH_WORDS_GETTER("bor.field.frame");
    }

    // 供应商
    DTO_FIELD(String, supplier);
    DTO_FIELD_INFO(supplier) {
        info->description = ZH_WORDS_GETTER("bor.field.supplier");
    }

    // 订单时间
    DTO_FIELD(String, time);
    DTO_FIELD_INFO(time) {
        info->description = ZH_WORDS_GETTER("bor.field.time");
    }

    // 订单编号
    DTO_FIELD(String, number);
    DTO_FIELD_INFO(number) {
        info->description = ZH_WORDS_GETTER("bor.field.number");
    }

    // 订单总额
    DTO_FIELD(Float64, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bor.field.total");
    }

    // 实际金额
    DTO_FIELD(Float64, actual);
    DTO_FIELD_INFO(actual) {
        info->description = ZH_WORDS_GETTER("bor.field.actual");
    }

    // 实付金额
    DTO_FIELD(Float64, money);
    DTO_FIELD_INFO(money) {
        info->description = ZH_WORDS_GETTER("bor.field.money");
    }

    // 订单成本
    DTO_FIELD(Float64, cost);
    DTO_FIELD_INFO(cost) {
        info->description = ZH_WORDS_GETTER("bor.field.cost");
    }

    // 采购人员
    DTO_FIELD(String, people);
    DTO_FIELD_INFO(people) {
        info->description = ZH_WORDS_GETTER("bor.field.people");
    }

    // 审核状态[0:未审核|1:已审核]
    DTO_FIELD(Int8, examine);
    DTO_FIELD_INFO(examine) {
        info->description = ZH_WORDS_GETTER("bor.field.examine");
    }

    // 核销状态[0:未核销|1:部分核销|2:已核销]
    DTO_FIELD(Int8, nucleus);
    DTO_FIELD_INFO(nucleus) {
        info->description = ZH_WORDS_GETTER("bor.field.nucleus");
    }

    // 费用状态[0:未结算|1:部分结算|2:已结算|3:无需结算]
    DTO_FIELD(Int8, cse);
    DTO_FIELD_INFO(cse) {
        info->description = ZH_WORDS_GETTER("bor.field.cse");
    }

    // 发票状态[0:未开票|1:部分开票|2:已开票|3:无需开具]
    DTO_FIELD(Int8, invoice);
    DTO_FIELD_INFO(invoice) {
        info->description = ZH_WORDS_GETTER("bor.field.invoice");
    }

    // 核对状态[0:未核对|1:已核对]
    DTO_FIELD(Int8, check);
    DTO_FIELD_INFO(check) {
        info->description = ZH_WORDS_GETTER("bor.field.check");
    }

    // 制单人
    DTO_FIELD(String, user);
    DTO_FIELD_INFO(user) {
        info->description = ZH_WORDS_GETTER("bor.field.user");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bor.field.data");
    }

    // 关联单据
    DTO_FIELD(String, source);
    DTO_FIELD_INFO(source) {
        info->description = ZH_WORDS_GETTER("bor.field.source");
    }

    // 结算账户
    DTO_FIELD(String, account);
    DTO_FIELD_INFO(account) {
        info->description = ZH_WORDS_GETTER("bor.field.account");
    }

    // 物流信息
    DTO_FIELD(String, logistics);
    DTO_FIELD_INFO(logistics) {
        info->description = ZH_WORDS_GETTER("bor.field.logistics");
    }

    // 单据附件
    DTO_FIELD(String, file);
    DTO_FIELD_INFO(file) {
        info->description = ZH_WORDS_GETTER("bor.field.file");
    }

    // 扩展信息
    DTO_FIELD(String, more);
    DTO_FIELD_INFO(more) {
        info->description = ZH_WORDS_GETTER("bor.field.more");
    }

    // 关联PayloadDTO对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/**
 * 采购订单信息（含id）
 */
class ExReportSimDTO : public ExReportSimAddDTO
{
    DTO_INIT(ExReportSimDTO, ExReportSimAddDTO);

    // 主键，采购订单唯一标识
    DTO_FIELD(String, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("bor.field.id");
    }
};

/**
 * 采购订单分页查询结果
 */
class ExReportSimPageDTO : public PageDTO<ExReportSimDTO::Wrapper>
{
    DTO_INIT(ExReportSimPageDTO, PageDTO<ExReportSimDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_EXBUY_DTO_H_