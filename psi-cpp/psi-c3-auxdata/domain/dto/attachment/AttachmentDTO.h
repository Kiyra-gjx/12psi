#pragma once
#ifndef _ATTACHMENT_DTO_
#define _ATTACHMENT_DTO_
#include "../../GlobalInclude.h"
#include "../../dto/attachment/AttachmentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个附件数据传输模型
 * 用于接收前端传递的附件修改参数
 */

class AttachmentRemoveDTO : public oatpp::DTO
{
    DTO_INIT(AttachmentRemoveDTO, DTO);

    //附件唯一标识
    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("attachment.field.id"));

    //文件存储路径，不要将服务器域名和端口存储到数据库
    API_DTO_FIELD_DEFAULT(String, save_path, ZH_WORDS_GETTER("attachment.field.save_path"));

    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};


class AttachmentDTO : public AttachmentRemoveDTO
{
    DTO_INIT(AttachmentDTO, AttachmentRemoveDTO);

    //文件名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("attachment.field.name"));

    //文件类型，值对应字典表value
    API_DTO_FIELD_DEFAULT(String, file_type, ZH_WORDS_GETTER("attachment.field.file_type"));

    //文件存储方式，值对应字典表value
    API_DTO_FIELD_DEFAULT(String, save_type, ZH_WORDS_GETTER("attachment.field.save_type"));

    //备注
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("attachment.field.remark"));

    //数据状态 0未使用 1使用中
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("attachment.field.status"));

    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

//需要传递的数据 查询的dto
class AttachmentQueryDTO : public AttachmentDTO
{
    DTO_INIT(AttachmentQueryDTO, AttachmentDTO);

    DTO_FIELD(UInt32, pageIndex);      // 当前页码
    DTO_FIELD(UInt32, pageSize);       // 每页大小
    DTO_FIELD(UInt64, total);          // 总记录数
    DTO_FIELD(UInt32, pageCount);      // 总页数
    DTO_FIELD(List<Object<AttachmentDTO>>, data);  // 数据列表

};


//添加文件的dto
class AttachmentAddDTO : public AttachmentDTO
{
    DTO_INIT(AttachmentAddDTO, AttachmentDTO);
    // 文件字段 - 必需
    API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
    //// 文件名 - 必需
    //API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("attachment.field.name"), true);
    //// 备注 - 可选
    //API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("attachment.field.remark"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_ATTACHMENT_DTO_