#ifndef _WAREHOUSEQUERY_H_
#define _WAREHOUSEQUERY_H_

#include "GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class WarehouseQuery : public PageQuery
{
	//初始化
	DTO_INIT(WarehouseQuery, PageQuery);
	//仓库名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("ware.field.name"));
	//仓库编号
	API_DTO_FIELD_DEFAULT(String, number, ZH_WORDS_GETTER("ware.field.number"));
	//联系人员
	API_DTO_FIELD_DEFAULT(String, contacts, ZH_WORDS_GETTER("ware.field.contacts"));
	//联系电话
	API_DTO_FIELD_DEFAULT(String, tel, ZH_WORDS_GETTER("ware.field.tel"));
	//仓库地址
	API_DTO_FIELD_DEFAULT(String, add, ZH_WORDS_GETTER("ware.field.add"));
	//备注信息
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("ware.field.data"));

};
#include OATPP_CODEGEN_END(DTO)
#endif 