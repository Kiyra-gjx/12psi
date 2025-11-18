#pragma once


#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: 生成代码
 @Date: 2024/05/20

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
#ifndef _GOODS_CATEGORY_CONTROLLER_
#define _GOODS_CATEGORY_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/goods-category/GoodsCategoryQuery.h"
#include "domain/dto/goods-category/GoodsCategoryDTO.h"
#include "domain/vo/goods-category/GoodsCategoryVO.h"
#include <iostream>
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("goodsCategory.tags.t1")

/**
 * 商品类别控制器
 */
class GoodsCategoryController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GoodsCategoryController);
public:

#pragma once
	ENDPOINT_INFO(getGoodsCategoryTreeJsonById) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("goodsCategory.get.tree-by-id.summary"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("goodsCategory.field.id"), "", true);
	}
	ENDPOINT(API_M_GET, "/goods-category/treeJsonById", getGoodsCategoryTreeJsonById,
		QUERY(String, id),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(execGetGoodsCategoryTreeJsonById(id));
	}
	//ENDPOINT_INFO(getGoodsCategoryTree) {
	//	API_DEF_ADD_TITLE(ZH_WORDS_GETTER("goods-category.get.tree.summary"));
	//	API_DEF_ADD_AUTH();
	//	API_DEF_ADD_RSP_JSON_WRAPPER(GoodsCategoryListJsonVO); // 对应新VO
	//	API_DEF_ADD_TAG(API_TAG);
	//}

	//// 接口实现声明
	//ENDPOINT(API_M_GET, "/goods-category/tree", getGoodsCategoryTree, API_HANDLER_AUTH_PARAME) {
	//	API_HANDLER_RESP_VO(execGetGoodsCategoryTree());
	//}
	// 分页查询商品类别
	ENDPOINT_INFO(queryGoodsCategory) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("goodsCategory.get.summary"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(GoodsCategoryPageJsonVO);
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("goodsCategory.field.name"), "", false);
	}
	ENDPOINT(API_M_GET, "/goods-category/getPageByName", queryGoodsCategory, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, GoodsCategoryQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryGoodsCategory(userQuery));
	}

	// 按ID查询商品类别
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("goodsCategory.query-by-id.summary"), queryGoodsCategoryById, GoodsCategoryJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("goodsCategory.field.id"), "", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/goods-category/queryById", queryGoodsCategoryById, QUERY(String, id), execQueryById(id));
	// 添加商品类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goodsCategory.post.summary"), addGoodsCategory, GoodsCategoryJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/goods-category/add", addGoodsCategory, BODY_DTO(GoodsCategoryAddDTO::Wrapper, dto), execAddGoodsCategory(dto));

	// 修改商品类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goodsCategory.put.summary"), modifyGoodsCategory, GoodsCategoryJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/goods-category/modify", modifyGoodsCategory, BODY_DTO(GoodsCategoryDTO::Wrapper, dto), execModifyGoodsCategory(dto));

	// 通过id主键删除商品类别
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goodsCategory.deleteById.summary"), removeGoodsCategory, BooleanJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/goods-category/remove", removeGoodsCategory, BODY_DTO(GoodsCategoryDeleteDTO::Wrapper, dto), execRemoveGoodsCategory(dto));


private:
	// 分页查询实现
	GoodsCategoryPageJsonVO::Wrapper execQueryGoodsCategory(const GoodsCategoryQuery::Wrapper& query);
	// 按ID查询实现
	GoodsCategoryJsonVO::Wrapper execQueryById(const String& id);
	// 添加实现
	GoodsCategoryJsonVO::Wrapper execAddGoodsCategory(const GoodsCategoryAddDTO::Wrapper& dto);
	// 修改实现
	GoodsCategoryJsonVO::Wrapper execModifyGoodsCategory(const GoodsCategoryDTO::Wrapper& dto);
	// 通过id主键删除商品类别
	BooleanJsonVO::Wrapper execRemoveGoodsCategory(const GoodsCategoryDeleteDTO::Wrapper& dto);
	// 通过名字查询实现
	GoodsCategoryJsonVO::Wrapper execQueryByName(const String& name);
	// 获取商品类别树实现
	GoodsCategoryListJsonVO::Wrapper execGetGoodsCategoryTree();
	// 通过根节点ID获取商品类别树实现
	StringJsonVO::Wrapper execGetGoodsCategoryTreeJsonById(const oatpp::String& rootId);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _GOODS_CATEGORY_CONTROLLER_