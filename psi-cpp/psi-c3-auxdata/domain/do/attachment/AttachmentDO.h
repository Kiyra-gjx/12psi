#ifndef ATTACHMENTDO_H 
#define ATTACHMENTDO_H
#include "../DoInclude.h"

/**
 * 测试文件存储数据模型
 */
class AttachmentDO :public BaseDO
{
	// 文件唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 文件名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 文件存储类型编码
	MYSQL_SYNTHESIZE(string, file_type, File_type);
	// 文件存储方式编码
	MYSQL_SYNTHESIZE(string, save_type, Save_type);
	// 文件存储路径
	MYSQL_SYNTHESIZE(string, save_path, Save_path);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 数据状态
	MYSQL_SYNTHESIZE(int, status, Status);
public:
	AttachmentDO() : BaseDO("annex")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD_NULLABLE("file_type", "s", file_type, false);
		MYSQL_ADD_FIELD_NULLABLE("save_type", "s", save_type, false);
		MYSQL_ADD_FIELD_NULLABLE("save_path", "s", save_path, false);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD_NULLABLE("status", "i", status, false);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<AttachmentDO> PtrAttachmentDO;

/**
 * 文件视图对象，关联一些外表的字段
 */
class AttachmentViewDO : public AttachmentDO {
	// 文件类型名称
	MYSQL_SYNTHESIZE(string, fileTypeName, FileTypeName);
	// 文件保存类型名称
	MYSQL_SYNTHESIZE(string, saveTypeName, SaveTypeName);
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<AttachmentViewDO> PtrFileViewDO;

#endif 