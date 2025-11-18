#include "stdafx.h"
#include "GoodsCategoryService.h"
#include "../../dao/goods-category/GoodsCategoryDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"


// 新增：按ID获取类别树（默认ID为0）
#include "GoodsCategoryService.h"
// ... 现有代码 ...

// 按ID获取类别树JSON
std::string GoodsCategoryService::getCategoryTreeJsonById(const std::string& rootId) {
	// 参数验证
	if (rootId.empty()) {
		return "{}";
	}

	// 调用DAO获取JSON
	GoodsCategoryDAO dao;
	return dao.selectCategoryTreeJsonById(rootId);
}

// 获取商品类别树形结构
oatpp::Vector<GoodsCategoryDTO::Wrapper> GoodsCategoryService::getCategoryTree() {
    // 1. 从 DAO 层获取原始商品类别树数据（DO 类型）
    GoodsCategoryDAO dao;
    std::list<GoodsCategoryDO> doList = dao.selectCategoryTree(); // 调用 DAO 递归查询方法

    // 2. 将 DO 列表转换为 DTO 列表（业务对象 -> 传输对象）
    std::list<GoodsCategoryDTO::Wrapper> dtoList;
    for (const auto& doItem : doList) {
        // 创建 DTO 智能指针
        auto dto = GoodsCategoryDTO::createShared();
        // 使用框架提供的宏快速映射 DO 字段到 DTO（字段名需一一对应）
        ZO_STAR_DOMAIN_DO_TO_DTO(
            dto,          // 目标 DTO 对象
            doItem,       // 源 DO 对象
            id, Id,       // DO的id 映射到 DTO的Id
            pid, Pid,     // DO的pid 映射到 DTO的Pid
            name, Name,   // DO的name 映射到 DTO的Name
            sort, Sort,   // DO的sort 映射到 DTO的Sort
            data, Data    // DO的data 映射到 DTO的Data
        );
        dtoList.push_back(dto); // 添加到 DTO 列表
    }

    // 3. 将 std::list 转换为 Oatpp 支持的 oatpp::Vector 容器（适配序列化）
    auto vectorData = oatpp::Vector<GoodsCategoryDTO::Wrapper>::createShared();
    for (const auto& dtoItem : dtoList) {
        vectorData->push_back(dtoItem);
    }

    // 4. 返回转换后的容器（供控制器层序列化返回）
    return vectorData;
}


// 分页查询商品类别
GoodsCategoryPageDTO::Wrapper GoodsCategoryService::listAll(const GoodsCategoryQuery::Wrapper& query) {
    auto pageDTO = GoodsCategoryPageDTO::createShared();
    pageDTO->pageIndex = query->pageIndex;
    pageDTO->pageSize = query->pageSize;

    GoodsCategoryDAO dao;
    uint64_t total = dao.count(query);
    if (total <= 0) {
        return pageDTO;
    }

    pageDTO->total = total;
    pageDTO->calcPages();

    std::list<GoodsCategoryDO> doList = dao.selectWithPage(query);
    for (const auto& doItem : doList) {
        auto dto = GoodsCategoryDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, doItem, id, Id, pid, Pid, name, Name, sort, Sort, data, Data);
        pageDTO->addData(dto);
    }

    return pageDTO;
}

// 通过名称获取商品类别
GoodsCategoryDTO::Wrapper GoodsCategoryService::getByName(const std::string& name) {

    GoodsCategoryDAO dao;
    auto res = dao.selectByName(name);
    // 没有查询到数据
    if (!res)
        return nullptr;
    // 查询到数据转换成DTO
    auto dto = GoodsCategoryDTO::createShared();
    ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, pid, Pid, name, Name, sort, Sort, data, Data);
    return dto;
}

// 通过ID获取商品类别
GoodsCategoryDTO::Wrapper GoodsCategoryService::getById(const std::string& id)
{
    // 查询数据
    GoodsCategoryDAO dao;
    auto res = dao.selectById(id);
    // 没有查询到数据
    if (!res)
        return nullptr;
    // 查询到数据转换成DTO
    auto dto = GoodsCategoryDTO::createShared();
    ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, pid, Pid, name, Name, sort, Sort, data, Data);
	return dto;
}

// 保存商品类型
GoodsCategoryDTO::Wrapper GoodsCategoryService::saveData(const GoodsCategoryAddDTO::Wrapper& dto) {

	// 数据转换
	GoodsCategoryDO goodsCategoryDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(goodsCategoryDO, dto, Pid, pid, Name, name, Sort, sort, Data, data);

	// 生成随机id值
	UuidFacade uf;
	string id = uf.genUuid();
	goodsCategoryDO.setId(id);
	
	// 保存数据
	GoodsCategoryDAO dao;

	if (dao.insert(goodsCategoryDO)) {
		// 查询到数据转换成DTO
		auto res = GoodsCategoryDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(res, goodsCategoryDO, id, Id, pid, Pid, name, Name, sort, Sort, data, Data);
		return res;
	}
	return nullptr;

}

// 更新商品类型
GoodsCategoryDTO::Wrapper GoodsCategoryService::updateData(const GoodsCategoryDTO::Wrapper& dto) {

	
	if (!dto || !dto->id)
	{
		std::cout << "参数不全，请输入完整参数" << std::endl;
		return {};
	}

	// 执行数据修改
	GoodsCategoryDAO dao;
	// 取出需要修改的类型的原名称
	PtrGoodsCategoryDO curCategory = dao.selectById(dto->id);
	if (curCategory == nullptr)
	{
		std::cout << "要更新的商品类别不存在！" << std::endl;
		return nullptr;
	}
	
	// 组装DO数据
	GoodsCategoryDO goodsCategoryDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(goodsCategoryDO, dto, Id, id, Pid, pid, Name, name, Sort, sort, Data, data);

	// 修改当前类型的元素
	int curRow = dao.update(goodsCategoryDO);
	if (curRow != 1)
	{
		std::cout << "更新失败" << std::endl;
		return nullptr;
	}

	// 查询到数据转换成DTO
	auto res = GoodsCategoryDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO(res, goodsCategoryDO, id, Id, pid, Pid, name, Name, sort, Sort, data, Data);

	// 返回结果
	return res;
}

// 通过id主键删除商品类型
GoodsCategoryDeleteDTO::Wrapper GoodsCategoryService::removeDataById(const std::string& id) {

	GoodsCategoryDAO dao;

	// 先获取当前的商品类型
	PtrGoodsCategoryDO curCategory = dao.selectById(id);
	if (curCategory == nullptr)
	{
		std::cout << "要删除的商品类别不存在！" << std::endl;
		return nullptr;
	}

	// 查询到数据转换成DTO
	auto res = GoodsCategoryDeleteDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(res, curCategory, id, Id);

	// 获取子类数据
	std::list<PtrGoodsCategoryDO> childCategorys = dao.selectByPId(id);
	if (!childCategorys.empty()) {
		// 存在子类型，不能删除
		std::cout << "存在子数据，删除失败！" << std::endl;
		return nullptr;
	}

	// 无子类型，执行删除
	int rows = dao.deleteById<GoodsCategoryDO>(id);

	// 删除成功返回真
	if (rows == 1)
	{
		return res;
	}
	else {
		return nullptr;
	}
}
