#pragma once

#ifndef _SUPPLIER_DAO_
#define _SUPPLIER_DAO_

#include "BaseDAO.h"
#include "../../domain/do/SupplierDO.h"
#include "../../domain/query/SupplierQuery/SupplierQuery.h"
#include "../../domain/dto/SupplierDTO/SupplierDTO.h"

/**
 * 供应商表数据库操作实现
 */
class SupplierDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const SupplierQuery::Wrapper& query, SqlParams& params);

public:
	// 统计供应商数量
	uint64_t count(const SupplierQuery::Wrapper& query);

	// 分页查询供应商数据
	std::list<SupplierDO> selectWithPage(const SupplierQuery::Wrapper& query);

	// 根据供应商名称查询数据
	PtrSupplierDO selectByName(const std::string& name);

	// 根据供应商ID查询单条数据
	PtrSupplierDO selectById(const std::string& id);
};
#endif // !_SUPPLIER_DAO_
