#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/10/18 19:34:41

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
#ifndef _CUSTOMERVO_H_
#define _CUSTOMERVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/CustomerDTO/CustomerDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 客户列表分页显示JsonVO，用于响应给客户端的Json对象
 */
class CustomerListPageJsonVO : public JsonVO<CustomerListPageDTO::Wrapper> {
	DTO_INIT(CustomerListPageJsonVO, JsonVO<CustomerListPageDTO::Wrapper>);
};

/**
 * 客户详情显示JsonVO，用于响应给客户端的Json对象
 */
class CustomerDetailJsonVO : public JsonVO<CustomerDetailDTO::Wrapper> {
	DTO_INIT(CustomerDetailJsonVO, JsonVO<CustomerDetailDTO::Wrapper>);
};



//修改客户JsonVO实体
class CustomerModifyJsonVO : public JsonVO<CustomerModifyDTO::Wrapper> {
public:
    DTO_INIT(CustomerModifyJsonVO, JsonVO<CustomerModifyDTO::Wrapper>);

};


class CustomerAddResponseVO : public JsonVO<CustomerAddResponseDTO::Wrapper>
{
	DTO_INIT(CustomerAddResponseVO, JsonVO<CustomerAddResponseDTO::Wrapper>);

};

class CustomerGetResponseVO : public JsonVO<CustomerGetResponseDTO::Wrapper>
{
	DTO_INIT(CustomerGetResponseVO, JsonVO<CustomerGetResponseDTO::Wrapper>);

};


#include OATPP_CODEGEN_END(DTO)
#endif //_CustomerDTO_H_ 