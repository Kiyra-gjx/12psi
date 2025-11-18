#pragma once
#ifndef _WAREHOUSE_DO_
#define _WAREHOUSE_DO_
#include "DoInclude.h"
#include "GlobalInclude.h"
/**
 * 示例数据库实体类-快乐五香蛋
 */
class WarehouseDO : public BaseDO
{
	// 仓库Id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 仓库名称
	MYSQL_SYNTHESIZE(string, name, Name);
	//仓库编号
	MYSQL_SYNTHESIZE(string, number, Number);
	// 所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	// 联系人员
	MYSQL_SYNTHESIZE(string, contacts, Contacts);
	// 联系电话
	MYSQL_SYNTHESIZE(string, tel, Tel);
	// 仓库地址
	MYSQL_SYNTHESIZE(string, add, Add);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
public:
	WarehouseDO() : BaseDO("warehouse")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("number", "s", number);
		MYSQL_ADD_FIELD("frame", "s", frame);
		MYSQL_ADD_FIELD("contacts", "s", contacts);
		MYSQL_ADD_FIELD("tel", "s", tel);
		MYSQL_ADD_FIELD("`add`", "s", add);
		MYSQL_ADD_FIELD("data", "s", data);
	}
};

// 给WarehouseDO智能指针设定一个别名方便使用
typedef std::shared_ptr<WarehouseDO> PtrWarehouseDO;
#endif // !_WAREHOUSE_DO_
