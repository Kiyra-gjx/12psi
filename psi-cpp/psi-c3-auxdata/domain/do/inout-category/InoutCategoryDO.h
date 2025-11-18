/*
	负责人：绿皮怪
	时间：2025.10.20
*/
#ifndef _INOUTCATEGORY_DO_
#define _INOUTCATEGORY_DO_
#include "../DoInclude.h"

/**
 * 收支类别-实体类 (对应 'iet' 表)
 */
class InoutCategoryDO : public BaseDO
{
	// 编号 (varchar(32))
	MYSQL_SYNTHESIZE(string, id, Id);	
	// 类别名称 (varchar(32))
	MYSQL_SYNTHESIZE(string, name, Name);
	// 收支类型 (tinyint(1))
	MYSQL_SYNTHESIZE(int, type, Type);
	// 类别排序 (int(11))
	MYSQL_SYNTHESIZE(int, sort, Sort);
	// 备注信息 (varchar(256), nullable)
	MYSQL_SYNTHESIZE(string, data, Data);
public:
    // [修正] 表名必须与数据库 "iet" 匹配
	InoutCategoryDO() : BaseDO("iet") 
	{
		// 字段映射
		MYSQL_ADD_FIELD_PK("id", "s", id);       // 主键 id (类型 's' for string)
		MYSQL_ADD_FIELD("name", "s", name);      // 类别名称 (NOT NULL)
		MYSQL_ADD_FIELD("type", "i", type);      // 收支类型 (NOT NULL)
		MYSQL_ADD_FIELD("sort", "i", sort);      // 类别排序 (NOT NULL)
        
        // [修正] data 字段允许 NULL, 必须使用 _NULLABLE 宏
        // [修正] 宏参数应为 'data', 而不是 'this->data'
		MYSQL_ADD_FIELD_NULLABLE("data", "s", this->data, true); 
	}
};

// 给InoutCategoryDO智能指针设定一个别名方便使用
typedef std::shared_ptr<InoutCategoryDO> PtrInoutCategoryDO;
#endif // !_INOUTCATEGORY_DO_