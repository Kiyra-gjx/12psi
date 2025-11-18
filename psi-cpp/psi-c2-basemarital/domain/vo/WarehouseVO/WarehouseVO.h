#ifndef _WAREHOUSEVO_H_
#define _WAREHOUSEVO_H_

#include "GlobalInclude.h"
#include "dto/WarehouseDTO/WarehouseDTO.h"
// 引入 oatpp 的 List 类型定义
//#include "oatpp/core/collection/List.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 仓库列表分页显示JsonVO，用于响应客户端的Json数据
 */
class WareListPageJsonVO : public JsonVO<WareListPageDTO::Wrapper> {
    DTO_INIT(WareListPageJsonVO, JsonVO<WareListPageDTO::Wrapper>);
};

/**
 * 仓库名称列表显示JsonVO，用于响应客户端的Json数据
 * 修复：使用 oatpp::List 完整类型，并正确嵌套模板参数
 */
class WareNameListJsonVO : public JsonVO<oatpp::List<WareNameListDTO::Wrapper>> {
    DTO_INIT(WareNameListJsonVO, JsonVO<oatpp::List<WareNameListDTO::Wrapper>>);
};


/*
* 添加仓库JsonVO，用于响应客户端的Json数据
*/
class WarehouseAddJsonVO : public JsonVO<WarehouseAddDTO::Wrapper>
{
	DTO_INIT(WarehouseAddJsonVO, JsonVO<WarehouseAddDTO::Wrapper>);

	// 仓库唯一id(新增之后需要把id添加上去一起返回给前端，前端才方便展示和修改)
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("ware.field.id"), true);
};

/*
* 仓库详情JsonVO，用于响应客户端的Json数据
*/
class WarehouseDetailJsonVO : public JsonVO<WarehouseDetailDTO::Wrapper>
{
    DTO_INIT(WarehouseDetailJsonVO, JsonVO<WarehouseDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif