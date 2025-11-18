#pragma once

#ifndef _SELL_SERVICE_H_
#define _SELL_SERVICE_H_

#include "stdafx.h"
#include "dao/SellDAO/SellDAO.h"
#include "domain/query/SellQuery.h"
#include "domain/dto/SellDTO.h"
#include "domain/vo/SellVO.h"


class SellService
{
public:
    // 分页查询销售单主表
    SellPageDTO::Wrapper queryWithPage(const SellListQuery::Wrapper& query);

    // 按ID查询销售单
    SellDetailDTO::Wrapper queryById(const std::string& id);

    // 新增销售单（返回是否成功）
    std::string create(const SellCreateDTO::Wrapper& dto);

    // 更新销售单
    SellUpdatePageDTO::Wrapper listAll(const  SellListQuery::Wrapper& query);
    bool updateData(const SellUpdateDTO::Wrapper& dto);

    // 删除销售单
    SalenoteDeleteResultVO::Wrapper batchDelete(const SalenoteDeleteDTO::Wrapper& dto);

    SellGenerateReturnDTO::Wrapper getSellGenerateReturn(const oatpp::String& number);

    bool importData(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto);

    SellAuditResultVO::Wrapper batchApprove(const SellAuditDTO::Wrapper& dto);
    SellAuditResultVO::Wrapper batchUnapprove(const SellAuditDTO::Wrapper& dto);
private:
    SellDAO sellDAO;
};

#endif // _SELL_SERVICE_H_
SellUpdatePageDTO::Wrapper listAll(const  SellListQuery::Wrapper& query);
bool updateData(const SellUpdateDTO::Wrapper& dto);