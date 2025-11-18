#pragma once
#ifndef _ATTACHMENT_DAO_
#define _ATTACHMENT_DAO_
#ifndef ATTACHMENTDAO_H 
#define ATTACHMENTDAO_H
#include "BaseDAO.h"
#include "domain/do/attachment/AttachmentDO.h"
#include "domain/dto/attachment/AttachmentDTO.h"
#include"domain/query/attachment/AttachmentQuery.h"

class AttachmentDAO : public BaseDAO
{
private:
	//************************************
	// Method:      queryConditionBuilder
	// FullName:    SampleDAO::queryConditionBuilder
	// Access:      private 
	// Returns:     std::string 返回条件SQL语句，即WHERE部分的语句
	// Parameter:   const SampleQuery::Wrapper& query 查询数据对象
	// Parameter:   SqlParams& params 存放查询数据的参数对象
	// Description: 查询条件构建器，根据SampleQuery对象动态构建查询条件相关参数
	//************************************
public:
	// 修改附件
	bool update(const PtrAttachmentDO& attachmentDO);
	// 删除附件
	bool deleteById(const std::string& id);

	std::string queryConditionBuilder(const AttachmentQuery::Wrapper& query, SqlParams& params);
	uint64_t count(const AttachmentQuery::Wrapper& query);

	std::list<PtrFileViewDO> selectAll(const AttachmentQuery::Wrapper& query);
	bool insert(const AttachmentDO& fdo);
};
#endif
#endif



