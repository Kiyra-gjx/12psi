#include "GoodsCategoryDAO.h"
#include "GoodsCategoryMapper.h"
#include "stdafx.h"



#include <sstream>
#include "GoodsCategoryDAO.h"
// ... 现有代码 ...

std::string GoodsCategoryDAO::selectCategoryTreeJsonById(const std::string& rootId) {
    GoodsCategoryDAO::initSessionConfig();
    std::string sql = R"(
    WITH RECURSIVE category_tree AS (
        SELECT id, pid, name, sort, data, 1 AS level, CAST(id AS CHAR(255)) AS path
        FROM category WHERE id = ?
        UNION ALL
        SELECT c.id, c.pid, c.name, c.sort, c.data, ct.level + 1 AS level, CONCAT(ct.path, '.', c.id) AS path
        FROM category c INNER JOIN category_tree ct ON c.pid = ct.id
    ),
    max_level AS (SELECT MAX(level) AS max_lvl FROM category_tree),
    sorted_nodes AS (
        SELECT *, (max_lvl - level + 1) AS reverse_level
        FROM category_tree, max_level ORDER BY reverse_level, path
    )
    SELECT CONCAT('{"category_tree": [', GROUP_CONCAT(json_str ORDER BY sort SEPARATOR ','), ']}') AS result_json
    FROM (
        SELECT 
            id, pid, sn.sort AS sort,
            -- 合并变量赋值与字段，压缩换行
            @json := CASE 
                WHEN NOT EXISTS (SELECT 1 FROM sorted_nodes WHERE pid = sn.id) THEN 
                    CONCAT('{"id":"', REPLACE(sn.id, '"', '\\"'), '","pid":', IF(sn.pid IS NULL, 'null', CONCAT('"', REPLACE(sn.pid, '"', '\\"'), '"')), ',"name":"', REPLACE(sn.name, '"', '\\"'), '","sort":', sn.sort, ',"data":"', REPLACE(sn.data, '"', '\\"'), '","level":', sn.level, ',"children":[]}')
                ELSE 
                    CONCAT('{"id":"', REPLACE(sn.id, '"', '\\"'), '","pid":', IF(sn.pid IS NULL, 'null', CONCAT('"', REPLACE(sn.pid, '"', '\\"'), '"')), ',"name":"', REPLACE(sn.name, '"', '\\"'), '","sort":', sn.sort, ',"data":"', REPLACE(sn.data, '"', '\\"'), '","level":', sn.level, ',"children":[',
                        (SELECT GROUP_CONCAT(JSON_UNQUOTE(JSON_EXTRACT(@json_map, CONCAT('$."', child_id, '".json_str'))) ORDER BY JSON_EXTRACT(@json_map, CONCAT('$."', child_id, '".sort')) SEPARATOR ',') 
                        FROM (SELECT JSON_UNQUOTE(json_key) AS child_id FROM JSON_TABLE(JSON_KEYS(@json_map), '$[*]' COLUMNS (json_key VARCHAR(50) PATH '$')) AS jk WHERE JSON_EXTRACT(@json_map, CONCAT('$."', json_key, '".pid')) = sn.id) AS children_ids),
                    ']}')
            END AS json_str,
            -- 关键：将@json_map赋值与上一行合并，删除换行
            @json_map := JSON_MERGE_PATCH(@json_map, JSON_OBJECT(sn.id, JSON_OBJECT('pid', sn.pid, 'sort', sn.sort, 'json_str', @json)))
        FROM sorted_nodes sn, (SELECT @json := '', @json_map := '{}') init
        ORDER BY reverse_level
    ) AS node_json
    WHERE id = ?;
)";
    // 使用当前DAO中定义的executeQueryOneColumn
    return executeQueryOneColumn(sql, "%s%s", rootId.c_str(), rootId.c_str());
}
std::list<GoodsCategoryDO> GoodsCategoryDAO::selectCategoryTree() {
    // 使用递归CTE查询树形结构
    std::string sql = R"(
        WITH RECURSIVE category_tree AS (
            -- 根节点：pid为空或0的节点
            SELECT id, pid, name, sort, data, 1 AS level 
            FROM category 
            WHERE pid IS NULL OR pid = '' OR pid = '0'
            
            UNION ALL
            
            -- 递归子节点：关联父节点ID
            SELECT c.id, c.pid, c.name, c.sort, c.data, ct.level + 1 AS level 
            FROM category c
            INNER JOIN category_tree ct ON c.pid = ct.id
        )
        SELECT id, pid, name, sort, data, level FROM category_tree 
        ORDER BY level, sort ASC
    )";

    // 执行查询并返回结果
    return sqlSession->executeQuery<GoodsCategoryDO>(sql, GoodsCategoryMapper(), SqlParams());
}
// 构建查询条件
std::string GoodsCategoryDAO::queryConditionBuilder(const GoodsCategoryQuery::Wrapper& query, SqlParams& params) {
    std::stringstream sqlCondition;
    sqlCondition << " WHERE 1=1"; // 基础条件，方便后续拼接AND


    // 处理父类别ID（pid）条件
    if (query->pid) {
        sqlCondition << " AND `pid`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->pid.getValue(""));
    }

    // 处理类别名称（name）模糊查询条件
    if (query->name) {
        sqlCondition << " AND `name` LIKE CONCAT('%',?,'%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
    }

    // 处理排序号（sort）条件
    if (query->sort) { // 假设level对应sort字段（根据业务场景调整）
        sqlCondition << " AND `sort`=?";
        SQLPARAMS_PUSH(params, "i", int, query->sort.getValue(0));
    }

    return sqlCondition.str();
}
// 统计符合条件的记录数
uint64_t GoodsCategoryDAO::count(const GoodsCategoryQuery::Wrapper& query) {
    SqlParams params;
    std::string sql = "SELECT COUNT(*) FROM category "; // 表名对应GoodsCategoryDO的构造函数（"category"）
    sql += queryConditionBuilder(query, params); // 拼接查询条件
    return sqlSession->executeQueryNumerical(sql, params); // 执行计数查询
}

std::list<GoodsCategoryDO> GoodsCategoryDAO::selectWithPage(const GoodsCategoryQuery::Wrapper & query) {
    SqlParams params;
    // 使用COALESCE确保data不为null
    std::string sql = "SELECT `id`,`pid`,`name`,`sort`,COALESCE(`data`, '') AS `data` FROM category ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY `sort` ASC, `id` DESC ";
    sql += " LIMIT " + std::to_string((query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10))
        + "," + std::to_string(query->pageSize.getValue(10));
    return sqlSession->executeQuery<GoodsCategoryDO>(sql, GoodsCategoryMapper(), params);
}
// 按ID查询商品类别
PtrGoodsCategoryDO GoodsCategoryDAO::selectById(const std::string& id) {
    std::string sql = "SELECT `id`,`pid`,`name`,`sort`,`data` FROM category WHERE `id`=?";
    // 执行单条查询，使用智能指针映射器
    return sqlSession->executeQueryOne<PtrGoodsCategoryDO>(sql, PtrGoodsCategoryMapper(), "%s", id);
}


// 通过pid查询数据
std::list<PtrGoodsCategoryDO> GoodsCategoryDAO::selectByPId(const string& pid)
{
    string sql = "SELECT id, pid, name, sort, data FROM category WHERE pid = ?";
    return sqlSession->executeQuery<PtrGoodsCategoryDO>(sql, PtrGoodsCategoryMapper(), "%s", pid);
}


// 按名称模糊查询商品类别
PtrGoodsCategoryDO GoodsCategoryDAO::selectByName(const std::string& name) {
    std::string sql = "SELECT `id`,`pid`,`name`,`sort`,`data` FROM category WHERE `name` LIKE CONCAT('%',?,'%') LIMIT 0,1";
    // 执行查询，返回列表
    return sqlSession->executeQueryOne<PtrGoodsCategoryDO>(sql, PtrGoodsCategoryMapper(), "%s", name);
}


