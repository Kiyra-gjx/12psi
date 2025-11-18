#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/18 19:25:14

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
#ifndef _CUSTOMERQUERY_H_
#define _CUSTOMERQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 客户分页查询对象
 */
class CustomerQuery : public PageQuery
{
	DTO_INIT(CustomerQuery, PageQuery);
	// 客户名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("cus.field.name"));
	// 客户编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("cus.field.number"));
	// 客户类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("cus.field.category"));
	// 客户等级
	API_DTO_FIELD_DEFAULT(String, grade, ZH_WORDS_GETTER("cus.field.grade"));
	// 联系人员
	API_DTO_FIELD_DEFAULT(String, contact_person, ZH_WORDS_GETTER("cus.field.contact_person"));
	// 联系电话
	API_DTO_FIELD_DEFAULT(String, telephone, ZH_WORDS_GETTER("cus.field.telephone"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(String, username, ZH_WORDS_GETTER("cus.field.username"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, memo, ZH_WORDS_GETTER("cus.field.memo"));
};


#include OATPP_CODEGEN_END(DTO)
#endif // !_CUSTOMER_QUERY