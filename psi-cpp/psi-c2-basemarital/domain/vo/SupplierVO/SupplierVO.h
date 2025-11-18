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
#ifndef _SUOOLIERVO_H_
#define _SUOOLIERVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/SupplierDTO/SupplierDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 导入数据，用于响应给客户端的Json对象
 */
class SupplierImportJsonVO : public JsonVO<SupplierDTO::Wrapper> {
	DTO_INIT(SupplierImportJsonVO, JsonVO<SupplierDTO::Wrapper>);
};

/**
 * 导出数据，用于响应给客户端的Json对象
 */
class SupplierExportJsonVO : public JsonVO<SupplierDTO::Wrapper> {
	DTO_INIT(SupplierExportJsonVO, JsonVO<SupplierDTO::Wrapper>);
};

/**
 * 删除，用于响应给客户端的Json对象
 */
class SupplierDeleteOJsonVO : public JsonVO<SupplierDTO::Wrapper> {
	DTO_INIT(SupplierDeleteOJsonVO, JsonVO<SupplierDTO::Wrapper>);
};


//显示供应商列表
class SupplierListJsonVO : public JsonVO< SupplierListDTO::Wrapper>
{
	DTO_INIT(SupplierListJsonVO, JsonVO< SupplierListDTO::Wrapper>);
};

//分页显示供应商列表
class SupplierListPageJsonVO : public JsonVO<SupplierListPageDTO::Wrapper>
{
	DTO_INIT(SupplierListPageJsonVO, JsonVO<SupplierListPageDTO::Wrapper>);
};

//供应商详情显示
class SupplierDetailJsonVO : public JsonVO<SupplierDetailDTO::Wrapper>
{
	DTO_INIT(SupplierDetailJsonVO, JsonVO<SupplierDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif

