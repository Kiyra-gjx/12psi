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
#ifndef _DETAILREPORT_DTO_H_
#define _DETAILREPORT_DTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页传输对象
 */
class DetailReportDTO : public oatpp::DTO
{
    DTO_INIT(DetailReportDTO, DTO);
    // 商品名称   是否多表一起查？？？
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("bre_info.goods");
    }

    // 规格型号
    DTO_FIELD(String, spec);
    DTO_FIELD_INFO(spec) {
        info->description = ZH_WORDS_GETTER("bre_info.spec");
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
    DTO_FIELD(Int32, nums);
    DTO_FIELD_INFO(nums) {
        info->description = ZH_WORDS_GETTER("bre_info.nums");
    }

    // 折扣率
    DTO_FIELD(Float64, discount);
    DTO_FIELD_INFO(discount) {
        info->description = ZH_WORDS_GETTER("bre_info.discount");
    }

    // 折扣额
    DTO_FIELD(Int32, dsc);
    DTO_FIELD_INFO(dsc) {
        info->description = ZH_WORDS_GETTER("bre_info.dsc");
    }

    // 金额
    DTO_FIELD(Int32, total);
    DTO_FIELD_INFO(total) {
        info->description = ZH_WORDS_GETTER("bre_info.total");
    }

    // 税率
    DTO_FIELD(Float64, tax);
    DTO_FIELD_INFO(tax) {
        info->description = ZH_WORDS_GETTER("bre_info.tax");
    }

    // 税额
    DTO_FIELD(Int32, tat);
    DTO_FIELD_INFO(tat) {
        info->description = ZH_WORDS_GETTER("bre_info.tat");
    }

    // 价税合计
    DTO_FIELD(Int32, tpt);
    DTO_FIELD_INFO(tpt) {
        info->description = ZH_WORDS_GETTER("bre_info.tpt");
    }

    // 备注信息
    DTO_FIELD(String, data);
    DTO_FIELD_INFO(data) {
        info->description = ZH_WORDS_GETTER("bre_info.data");
    }
    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/**
 * 示例传输对象
 */
class ExReportDeDTO : public DetailReportDTO
{
    DTO_INIT(ExReportDeDTO, DetailReportDTO);
    // 编号
    DTO_FIELD(String, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("sample.field.id");
    }
};

/**
 * 示例分页传输对象
 */
class ExReportDePageDTO : public PageDTO<ExReportDeDTO::Wrapper>
{
    DTO_INIT(ExReportDePageDTO, PageDTO<ExReportDeDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_