#include "stdafx.h"
#include "AttachmentDAO.h"
#include "AttachmentMapper.h"

std::string AttachmentDAO::queryConditionBuilder(const AttachmentQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    if (query->name) {

        sqlCondition << " AND `name`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
    }
    if (query->file_type) {

        sqlCondition << " AND file_type=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->file_type.getValue(""));
    }
    if (query->save_type) {

        sqlCondition << " AND save_type=?";
        SQLPARAMS_PUSH(params, "s", string, query->save_type.getValue(""));
    }

    if (query->save_path) {

        sqlCondition << " AND save_path=?";
        SQLPARAMS_PUSH(params, "s", string, query->save_path.getValue(""));
    }

    if (query->remark) {

        sqlCondition << " AND remark=?";
        SQLPARAMS_PUSH(params, "s", string, query->remark.getValue(""));
    }

    if (query->status) {

        sqlCondition << " AND status=?";
        SQLPARAMS_PUSH(params, "i", int, query->status.getValue(0));
    }

    return sqlCondition.str();
}

bool AttachmentDAO::update(const PtrAttachmentDO& attachmentDO) {
    if (!attachmentDO || attachmentDO->getId().empty()) return false;

    SqlParams params;
    std::string sql = "UPDATE `annex` SET `name`=?, `file_type`=?, `save_type`=?, `save_path`=?, `remark`=?, `status`=? WHERE `id`=?";

    // 通过公共getter方法获取字段值
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getName());
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getFile_type());
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getSave_type());
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getSave_path());
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getRemark());
    SQLPARAMS_PUSH(params, "i", int, attachmentDO->getStatus());
    SQLPARAMS_PUSH(params, "s", std::string, attachmentDO->getId()); // WHERE条件绑定id

    return sqlSession->executeUpdate(sql, params) > 0;
}

bool AttachmentDAO::deleteById(const std::string& id) {
    if (id.empty()) return false;

    SqlParams params;
    std::string sql = "DELETE FROM `annex` WHERE `id`=?";
    SQLPARAMS_PUSH(params, "s", std::string, id);
    return sqlSession->executeUpdate(sql, params) > 0;
}

bool AttachmentDAO::insert(const AttachmentDO& fdo)
{

    try {
        std::cout << "Inserting file with ID: " << fdo.getId() << std::endl;

        std::string sql = R"(
        INSERT INTO annex
        (id, name, file_type, save_type, save_path, remark, status)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getId());
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getName());
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getFile_type());
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getSave_type());
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getSave_path());
        SQLPARAMS_PUSH(params, "s", std::string, fdo.getRemark());
        SQLPARAMS_PUSH(params, "i", std::int32_t, fdo.getStatus());


        try {
            int result = sqlSession->executeUpdate(sql, params);
            std::cout << "鏁版嵁搴撴彃鍏ョ粨鏋滐紝褰卞搷琛屾暟: " << result << std::endl;
            return result > 0;
        }
        catch (const std::exception& e) {
            std::cerr << "Error inserting file: " << e.what() << std::endl;
            return false;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Database insert error: " << e.what() << std::endl;
        return false;
    }
}


std::list<PtrFileViewDO> AttachmentDAO::selectAll(const AttachmentQuery::Wrapper& query)
{
    try {
        SqlParams params;

        // 修正查询字段，与映射器期望的字段保持一致
        string sql = "SELECT * FROM annex ";

        // 构建查询条件
        sql += queryConditionBuilder(query, params);

        // 构建排序语句
        sql += " ORDER BY id DESC ";

        // 添加分页参数验证
        if (query && query->pageIndex && query->pageSize) {
            uint64_t offset = (static_cast<uint64_t>(*query->pageIndex) - 1) * static_cast<uint64_t>(*query->pageSize);
            sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(*query->pageSize);
        }
        else {
            // 默认分页设置
            sql += " LIMIT 0, 20";
        }

        return sqlSession->executeQuery<PtrFileViewDO>(sql, AttachmentMapper(), params);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in selectAll: " << e.what() << std::endl;
        return std::list<PtrFileViewDO>(); // 返回空列表
    }
}
uint64_t AttachmentDAO::count(const AttachmentQuery::Wrapper& query)
{
    try {
        SqlParams params;
        string sql = "SELECT COUNT(*) FROM annex ";
        sql += queryConditionBuilder(query, params);
        return sqlSession->executeQueryNumerical(sql, params);
    }
    catch (const std::exception& e) {
        std::cerr << "Error in count: " << e.what() << std::endl;
        return 0;
    }
}
