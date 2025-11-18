#pragma once
#ifndef _SUPPLIER_QUERY_
#define _SUPPLIER_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class SupplierQuery : public PageQuery
{
	DTO_INIT(SupplierQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("sup.field.id"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("sup.field.name"));
	API_DTO_FIELD_DEFAULT(String, category, ZH_WORDS_GETTER("sup.field.category"));
	API_DTO_FIELD_DEFAULT(String, rate, ZH_WORDS_GETTER("sup.field.rate"));
	API_DTO_FIELD_DEFAULT(String, bank, ZH_WORDS_GETTER("sup.field.bank"));
	API_DTO_FIELD_DEFAULT(String, account, ZH_WORDS_GETTER("sup.field.account"));
	API_DTO_FIELD_DEFAULT(String, tax, ZH_WORDS_GETTER("sup.field.tax"));
	API_DTO_FIELD_DEFAULT(String, balance, ZH_WORDS_GETTER("sup.field.balance"));
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("sup.field.frame"));
	API_DTO_FIELD_DEFAULT(String, user, ZH_WORDS_GETTER("sup.field.user"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("sup.field.data"));
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("sup.field.contacts"));
};

class SupQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(SupQuery, PageQuery);
	
};


#include OATPP_CODEGEN_END(DTO)

#endif