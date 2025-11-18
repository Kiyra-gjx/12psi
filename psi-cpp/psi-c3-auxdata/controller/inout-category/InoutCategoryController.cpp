#include "InoutCategoryController.h"
#include "service/inout-category/InoutCategoryService.h"

// ==================== 收支类别控制器实现 ====================

/**
 * 获取收支类别名称列表的业务逻辑实现
 * @param query 查询条件对象
 * @return 类别简单对象列表的VO包装器
 */
InoutCategorySimpleListVO::Wrapper InoutCategoryController::execQueryCategoryNames(const InoutCategoryQuery::Wrapper& query)
{
	//创建响应 VO 对象
	auto vo = InoutCategorySimpleListVO::createShared();
	
	if (query->type != nullptr) // 检查可选的 type 字段是否被传入
	{
		// 如果传入了，检查值是否在 0 或 1 范围内
		if (*(query->type) != 0 && *(query->type) != 1)
		{
			vo->init(nullptr, ResultStatus("收支类型（type）参数只能为0或1"));
			return vo;
		}
	}

	// 定义 Service 实例
	InoutCategoryService service;
	//调用service
	auto dtoList = service.listNames(query);
	//封装响应
	vo->success(dtoList);
	//返回响应
	return vo;
}

/**
 * 分页查询收支类别列表的业务逻辑实现
 * @param query 查询条件对象（包含分页参数）
 * @return 分页结果包装器
 */
InoutCategoryPageVO::Wrapper InoutCategoryController::execQueryPage(const InoutCategoryPageQuery::Wrapper& query)
{
	//创建vo
	auto vo = InoutCategoryPageVO::createShared();

	if (query->pageIndex == nullptr || *(query->pageIndex) <= 0)
	{
		vo->init(nullptr, ResultStatus("页码必须大于0"));
		return vo;
	}
	if (query->pageSize == nullptr || *(query->pageSize) <= 0)
	{
		vo->init(nullptr, ResultStatus("每页数量必须大于0"));
		return vo;
	}
	if (query->type != nullptr) // 检查可选的 type 字段是否被传入
	{
		// 如果传入了，检查值是否在 0 或 1 范围内
		if (*(query->type) != 0 && *(query->type) != 1)
		{
			vo->init(nullptr, ResultStatus("收支类型（type）参数只能为0或1"));
			return vo;
		}
	}
	// 定义 Service 实例
	InoutCategoryService service;
	//调用service
	auto dtoPage = service.listPage(query);
	//封装响应
	vo->success(dtoPage);
	//返回响应
	return vo;
}

/**
 * 根据ID查询收支类别详情的业务逻辑实现
 * @param id 类别ID
 * @return 单个类别详情包装器
 */
InoutCategoryDetailVO::Wrapper InoutCategoryController::execQueryById(const String& id)
{
	//创建vo
	auto vo = InoutCategoryDetailVO::createShared();
	if (!id || id->empty())
	{
		vo->init(nullptr, ResultStatus("id不能为空"));
		return vo;
	}
	// 定义 Service 实例
	InoutCategoryService service;
	//调用service
	auto dto = service.getById(id.getValue({}));
	//封装响应
	if (!dto) {
		vo->init(nullptr, ResultStatus("查询的类别不存在"));
	}
	else {
		vo->success(dto);
	}
	//返回响应
	return vo;
}

/**
 * 新增单个收支类别的业务逻辑实现
 * @param dto 要新增的 InoutCategoryAddDTO 对象
 * @return 新增后的 InoutCategoryDetailVO 包装器
 */
InoutCategoryDetailVO::Wrapper InoutCategoryController::execAddInoutCategory(const InoutCategoryAddDTO::Wrapper& dto)
{
	// 调用 Service 完成持久化
	InoutCategoryService service;
	std::string id = service.AddInoutCategory(dto);

	auto result = InoutCategoryDetailVO::createShared();

	if (!id.empty()) {
		result->setStatus(RS_SUCCESS);

		// 创建并填充返回对象
		result->data = InoutCategoryDetailDTO::createShared();
		result->data->id = id;
		result->data->name = dto->name;
		result->data->type = dto->type;
		result->data->sort = dto->sort;
		result->data->data = dto->data;
	}
	else {
		result->setStatus(RS_FAIL);
		result->data = InoutCategoryDetailDTO::createShared();
	}

	return result;
}

/**
 * 修改单个收支类别的业务逻辑实现
 * @param dto 要修改的 InoutCategoryUpdateDTO 对象
 * @return 修改后的 InoutCategoryDetailVO 包装器
 */
//InoutCategoryDetailVO::Wrapper InoutCategoryController::execModifyInoutCategory(const InoutCategoryUpdateDTO::Wrapper& dto)
//{
//	// TODO: 调用 Service/DAO 执行实际更新逻辑
//
//	auto result = InoutCategoryDetailVO::createShared();
//	result->setStatus(RS_SUCCESS);
//
//	// 返回一个空的对象
//	result->data = InoutCategoryDetailDTO::createShared();
//
//	return result;
//}
InoutCategoryDetailVO::Wrapper InoutCategoryController::execModifyInoutCategory(const InoutCategoryUpdateDTO::Wrapper& dto)
{
	auto result = InoutCategoryDetailVO::createShared();
	// 校验dto
	if (!dto || !dto->id) {
		result->init(nullptr, RS_PARAMS_INVALID);
		return result;
	}
	// 定义一个Service
	InoutCategoryService service;
	// 执行数据修改
	if (service.ModifyInoutCategory(dto)) {
		// 修改成功后，调用getById获取最新数据
		auto updatedDto = service.getById(dto->id.getValue({}));
		if (updatedDto) {
			result->success(updatedDto);
		}
		else {
			result->init(nullptr, ResultStatus("修改成功，但获取更新后的数据失败"));
		}
	}
	else {
		result->fail(nullptr);
	}

	return result;
}
/**
 * 删除单个收支类别的业务逻辑实现
 */
BooleanJsonVO::Wrapper InoutCategoryController::execRemoveInoutCategory(const String& id)
{
	// TODO: 调用 Service/DAO 执行实际删除逻辑

	auto result = BooleanJsonVO::createShared();
	// 校验id
	if (id->empty()) {
		result->init(nullptr, RS_PARAMS_INVALID);
		return result;
	}
	// 定义一个Service
	InoutCategoryService service;
	// 执行数据删除
	if (service.RemoveInoutCategory(id)) {
		result->success(true);
	}
	else
	{
		result->fail(false);
	}
	// 响应结果
	return result;
}