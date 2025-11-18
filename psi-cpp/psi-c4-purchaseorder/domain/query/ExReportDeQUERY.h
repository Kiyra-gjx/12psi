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
#include "../../../lib-oatpp/include/domain/query/PageQuery.h"
// #include "domain/query"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 采购订单添加条件ExBuyQuery字段说明，不含id
 */
class ExReportDeQUERY : public PageQuery
{
    DTO_INIT(ExReportDeQUERY, DTO);

    // 商品名称
    DTO_FIELD(String, goods);
    DTO_FIELD_INFO(goods) {
        info->description = ZH_WORDS_GETTER("bor_info.field.goods");
    }

    // 辅助属性
    DTO_FIELD(String, attr);
    DTO_FIELD_INFO(attr) {
        info->description = ZH_WORDS_GETTER("bor_info.field.attr");
    }

    // 单位
    DTO_FIELD(String, unit);
    DTO_FIELD_INFO(unit) {
        info->description = ZH_WORDS_GETTER("bor_info.field.unit");
    }

    // 仓库
    DTO_FIELD(String, warehouse);
    DTO_FIELD_INFO(warehouse) {
        info->description = ZH_WORDS_GETTER("bor_info.field.warehouse");
    }

    // 单价
    DTO_FIELD(String, price);
    DTO_FIELD_INFO(price) {
        info->description = ZH_WORDS_GETTER("bor_info.field.price");
    }

    // 数量
    DTO_FIELD(String, nums);
    DTO_FIELD_INFO(nums) {
        info->description = ZH_WORDS_GETTER("bor_info.field.nums");
    }

    // 金额
    DTO_FIELD(String, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bor_info.field.total");
    }

    // 税率(%)
    DTO_FIELD(String, tax);
    DTO_FIELD_INFO(tax) {
        info->description = ZH_WORDS_GETTER("bor_info.field.tax");
    }

    // 税额
    DTO_FIELD(String, tat);
    DTO_FIELD_INFO(tat) {
        info->description = ZH_WORDS_GETTER("bor_info.field.tat");
    }

    // 价税合计
    DTO_FIELD(String, tpt);
    DTO_FIELD_INFO(tpt) {
        info->description = ZH_WORDS_GETTER("bor_info.field.tpt");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bor_info.field.data");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_EXBUYINFOQUERY_QUERY_