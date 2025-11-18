#pragma
#ifndef _SUPPLIER_DTO_H
#define _SUPPLIER_DTO_H

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/*
  新增供应商数据传输模型
*/
class SupplierAddDTO : public oatpp::DTO
{
	// 初始化DTO
	DTO_INIT(SupplierAddDTO, DTO)
	// 供应商名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("supplier.field.name"));
	// 供应商编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("supplier.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(Int32, frame, ZH_WORDS_GETTER("supplier.field.frame"));
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("supplier.field.py"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(Int32, user, ZH_WORDS_GETTER("supplier.field.user"));
	// 供应商类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("supplier.field.category"));
	// 增值税税率
	API_DTO_FIELD_DEFAULT(Float32, rate, ZH_WORDS_GETTER("supplier.field.rate"));
	// 开户银行
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("supplier.field.bank"));
	// 银行账号
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("supplier.field.account"));
	// 纳税号码
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("supplier.field.tax"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("supplier.field.data"));
	// 联系资料
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("supplier.field.contacts"));
};

class SupplierUpdateDTO : public SupplierAddDTO
{
	// 初始化DTO
	DTO_INIT(SupplierUpdateDTO, SupplierAddDTO)
		// 供应商id
		API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("supplier.field.id"));
};

class SupplierDTO : public oatpp::DTO
{
	DTO_INIT(SupplierDTO, DTO);
	// id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("supplier.field.id"));
	// 供应商名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("supplier.field.name"));
	// 拼音信息
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("supplier.field.py"));
	// 供应商编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("supplier.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("supplier.field.frame"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("supplier.field.user"));
	// 供应商类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("supplier.field.category"));
	// 增值税税率
	API_DTO_FIELD_DEFAULT(Float64, rate, ZH_WORDS_GETTER("supplier.field.rate"));
	// 开户银行
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("supplier.field.bank"));
	// 银行账号
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("supplier.field.account"));
	// 纳税号码
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("supplier.field.tax"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("supplier.field.data"));
	// 联系资料
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("supplier.field.contacts"));
	// 应付款余额
	API_DTO_FIELD_DEFAULT(Float64, balance, ZH_WORDS_GETTER("supplier.field.balance"));
	// 扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("supplier.field.more"));
};

//列表DTO
class SupplierListDTO : public oatpp::DTO
{
	DTO_INIT(SupplierListDTO, DTO);
	// id
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("supplier.field.id"));
	// 供应商名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("supplier.field.name"));
	// 拼音信息
	API_DTO_FIELD_DEFAULT(String, py, ZH_WORDS_GETTER("supplier.field.py"));
	// 供应商编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("supplier.field.number"));
	// 所属组织
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("supplier.field.frame"));
	// 所属用户
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("supplier.field.user"));
	// 供应商类别
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("supplier.field.category"));
	// 增值税税率
	API_DTO_FIELD_DEFAULT(Float32, rate, ZH_WORDS_GETTER("supplier.field.rate"));
	// 开户银行
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("supplier.field.bank"));
	// 银行账号
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("supplier.field.account"));
	// 纳税号码
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("supplier.field.tax"));
	// 备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("supplier.field.data"));
	// 联系资料
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("supplier.field.contacts"));
	// 应付款余额
	API_DTO_FIELD_DEFAULT(Float32, balance, ZH_WORDS_GETTER("supplier.field.balance"));
	// 扩展信息
	API_DTO_FIELD_DEFAULT(String, more, ZH_WORDS_GETTER("supplier.field.more"));

};

//分页DTO
class SupplierListPageDTO : public PageDTO< SupplierListDTO::Wrapper>
{
	DTO_INIT(SupplierListPageDTO, PageDTO< SupplierListDTO::Wrapper>);

};

class SupplierPageDTO : public PageDTO<SupplierDTO::Wrapper>
{
	DTO_INIT(SupplierPageDTO, PageDTO<SupplierDTO::Wrapper>);
};

//供应商详情获取
class SupplierDetailDTO : public SupplierDTO
{
	DTO_INIT(SupplierDetailDTO, SupplierDTO);
};

class SupFileAddDTO : public oatpp::DTO
{
	DTO_INIT(SupFileAddDTO, DTO);
	// 文件名
	API_DTO_FIELD_DEFAULT(String, filename, ZH_WORDS_GETTER("sup.field.filename"));
	// 文件类型编码
	API_DTO_FIELD_REQUIRE(String, fileType, ZH_WORDS_GETTER("sup.field.ft"), true);
	// 文件存储类型编码
	API_DTO_FIELD_REQUIRE(String, saveType, ZH_WORDS_GETTER("sup.field.st"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("sup.field.remark"));
	//数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("sup.field.file"), true);
};


#include OATPP_CODEGEN_END(DTO)
#endif