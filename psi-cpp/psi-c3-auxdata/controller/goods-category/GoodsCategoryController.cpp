#include "GoodsCategoryController.h"
#include "../../service/goods-category/GoodsCategoryService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"

// 通过根节点ID获取商品类别树实现
StringJsonVO::Wrapper GoodsCategoryController::execGetGoodsCategoryTreeJsonById(const oatpp::String& rootId) {
	auto jvo = StringJsonVO::createShared();

	// 参数验证
	if (!rootId || rootId->empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 调用服务层获取JSON
	GoodsCategoryService service;
	std::string jsonResult = service.getCategoryTreeJsonById(rootId->c_str());

	if (jsonResult.empty() || jsonResult == "{}") {
		jvo->init(nullptr, ResultStatus(std::string("not found"),404));
	}
	else {
		jvo->success(oatpp::String(jsonResult.c_str()));
	}

	return jvo;
}

// 获取商品类别树实现
GoodsCategoryListJsonVO::Wrapper GoodsCategoryController::execGetGoodsCategoryTree() {
	auto jvo = GoodsCategoryListJsonVO::createShared();
	GoodsCategoryService service;
	auto treeData = service.getCategoryTree(); // 此时返回 oatpp::Vector
	jvo->success(treeData); // 正确序列化
	return jvo;
}

// 分页查询商品类别实现
GoodsCategoryPageJsonVO::Wrapper GoodsCategoryController::execQueryGoodsCategory(const GoodsCategoryQuery::Wrapper& query)
{
	auto jvo = GoodsCategoryPageJsonVO::createShared();
	GoodsCategoryService service;
	auto result = service.listAll(query);

	jvo->success(result);
	return jvo;
	return nullptr;
}

// 按ID查询商品类别实现
GoodsCategoryJsonVO::Wrapper GoodsCategoryController::execQueryById(const String& id)
{
	//	// 定义返回数据对象
	auto jvo = GoodsCategoryJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 定义一个Service
	GoodsCategoryService service;
	// 执行数据新增
	auto res = service.getById(id.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
	return nullptr;
}

// 按名称查询商品类别实现
GoodsCategoryJsonVO::Wrapper GoodsCategoryController::execQueryByName(const oatpp::String& name) { 
	auto jvo = GoodsCategoryJsonVO::createShared();

	// 参数校验
	// 非空校验
	if (!name)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 定义一个Service
	GoodsCategoryService service;
	// 执行数据新增
	auto res = service.getByName(name.getValue({}));
	jvo->success(res);

	//响应结果
	return jvo;
	return nullptr;
}
// 新增商品类别实现
GoodsCategoryJsonVO::Wrapper GoodsCategoryController::execAddGoodsCategory(const GoodsCategoryAddDTO::Wrapper& dto)
{
	// 定义返回数据对象
	auto jvo = GoodsCategoryJsonVO::createShared();
	// 非空校验
	if (!dto->name)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 保存数据
	GoodsCategoryService service;
	auto res = service.saveData(dto);
	if (res) {
		jvo->success(res);
	}
	else
	{
		jvo->fail(nullptr);
	}
	return jvo;
}

// 通过id主键修改商品类别
GoodsCategoryJsonVO::Wrapper GoodsCategoryController::execModifyGoodsCategory(const GoodsCategoryDTO::Wrapper& dto)
{
	// 定义返回数据对象
	auto jvo = GoodsCategoryJsonVO::createShared();
	// 非空校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 定义一个Service
	GoodsCategoryService service;
	// 执行数据修改
	auto res = service.updateData(dto);
	if (res) {
		jvo->success(res);
	}
	else
	{
		jvo->fail(nullptr);
	}

	// 响应结果
	return jvo;
}


// 通过id主键删除商品类别
BooleanJsonVO::Wrapper GoodsCategoryController::execRemoveGoodsCategory(const GoodsCategoryDeleteDTO::Wrapper& dto)
{
	// 定义返回数据对象
	auto jvo = BooleanJsonVO::createShared();
	// 参数校验
	if (!dto->id || dto->id->empty())
	{
		jvo->init(false, RS_PARAMS_INVALID);
		return jvo;
	}
	// 定义一个Service
	GoodsCategoryService service;

	// 执行数据删除
	auto res = service.removeDataById(dto->id);
	if (res) {
		jvo->success(true);
	}
	else
	{
		jvo->fail(false);
	}
	// 响应结果
	return jvo;
}