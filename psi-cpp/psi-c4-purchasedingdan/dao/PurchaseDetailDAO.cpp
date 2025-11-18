#include "stdafx.h"
#include "PurchaseDetailDAO.h"
#include "PurchaseDetailViewMapper.h"

// 构建查询条件（基于 bor 表字段过滤）
std::string PurchaseDetailDAO::queryConditionBuilder(const PurchaseDetailQuery::Wrapper& query, SqlParams& params) {
    std::stringstream condition;
    condition << " WHERE 1=1"; 

    // 供应商
    if (query->supplier && !query->supplier.getValue("").empty()) {
        condition << " AND bor.supplier LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + query->supplier.getValue("") + "%");
    }

    // 单据日期
    if (query->docDate && !query->docDate.getValue("").empty()) {
        condition << " AND bor.time = ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->docDate.getValue(""));
    }

    // 单据编号
    if (query->docNo && !query->docNo.getValue("").empty()) {
        condition << " AND bor.number = ?"; 
        SQLPARAMS_PUSH(params, "s", std::string, query->docNo.getValue(""));
    }

    return condition.str();
}

// 分页查询：联表 bor_info + goods，返回 DTO 所需字段
std::list<PurchaseDetailViewDO> PurchaseDetailDAO::selectPurchaseDetail(const PurchaseDetailQuery::Wrapper& query) {
    SqlParams params;
    std::string sql = "SELECT "
        // goods 表字段（映射商品信息）
        "g.`name` AS goodsName, "       // 商品名称
        "g.`number` AS goodsNo, "       // 商品编号
        "g.`spec` AS specModel, "       // 规格型号
        // bor_info 表字段（映射采购单详情）
        "bor_info.`attr` AS attr, "           // 辅助属性
        "bor_info.`unit` AS unit, "           // 单位
        "bor_info.`warehouse` AS warehouse, " // 仓库
        "bor_info.`price` AS price, "         // 单价
        "bor_info.`nums` AS nums, "           // 数量
        "bor_info.`total` AS total, "         // 金额
        "bor_info.`data` AS remark, "         // 备注信息
        "bor_info.`handle` AS handle "        // 入库数量
        "FROM bor_info "
        // 联表 goods：通过 bor_info.id 关联 goods.id
        "LEFT JOIN goods g ON bor.`id` = g.`id` ";    // 给 goods 取别名 g
        "LEFT JOIN bor ON bor.`id` = bor_info.`id` "; // 和 bor 表联立
        
    // 拼接查询条件（基于 bor_info 表字段过滤，queryConditionBuilder 已经做了这个）
    sql += queryConditionBuilder(query, params);

    // 排序逻辑（按 bor_info 更新时间/创建时间倒序，无则按 ID 倒序）
    sql += " ORDER BY IFNULL(bor_info.`update_time`, bor_info.`create_time`) DESC, bor_info.`id` DESC ";

    // 分页条件（与原风格一致：(页码-1)*每页条数）
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询：使用 PurchaseDetailViewMapper 映射结果到 PurchaseDetailViewDO
    return sqlSession->executeQuery<PurchaseDetailViewDO>(sql, PurchaseDetailViewMapper(), params);
}
