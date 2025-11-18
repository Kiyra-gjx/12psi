#pragma once
#ifndef _INOUTCATEGORY_SERVICE_H_
#define _INOUTCATEGORY_SERVICE_H_
#include "domain/vo/inout-category/InoutCategoryVO.h"
#include "domain/query/inout-category/InoutCategoryQuery.h"
#include "domain/dto/inout-category/InoutCategoryDTO.h"

class InoutCategoryService
{
public:
	//获取收支类别名称列表（条件）
	List<InoutCategorySimpleDTO::Wrapper> listNames(const InoutCategoryQuery::Wrapper& query);
	//获取收支类别列表（条件+分页）
	InoutCategoryPageDTO::Wrapper listPage(const InoutCategoryPageQuery::Wrapper& query);
	//获取指定类别详情
	InoutCategoryDetailDTO::Wrapper getById(const string& id);

	// 新增数据
	std::string AddInoutCategory(const InoutCategoryAddDTO::Wrapper& dto);
	// 修改数据
	bool ModifyInoutCategory(const InoutCategoryUpdateDTO::Wrapper& dto);
	// 通过ID删除数据
	bool RemoveInoutCategory(const oatpp::String& id);
};

#endif // !_INOUTCATEGORY_SERVICE_H_
