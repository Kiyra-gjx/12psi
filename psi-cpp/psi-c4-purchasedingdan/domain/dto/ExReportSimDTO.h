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
#ifndef _EXREPORTSIM_DTO_H_
#define _EXREPORTSIM_DTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页传输对象
 */
class ExReportSimAddDTO : public oatpp::DTO
{
	DTO_INIT(ExReportSimAddDTO, DTO);
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
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/**
 * 示例传输对象
 */
class ExReportSimDTO : public ExReportSimAddDTO
{
	DTO_INIT(ExReportSimDTO, ExReportSimAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("sample.field.id");
	}
};

/**
 * 示例分页传输对象
 */
class ExReportSimPageDTO : public PageDTO<ExReportSimDTO::Wrapper>
{
	DTO_INIT(ExReportSimPageDTO, PageDTO<ExReportSimDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_