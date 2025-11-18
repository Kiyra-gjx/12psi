#pragma once
#ifndef _ATTACHMENT_MAPPER_H_
#define _ATTACHMENT_MAPPER_H_
#include "Mapper.h"                  // 项目基础 Mapper 类
#include "../../domain/do/attachment/AttachmentDO.h"

/**
 * 附件表匹配映射
 */
class AttachmentMapper : public Mapper<PtrFileViewDO>
{
public:
	PtrFileViewDO mapper(ResultSet* resultSet) const override
	{
		PtrFileViewDO file = std::make_shared<AttachmentViewDO>();
		file->setId(resultSet->getString("id"));
		file->setName(resultSet->getString("name"));
		file->setFile_type(resultSet->getString("file_type"));
		file->setSave_type(resultSet->getString("save_type"));
		file->setSave_path(resultSet->getString("save_path"));
		file->setRemark(resultSet->getString("remark"));
		file->setStatus(resultSet->getInt("status"));

		return file;
	}
};
#endif