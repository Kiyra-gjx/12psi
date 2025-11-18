#include "stdafx.h"
#include "PurchaseListDAO.h"
#include "PurchaseListMapper.h"

std::string PurchaseListDAO::queryConditionBuilder(const PurchaseListQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 单据编号 
    if (query->number) {
        sqlCondition << " AND `number`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
    }

    // 供应商
    if (query->supplier) {
        sqlCondition << " AND `supplier`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->supplier.getValue(""));
    }

    // 关联人员
    if (query->people) {
        sqlCondition << " AND `people`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->people.getValue(""));
    }

    // 制单人
    if (query->user) {
        sqlCondition << " AND `user`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->user.getValue(""));
    }

    // 审核状态
    if (query->examine) {
        sqlCondition << " AND `examine`=?";
        SQLPARAMS_PUSH(params, "i", int, query->examine.getValue(0));
    }

    // 入库状态
    if (query->state) {
        sqlCondition << " AND `state`=?";
        SQLPARAMS_PUSH(params, "i", int, query->state.getValue(0));
    }

    // 备注信息
    if (query->data) {
        sqlCondition << " AND `data`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
    }

    return sqlCondition.str();
}


std::list<PurchaseDingDanDO> PurchaseListDAO::selectWithPage(const PurchaseListQuery::Wrapper& query)
{
    SqlParams params;
    // SELECT 子句：包含 DTO 所需的所有字段
    string sql = "SELECT "
        "id, "
        "frame, "          // 所属组织
        "supplier, "       // 供应商
        "time, "           // 单据时间
        "number, "         // 单据编号
        "total, "          // 单据金额
        "source, "         // 关联单据
        "actual, "         // 实际金额
        "arrival, "        // 到货时间
        "logistics, "      // 物流信息
        "file, "           // 单据附件
        "more, "           // 扩展信息
        "create_time, "    // 创建时间
        "update_time "     // 更新时间
        "FROM bor ";       // 表名确保正确

    // 构建查询条件
    sql += queryConditionBuilder(query, params);

    // 排序逻辑（沿用原风格，按时间和ID倒序）
    sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";

    // 分页条件（计算偏移量，与原逻辑一致）
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询：注意 mapper 需与 DO 对应（如果 PurchaseDingDanDO 有专用 mapper，需替换）
    return sqlSession->executeQuery<PurchaseDingDanDO>(sql, PurchaseListMapper(), params);
}

uint64_t PurchaseListDAO::count(const PurchaseListQuery::Wrapper& query) {
    SqlParams params;
    string sql = "SELECT COUNT(*) AS total FROM bor ";  
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}
