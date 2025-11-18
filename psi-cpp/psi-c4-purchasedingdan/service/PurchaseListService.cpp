#include "stdafx.h"
#include "PurchaseListService.h"
#include "id/UuidFacade.h"
#include "../dao/PurchaseListDAO.h"
#include "NacosClient.h"

// 采购订单列表分页查询实现
PurchaseListPageDTO::Wrapper PurchaseListService::listAll(const PurchaseListQuery::Wrapper& query)
{
    // 构建分页返回对象
    auto pages = PurchaseListPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    // 查询总条数
    PurchaseListDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages; // 无数据时直接返回空分页
    }

    // 分页查询数据
    pages->total = count;
    pages->calcPages(); // 计算总页数（PageDTO基类已实现分页逻辑）
    list<PurchaseDingDanDO> data_list = dao.selectWithPage(query);

    // 将DO转换为DTO并添加到分页结果
    for (auto& sub : data_list)
    {
        auto dto = PurchaseListDTO::createShared();
        // DO到DTO的字段映射（根据实际DO字段名调整）
        ZO_STAR_DOMAIN_DO_TO_DTO(
            dto, sub,
            frame, Frame,
            supplier, Supplier,
            time, Time,
            number, Number,
            total, Total,
            source, Source,
            actual, Actual,
            arrival, Arrival,
            logistics, Logistics,
            file, File,
            more, More
        );
        pages->addData(dto);
    }

    return pages;
}