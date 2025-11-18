#include "stdafx.h"
#include "../../dao/attachment/AttachmentDAO.h"
#include "SimpleDateTimeFormat.h"
#include"service/attachment/AttachmentService.h"
#include "id/UuidFacade.h"
#include "domain/do/attachment/AttachmentDO.h"

bool AttachmentService::modifyData(const AttachmentDTO::Wrapper& dto)
{
    // 组装DO数据
    auto data = std::make_shared<AttachmentDO>();
    data->setId(dto->id.getValue(""));
    data->setName(dto->name.getValue(""));
    data->setFile_type(dto->file_type.getValue(""));
    data->setSave_type(dto->save_type.getValue(""));
    data->setSave_path(dto->save_path.getValue(""));
    data->setRemark(dto->remark.getValue(""));
    data->setStatus(dto->status.getValue(0));
    // 执行数据修改
    AttachmentDAO dao;
    return dao.update(data) == 1;
}

bool AttachmentService::removeData(const AttachmentRemoveDTO::Wrapper& id)
{
    // 取出AttachmentRemoveDTO里的id
    std::string rid = id->id.getValue("");
    // 执行数据删除
    AttachmentDAO dao;
    return dao.deleteById(rid) == 1;
}

std::string AttachmentService::saveFile(const AttachmentDTO::Wrapper& data)
{

    UuidFacade uf;
    std::string id = uf.genUuid();
    std::cout << "Generated ID: " << id << std::endl;

    if (id.empty() || id.length() != 32) {
        std::cerr << "Invalid UUID generated: " << id << std::endl;
        return "";
    }
    AttachmentDO fdo;

    fdo.setId(id);
    fdo.setStatus(data->status.getValue(0));

    if (data->name && !data->name->empty()) {
        fdo.setName(data->name.getValue(""));
    }
    else {
        fdo.setName("");
    }

    if (data->file_type && !data->file_type->empty()) {
        fdo.setFile_type(data->file_type.getValue(""));
    }
    else {
        fdo.setFile_type("");
    }

    if (data->save_type && !data->save_type->empty()) {
        fdo.setSave_type(data->save_type.getValue(""));
    }
    else {
        fdo.setSave_type("");
    }

    if (data->save_path && !data->save_path->empty()) {
        fdo.setSave_path(data->save_path.getValue(""));
    }
    else {
        fdo.setSave_path("");
    }

    if (data->remark && !data->remark->empty()) {
        fdo.setRemark(data->remark.getValue(""));
    }
    else {
        fdo.setRemark("");
    }


    AttachmentDAO dao;
    if (dao.insert(fdo)) return id;
    return "";
}


AttachmentPageResult AttachmentService::listAll(const AttachmentQuery::Wrapper& query)
{
    AttachmentPageResult result;

    // 分页设置保持不变
    result.pageIndex = (query->pageIndex && *query->pageIndex > 0) ? *query->pageIndex : 1;
    result.pageSize = (query->pageSize && *query->pageSize > 0) ? *query->pageSize : 20;

    AttachmentDAO dao;
    result.total = dao.count(query);
    result.pageCount = (result.total + result.pageSize - 1) / result.pageSize;

    std::list<PtrFileViewDO> dbResult = dao.selectAll(query);

    // 修复：使用智能指针创建DTO对象
    for (PtrFileViewDO& sub : dbResult)
    {
        // 创建智能指针包装的DTO对象
        auto dto = std::make_shared<AttachmentDTO>();
        dto->id = sub->getId();
        dto->name = sub->getName();
        dto->file_type = sub->getFile_type();
        dto->save_type = sub->getSave_type();
        dto->save_path = sub->getSave_path();
        dto->remark = sub->getRemark();
        dto->status = sub->getStatus();

        result.data.push_back(*dto);  // 存储DTO对象而非指针
    }

    std::cout << "数据库查询结果数量: " << dbResult.size() << std::endl;
    return result;
}