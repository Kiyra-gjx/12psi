/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:26:52

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "ExReportSimDAO.h"
#include "ExReportSimDAOMapper.h" // 保持原头文件不变

std::string ExReportSimDAO::queryConditionBuilder(const ExReportSimQUERY::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // // 所属组织
    // if (query->frame) {
    //     sqlCondition << " AND frame=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->frame.getValue(""));
    // }
    //
    // // 供应商
    // if (query->supplier) {
    //     sqlCondition << " AND supplier=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->supplier.getValue(""));
    // }
    //
    // // 单据时间
    // if (query->time) {
    //     sqlCondition << " AND time=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->time.getValue(""));
    // }
    //
    // // 单据编号
    // if (query->number) {
    //     sqlCondition << " AND number=?";
    //     SQLPARAMS_PUSH(params, "s", std::string, query->number.getValue(""));
    // }
    //
    // // 单据金额
    // if (query->total) {
    //     sqlCondition << " AND total=?";
    //     SQLPARAMS_PUSH(params, "d", double, query->total.getValue(0.0));
    // }
    //
    // // 实际金额
    // if (query->actual) {
    //     sqlCondition << " AND actual=?";
    //     SQLPARAMS_PUSH(params, "d", double, query->actual.getValue(0.0));
    // }
    //
    // // 实付金额
    // if (query->money) {
    //     sqlCondition << " AND money=?";
    //     SQLPARAMS_PUSH(params, "d", double, query->money.getValue(0.0));
    // }
    //
    // // 单据费用
    // if (query->cost) {
    //     sqlCondition << " AND cost=?";
    //     SQLPARAMS_PUSH(params, "d", double, query->cost.getValue(0.0));
    // }
    //
    // // 审核状态
    // if (query->examine) {
    //     sqlCondition << " AND examine=?";
    //     SQLPARAMS_PUSH(params, "i", int, query->examine.getValue(0));
    // }
    //
    // // 核销状态
    // if (query->nucleus) {
    //     sqlCondition << " AND nucleus=?";
    //     SQLPARAMS_PUSH(params, "i", int, query->nucleus.getValue(0));
    // }
    //
    // // 费用状态
    // if (query->cse) {
    //     sqlCondition << " AND cse=?";
    //     SQLPARAMS_PUSH(params, "i", int, query->cse.getValue(0));
    // }
    //
    // // 发票状态
    // if (query->invoice) {
    //     sqlCondition << " AND invoice=?";
    //     SQLPARAMS_PUSH(params, "i", int, query->invoice.getValue(0));
    // }
    //
    // // 核对状态
    // if (query->check) {
    //     sqlCondition << " AND check=?";
    //     SQLPARAMS_PUSH(params, "i", int, query->check.getValue(0));
    // }
    //
    // // 关联人员
    // if (query->people) {
    //     sqlCondition << " AND people=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->people.getValue(""));
    // }
    //
    // // 制单人
    // if (query->user) {
    //     sqlCondition << " AND user=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->user.getValue(""));
    // }
    //
    // // 备注信息
    // if (query->data) {
    //     sqlCondition << " AND data=?";
    //     SQLPARAMS_PUSH(params, "s", std::string, query->data.getValue(""));
    // }
    //
    // // 扩展信息
    // if (query->more) {
    //     sqlCondition << " AND more=?";
    //     SQLPARAMS_PUSH(params, "s", string, query->more.getValue(""));
    // }

    return sqlCondition.str();
}

uint64_t ExReportSimDAO::count(const ExReportSimQUERY::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM buy ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<BuyDO> ExReportSimDAO::selectWithPage(const ExReportSimQUERY::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT id, source, frame, supplier, time, number, total, actual, money, cost, account, people, logistics, file, data, more, examine, nucleus, cse, invoice, check, user FROM buy";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY time DESC, id DESC ";
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 仅修正映射器调用，使用当前头文件中定义的正确映射器（假设ExReportDeMapper.h中包含BuyDO的映射器）
    return sqlSession->executeQuery<BuyDO>(sql, ExReportSimMapper(), params);
}