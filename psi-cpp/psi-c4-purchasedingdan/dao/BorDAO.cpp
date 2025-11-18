#include "stdafx.h"
#include "BorDAO.h"

bool BorDAO::batchUpdateExamineStatus(const oatpp::List<oatpp::String>& ids, int examineStatus)
{
	if (ids == nullptr || ids->size() == 0) {
		return false;
	}

	string sql = "UPDATE bor SET examine=? WHERE id IN (";
	SqlParams params;
	SQLPARAMS_PUSH(params, "i", int, examineStatus);

	// 构建IN查询的参数
	for (size_t i = 0; i < ids->size(); ++i) {
		if (i > 0) {
			sql += ",";
		}
		sql += "?";
		SQLPARAMS_PUSH(params, "s", std::string, ids[i]->c_str());
	}
	sql += ")";

	return sqlSession->executeUpdate(sql, params) > 0;
}

bool BorDAO::updateBor(const PtrBorDO& borDO)
{
	if (!borDO) {
		return false;
	}

	string sql = "UPDATE bor SET ";
	SqlParams params;
	bool hasUpdateFields = false;

	// 供应商
	if (!borDO->getSupplier().empty()) {
		sql += "supplier=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getSupplier());
		hasUpdateFields = true;
	}

	// 单据时间
	if (!borDO->getTime().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "time=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getTime());
		hasUpdateFields = true;
	}

	// 单据编号
	if (!borDO->getNumber().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "number=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getNumber());
		hasUpdateFields = true;
	}

	// 到货时间
	if (!borDO->getArrival().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "arrival=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getArrival());
		hasUpdateFields = true;
	}

	// 物流信息
	if (!borDO->getLogistics().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "logistics=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getLogistics());
		hasUpdateFields = true;
	}

	// 关联人员
	if (!borDO->getPeople().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "people=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getPeople());
		hasUpdateFields = true;
	}

	// 单据附件
	if (!borDO->getFile().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "file=?";
		SQLPARAMS_PUSH(params, "s", std::string, borDO->getFile());
		hasUpdateFields = true;
	}

	// 单据金额
	if (borDO->getTotal() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "total=?";
		SQLPARAMS_PUSH(params, "d", double, borDO->getTotal());
		hasUpdateFields = true;
	}

	// 实际金额
	if (borDO->getActual() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "actual=?";
		SQLPARAMS_PUSH(params, "d", double, borDO->getActual());
		hasUpdateFields = true;
	}

	if (!hasUpdateFields) {
		return false; // 没有需要更新的字段
	}

	sql += " WHERE id=?";
	SQLPARAMS_PUSH(params, "s", std::string, borDO->getId());

	return sqlSession->executeUpdate(sql, params) > 0;
}
