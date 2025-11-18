#pragma

#ifndef _CATEGORYDO_H_
#define _CATEGORYDO_H_
#include "DoInclude.h"

/*
* 商品类别存储数据对象
*/
class CategoryDO : public BaseDO
{
	// 商品类别唯一标识
	MYSQL_SYNTHESIZE(string, id, Id); 
	// 商品所属类别
	MYSQL_SYNTHESIZE(string, pid, Pid);
	// 商品类别名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 商品类别排序
	MYSQL_SYNTHESIZE(int, sort, Sort);
	// 商品类别备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
public:
	CategoryDO() : BaseDO("category")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("pid", "s", pid);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name,false);
		MYSQL_ADD_FIELD("sort", "i", sort);
		MYSQL_ADD_FIELD("data", "s", data);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<CategoryDO> PtrCategoryDO;

#endif