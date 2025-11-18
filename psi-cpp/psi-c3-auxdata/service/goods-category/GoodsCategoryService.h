
#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 */
#ifndef _GOODS_CATEGORY_SERVICE_
#define _GOODS_CATEGORY_SERVICE_
#include "../../domain/vo/goods-category/GoodsCategoryVO.h"
#include "../../domain/query/goods-category/GoodsCategoryQuery.h"
#include "../../domain/dto/goods-category/GoodsCategoryDTO.h"
#include <string>
#include <iostream>
 /**
  * 商品类别业务服务
  */
class GoodsCategoryService
{
public:

	// 分页查询商品类别
	GoodsCategoryPageDTO::Wrapper listAll(const GoodsCategoryQuery::Wrapper& query);
	// 根据ID查询商品类别
	GoodsCategoryDTO::Wrapper getById(const std::string& id);
	// 根据名称查询商品类别
	GoodsCategoryDTO::Wrapper getByName(const std::string& name);
	// 新增商品类别
	GoodsCategoryDTO::Wrapper saveData(const GoodsCategoryAddDTO::Wrapper& dto);
	// 更新商品类别
	GoodsCategoryDTO::Wrapper updateData(const GoodsCategoryDTO::Wrapper& dto);
	// 通过id主键删除商品类型
	GoodsCategoryDeleteDTO::Wrapper removeDataById(const std::string& id);
	// 获取商品类别树形结构
	oatpp::Vector<GoodsCategoryDTO::Wrapper> getCategoryTree();
	//oatpp::Vector<GoodsCategoryDTO::Wrapper> getCategoryTreeById(const std::string& rootId = "0");
	// 按ID获取类别树JSON
	std::string getCategoryTreeJsonById(const std::string& rootId);
};

#endif // !_GOODS_CATEGORY_SERVICE_
