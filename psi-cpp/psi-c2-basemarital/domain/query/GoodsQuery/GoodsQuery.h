
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
#ifndef _GOODSQUERY_H_
#define _GOODSQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 商品分页查询对象
 */
class GoodsQuery : public PageQuery
{
	DTO_INIT(GoodsQuery, PageQuery);
	// 商品名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("goods.field.name"));
	// 商品编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("goods.field.number"));
	// 规格型号
	API_DTO_FIELD_DEFAULT(String, specification_model, ZH_WORDS_GETTER("goods.field.specification_model"));
	//商品分类
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("goods.field.kinds"));
	//商品品牌
	API_DTO_FIELD_DEFAULT(String, brand, ZH_WORDS_GETTER("goods.field.brand"));
	//商品单位
	API_DTO_FIELD_DEFAULT(String, goods_unit, ZH_WORDS_GETTER("goods.field.goods_unit"));
	//商品条码
	API_DTO_FIELD_DEFAULT(String, code, ZH_WORDS_GETTER("goods.field.code"));
	//商品类型
	API_DTO_FIELD_DEFAULT(String, type, ZH_WORDS_GETTER("goods.field.type"));
	//商品备注
	API_DTO_FIELD_DEFAULT(String, memo, ZH_WORDS_GETTER("goods.field.memo"));

};



#include OATPP_CODEGEN_END(DTO)
#endif 
