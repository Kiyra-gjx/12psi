#include "stdafx.h"
#include "PurchaseDetailService.h"
#include "id/UuidFacade.h"
#include "../dao/PurchaseDetailDAO.h" 
#include "NacosClient.h"

PurchaseDetailDTO::Wrapper PurchaseDetailService::PurchaseDetail(const PurchaseDetailQuery::Wrapper& query)
{
    auto pages = PurchaseDetailDTO::createShared();//定义返回dto
    PurchaseDetailDAO dao;//定义DAO用于操作
    auto res = dao.selectPurchaseDetail(query);//res获取操作结果(通常是DO形式)
    //将DO转换成DTO
    for (auto& sud : res) {
        auto dto = Purchase_DetailDTO::createShared();
        // DO到DTO的字段映射
        ZO_STAR_DOMAIN_DO_TO_DTO(
            dto, sud,
            goodsName, GoodsName,    // 商品名称
            goodsNo, GoodsNo,        // 商品编号
            specModel, SpecModel,    // 规格型号
            attr, Attr,              // 辅助属性
            unit, Unit,              // 单位
            warehouse, Warehouse,    // 仓库
            price, Price,            // 单价
            nums, Nums,              // 数量
            total, Total,            // 金额
            remark, Remark,          // 备注信息
            handle, Handle           // 入库数量
        );
        pages->addData(dto);
    }
    return pages;
}
