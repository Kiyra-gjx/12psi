#pragma once
#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 客户端分页查询
class AttachmentQuery :public PageQuery
{
	DTO_INIT(AttachmentQuery, PageQuery);
	// id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("attachment.field.id");
	}
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("attachment.field.name");
	}

	DTO_FIELD(String, save_path);
	DTO_FIELD_INFO(save_path) {
		info->description = ZH_WORDS_GETTER("attachment.field.save_path");
	}
	DTO_FIELD(String, save_type);
	DTO_FIELD_INFO(save_type) {
		info->description = ZH_WORDS_GETTER("attachment.field.save_type");
	}
	DTO_FIELD(String, file_type);
	DTO_FIELD_INFO(file_type) {
		info->description = ZH_WORDS_GETTER("attachment.field.file_type");
	}
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("attachment.field.remark");
	}
	DTO_FIELD(Int32, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("attachment.field.status");
	}
};

#include OATPP_CODEGEN_END(DTO)