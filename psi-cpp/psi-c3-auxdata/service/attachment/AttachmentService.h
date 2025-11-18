#pragma once
#ifndef _ATTACHMENT_SERVICE_
#define _ATTACHMENT_SERVICE_

#ifndef _ATTACHMENTSERVICE_H_
#define _ATTACHMENTSERVICE_H_

#include "domain/dto/attachment/AttachmentDTO.h"
#include "domain/query/attachment/AttachmentQuery.h"
#include <oatpp/core/Types.hpp>
#include <string>
#include "domain/vo/attachment/AttachmentVO.h"
#include "domain/query/attachment/AttachmentQuery.h"
#include "domain/dto/attachment/AttachmentDTO.h"

/**
 * 附件服务实现
 */
struct AttachmentPageResult {
    uint32_t pageIndex;
    uint32_t pageSize;
    uint64_t total;
    uint32_t pageCount;
    std::vector<AttachmentDTO> data;
};
class AttachmentService
{
public:
    // 修改数据
    bool modifyData(const AttachmentDTO::Wrapper& dto);
    // 通过ID删除数据
    bool removeData(const AttachmentRemoveDTO::Wrapper& id);
    //保存文件
    std::string saveFile(const AttachmentDTO::Wrapper& data);
    //查询数据
    AttachmentPageResult listAll(const AttachmentQuery::Wrapper& query);
};
#endif
#endif
