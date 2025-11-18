#pragma once

#include"domain/query/SaleOrderListQuery.h"
#include"domain/dto/SaleOrderListDTO.h"
#include"domain/dto/SellDTO.h"
#include"domain/vo/SaleOrderListVO.h"
#include"../../dao/SorDAO/SorDAO.h"
class SorService
{
public:
    // 分页查询销售订单列表（条件+分页）
    SaleOrderListPageDTO::Wrapper listAll(const SaleOrderListQuery::Wrapper& query);

    // 获取指定销售订单详情
    SaleOrderDetailDTO::Wrapper getById(std::string id);

    // 获取生成销售单数据
    SO_by_saleJsonVO::Wrapper getSellGenerateData(const SellGenerateDTO::Wrapper& create);

    // 获取生成采购订单数据
    PO_by_saleJsonVO::Wrapper getPurchaseGenerateData(const PurchaseGenerateDTO::Wrapper& query);

    // 新增销售订单???
    std::string saveData(const SaleOrderAddDTO::Wrapper& dto);

    // 删除销售订单（支持批量）
    bool deleteById(const oatpp::String& id);

    // 修改销售订单
    bool updateData(const SorUpdateDTO::Wrapper& dto);


    // 批量删除销售订单（支持批量）
    SorDeleteResultVO::Wrapper batchDelete(const SorDeleteDTO::Wrapper& dto);

    // 批量审核  
    SorAuditResultVO::Wrapper batchApprove(const SorAuditDTO::Wrapper& dto);

    // 批量反审核  
    SorAuditResultVO::Wrapper batchUnapprove(const SorAuditDTO::Wrapper& dto);

    // 导入数据
    bool importData(const PayloadDTO& payload, const SorImportDTO::Wrapper& dto);

	bool updateSaleOrder(const SorUpdateDTO::Wrapper& dto);

    // 导出简单报表
    std::vector<SorExportSimpleDTO::Wrapper> querySimpleReport(const SorExportSimpleQuery::Wrapper& query);

    // 导出详细报表
    std::vector<SorExportDetailDTO::Wrapper> queryDetailReport(const SorExportDetailQuery::Wrapper& query);

    //获取文件服务器地址
    std::string getDfsServerAddrssUrl();

};

