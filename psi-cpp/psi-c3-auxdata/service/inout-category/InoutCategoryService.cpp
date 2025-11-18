#include "InoutCategoryService.h"
#include "stdafx.h"
#include "dao/inout-category/InoutCategoryDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include "domain/do/inout-category/InoutCategoryDO.h"

//获取收支类别名称列表（条件）
List<InoutCategorySimpleDTO::Wrapper> InoutCategoryService::listNames(const InoutCategoryQuery::Wrapper& query)
{
	//实例化 dao
	InoutCategoryDAO dao;
	//调用dao
	std::list<InoutCategoryDO> doList = dao.selectNames(query);
	// 创建 DTO 列表
	auto dtoList = oatpp::List<InoutCategorySimpleDTO::Wrapper>::createShared();
	// 遍历 DO 列表
	for (const auto& inoutDo : doList)
	{
		// a. 创建一个空的 SimpleDTO
		auto dto = InoutCategorySimpleDTO::createShared();

		// b. 将 DO 的数据 复制到 DTO 中
		//    (oatpp::String 会自动接受 std::string)
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, inoutDo, id, Id, name, Name);
		// c. 将 DTO 添加到列表中
		dtoList->push_back(dto);
	}

	// 返回 DTO 列表给 Controller
	return dtoList;
}

//获取收支类别列表（条件+分页）
InoutCategoryPageDTO::Wrapper InoutCategoryService::listPage(const InoutCategoryPageQuery::Wrapper& query)
{
	//创建返回对象
	auto pageDto = InoutCategoryPageDTO::createShared();
	//实例化 dao
	InoutCategoryDAO dao;
	//调用dao，获取总条数
	uint64_t total = dao.count(query);
	if (total <= 0)return pageDto;
	//调用dao，获取do列表
	auto doList = dao.selectPage(query);
	for (auto& sub : doList)
	{
		auto dto = InoutCategoryDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, type,Type,sort, Sort);
		pageDto->addData(dto);
	}
	//补全分页参数
	pageDto->pageIndex = query->pageIndex;
	pageDto->pageSize = query->pageSize;
	pageDto->total = total;
	pageDto->calcPages();

	// 返回 pageDto 给 Controller
	return pageDto;
}

//获取指定类别详情
InoutCategoryDetailDTO::Wrapper InoutCategoryService::getById(const string& id)
{
	//实例化 dao
	InoutCategoryDAO dao;
	//调用dao
	auto inoutDo = dao.selectById(id);
	if (!inoutDo)return nullptr;
	//do转dto
	auto dto = InoutCategoryDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, inoutDo, id, Id, name, Name, type, Type, sort, Sort,data, Data);
	return dto;
}

// ==================== 新增收支类别数据实现 ====================
std::string InoutCategoryService::AddInoutCategory(const InoutCategoryAddDTO::Wrapper& dto)
{
	// 组装DO数据
	InoutCategoryDO inoutcategory;
	ZO_STAR_DOMAIN_DTO_TO_DO(inoutcategory, dto, Name, name, Type, type, Sort, sort, Data, data);
	//生成ID
	UuidFacade uf;
	inoutcategory.setId(uf.genUuid());
	// 执行数据添加
	InoutCategoryDAO dao;
	return dao.insert(inoutcategory) == 1 ? inoutcategory.getId() : "";
}

// ==================== 修改收支类别数据实现 ====================
bool InoutCategoryService::ModifyInoutCategory(const InoutCategoryUpdateDTO::Wrapper& dto)
{
	// 组装DO数据
	InoutCategoryDO inoutcategory;
	ZO_STAR_DOMAIN_DTO_TO_DO(inoutcategory, dto, Id, id, Name, name, Type, type, Sort, sort, Data, data);
	InoutCategoryDAO dao;
	return dao.update(inoutcategory) == 1;
}

// ==================== 删除收支类别数据实现 ====================
bool InoutCategoryService::RemoveInoutCategory(const oatpp::String& id)
{
	InoutCategoryDAO dao;
	return dao.deleteById<InoutCategoryDO>(std::string(id)) == 1;
}