#pragma once

#ifndef _WAREHOUSEDTO_H_
#define _WAREHOUSEDTO_H_

#include "GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 仓库列表查询传输数据对象
 */
class WareListDTO : public oatpp::DTO
{
	//初始化DTO
	DTO_INIT(WareListDTO, DTO);
	//仓库id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("ware.field.id"));
	//仓库名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("ware.field.name"));
	//仓库编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("ware.field.number"));
	//所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("ware.field.frame"));
	// 仓库备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("ware.field.data"));
};

/**
 * 仓库分页查询数据传输对象
 */
class WareListPageDTO : public PageDTO<WareListDTO::Wrapper>
{
	//初始化DTO
	DTO_INIT(WareListPageDTO, PageDTO<WareListDTO::Wrapper>);
};

/*
* 仓库名称列表数据传输对象
*/
class WareNameListDTO : public oatpp::DTO
{
	//初始化DTO
	DTO_INIT(WareNameListDTO, DTO);
	//仓库id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("ware.field.id"));
	//仓库名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("ware.field.name"));
	//仓库编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("ware.field.number"));
};

//
//class WareNameListPageDTO : public PageDTO<WareNameListDTO::Wrapper>
//{
//	//初始化DTO
//	DTO_INIT(WareNameListPageDTO, PageDTO < WareNameListDTO::Wrapper>);
//};

/**
 * 新增仓库数据传输对象
 */
class WarehouseAddDTO : public oatpp::DTO
{
	DTO_INIT(WarehouseAddDTO, DTO);
	// 仓库名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("ware.field.name"), true);
	// 仓库编号
	API_DTO_FIELD_REQUIRE(String, number, ZH_WORDS_GETTER("ware.field.number"), true);
	// 仓库所属组织
	API_DTO_FIELD_REQUIRE(String, frame, ZH_WORDS_GETTER("ware.field.frame"), true);
	// 仓库联系人员
	API_DTO_FIELD_REQUIRE(String, contacts, ZH_WORDS_GETTER("ware.field.contacts"), false);
	// 仓库联系电话
	API_DTO_FIELD_REQUIRE(String, tel, ZH_WORDS_GETTER("ware.field.tel"), false);
	// 仓库地址
	API_DTO_FIELD_REQUIRE(String, add, ZH_WORDS_GETTER("ware.field.add"), false);
	// 仓库备注信息
	API_DTO_FIELD_REQUIRE(String, data, ZH_WORDS_GETTER("ware.field.data"), false);

	
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/*
* 仓库详情数据传输对象
*/
class WarehouseDetailDTO : public WarehouseAddDTO
{
	DTO_INIT(WarehouseDetailDTO, WarehouseAddDTO);
	// 仓库唯一id
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("ware.field.id"), true);
};


#include OATPP_CODEGEN_END(DTO)
#endif 