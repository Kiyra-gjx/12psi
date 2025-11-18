#pragma once
#include "../DoInclude.h"

/**
 * 商品类别数据实体
 */
class GoodsCategoryDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 父类别ID
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 类别名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 排序号
	MYSQL_SYNTHESIZE(int, sort, Sort);
	// 备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
public:
	GoodsCategoryDO() : BaseDO("category")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("sort", "i", sort);
		MYSQL_ADD_FIELD("data", "s", data);
	}

};

// 智能指针定义
typedef std::shared_ptr<GoodsCategoryDO> PtrGoodsCategoryDO;
