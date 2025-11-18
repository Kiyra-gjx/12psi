#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: mlg
 @Date: 2025/10/20 21:40:29

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
#ifndef _FUNDS_QUERY_
#define _FUNDS_QUERY_

#include "GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class FundsQuery : public PageQuery
{
	DTO_INIT(FundsQuery, PageQuery);
	// 账户名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("funds.field.name");
	}
	// 账户编号
	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("funds.field.number");
	}
	// 备注信息
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("funds.field.data");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_