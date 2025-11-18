#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 商品类别查询参数
 */
#include "domain/query/PageQuery.h"
class GoodsCategoryQuery : public PageQuery  // 继承PageQuery
{
	DTO_INIT(GoodsCategoryQuery, PageQuery);
	// 移除手动定义的pageIndex和pageSize（由PageQuery提供）
	// 保留业务查询字段：id,pid,name,sort,data
	DTO_FIELD(String, id, "id");
	DTO_FIELD(String, pid, "pid");
	DTO_FIELD(String, name, "name");     // 类别名称（支持模糊查询）
	DTO_FIELD(Int32, sort, "sort");      // 类别排序（按排序字段筛选）
	DTO_FIELD(String, data, "data");     // 备注信息（按备注筛选）
	// ...其他业务字段
};
#include OATPP_CODEGEN_END(DTO)
