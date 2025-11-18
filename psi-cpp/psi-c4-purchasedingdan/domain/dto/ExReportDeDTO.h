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
#ifndef _EXREPORTDEDTO_H_
#define _EXREPORTDEDTO_H_

#include "../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页传输对象
 */
class ExReportDeAddDTO : public oatpp::DTO
{
	DTO_INIT(ExReportDeAddDTO, DTO);
    // 商品名称
    DTO_FIELD(String, goodsName);
    DTO_FIELD_INFO(goodsName) {
        info->description = ZH_WORDS_GETTER("bor_info.good");
    }

    // 规格型号
    DTO_FIELD(String, spec);
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
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/**
 * 示例传输对象
 */
class ExReportDeDTO : public ExReportDeAddDTO
{
	DTO_INIT(ExReportDeDTO, ExReportDeAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("sample.field.id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_