#pragma once

/*
 Copyright Zero One Star. All rights reserved.
 */
#ifndef _GOODS_CATEGORY_DAO_
#define _GOODS_CATEGORY_DAO_
#include "BaseDAO.h"
#include "GoodsCategoryMapper.h"
#include "../../domain/do/goods-category/GoodsCategoryDO.h"
#include "../../domain/query/goods-category/GoodsCategoryQuery.h"
#include <list>
#include<cstdarg>
#include <iostream>
#include <any>
 /**
  * 商品类别数据访问接口
  */
class GoodsCategoryDAO : public BaseDAO
{
private:
	// 构建查询条件SQL
	inline std::string queryConditionBuilder(const GoodsCategoryQuery::Wrapper& query, SqlParams& params);
public:
	// 统计符合条件的总数
	uint64_t count(const GoodsCategoryQuery::Wrapper& query);
	// 分页查询商品类别
	std::list<GoodsCategoryDO> selectWithPage(const GoodsCategoryQuery::Wrapper& query);
	// 根据ID查询商品类别
	PtrGoodsCategoryDO selectById(const std::string& id);

	// 通过pid查询数据
	std::list<PtrGoodsCategoryDO> selectByPId(const string& pid);

	//根据name查询商品类别
	PtrGoodsCategoryDO selectByName(const std::string& name);
	std::list<GoodsCategoryDO> selectCategoryTree();




    std::string executeQueryOneColumn(const std::string& sql, const SqlParams& params) {
        // 调用executeQuery，模板参数为std::string，使用StringMapper
        auto resultList = sqlSession->executeQuery<std::string>(sql, StringMapper(), params);
        if (!resultList.empty()) {
            return resultList.front(); // 返回第一行数据
        }
        return ""; // 无数据返回空
    }

    // 修正：可变参数重载（正确解析参数数量）
    std::string executeQueryOneColumn(const std::string& sql, const char* format, ...) {
        SqlParams params;
        va_list args;
        va_start(args, format);

        // 解析格式字符串（如"%s%s"对应两个字符串参数）
        for (size_t i = 0; format[i] != '\0'; ++i) {
            if (format[i] == '%' && format[i + 1] != '\0') {
                switch (format[++i]) {
                case 's': { // 字符串参数
                    const char* val = va_arg(args, const char*);
                    SQLPARAMS_PUSH(params, "s", std::string, val);
                    break;
                }
                case 'i': { // 整数参数
                    int val = va_arg(args, int);
                    SQLPARAMS_PUSH(params, "i", int, val);
                    break;
                }
                        // 可扩展其他类型（如%lld对应长整数）
                }
            }
        }
        va_end(args);
        return executeQueryOneColumn(sql, params);
    }
    // 在GoodsCategoryDAO.cpp中添加初始化方法（或在服务启动时执行）
    void initSessionConfig() {
        std::string setSql = "SET SESSION group_concat_max_len = 1000000;";
        SqlParams params;
        sqlSession->executeUpdate(setSql, params); // 执行更新操作（无返回值）
    }
	//std::list<GoodsCategoryDO> selectCategoryTreeById(const std::string& rootId);
	std::string selectCategoryTreeJsonById(const std::string& rootId);

};

#endif // !_GOODS_CATEGORY_DAO_
