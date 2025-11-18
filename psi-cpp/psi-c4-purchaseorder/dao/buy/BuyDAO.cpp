#include "stdafx.h"
#include "BuyDAO.h"


bool BuyDAO::batchUpdateExamineStatus(const oatpp::List<oatpp::String>& ids, int examineStatus)
{
	if (ids == nullptr || ids->size() == 0) {
		return false;
	}

	string sql = "UPDATE buy SET examine=? WHERE id IN (";
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

bool BuyDAO::updateBuy(const PtrBuyDO& buyDO)
{
	if (!buyDO) {
		return false;
	}

	string sql = "UPDATE buy SET ";
	SqlParams params;
	bool hasUpdateFields = false;

	// 供应商
	if (!buyDO->getSupplier().empty()) {
		sql += "supplier=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getSupplier());
		hasUpdateFields = true;
	}

	// 单据时间
	if (!buyDO->getTime().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "time=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getTime());
		hasUpdateFields = true;
	}

	// 单据编号
	if (!buyDO->getNumber().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "number=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getNumber());
		hasUpdateFields = true;
	}

	// 单据金额
	if (buyDO->getTotal() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "total=?";
		SQLPARAMS_PUSH(params, "d", double, buyDO->getTotal());
		hasUpdateFields = true;
	}

	// 实际金额
	if (buyDO->getActual() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "actual=?";
		SQLPARAMS_PUSH(params, "d", double, buyDO->getActual());
		hasUpdateFields = true;
	}

	// 实付金额
	if (buyDO->getMoney() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "money=?";
		SQLPARAMS_PUSH(params, "d", double, buyDO->getMoney());
		hasUpdateFields = true;
	}
	
	// 单据费用
	if (!buyDO->getCost()>0 ) {
		if (hasUpdateFields) sql += ", ";
		sql += "cost=?";
		SQLPARAMS_PUSH(params, "d", double, buyDO->getCost());
		hasUpdateFields = true;
	}
	
	// 结算账户
	if (!buyDO->getAccount().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "account=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getAccount());
		hasUpdateFields = true;
	}

	// 物流信息
	if (!buyDO->getLogistics().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "logistics=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getLogistics());
		hasUpdateFields = true;
	}

	// 关联人员
	if (!buyDO->getPeople().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "people=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getPeople());
		hasUpdateFields = true;
	}

	// 单据附件
	if (!buyDO->getFile().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "file=?";
		SQLPARAMS_PUSH(params, "s", std::string, buyDO->getFile());
		hasUpdateFields = true;
	}

	

	if (!hasUpdateFields) {
		return false; // 没有需要更新的字段
	}

	sql += " WHERE id=?";
	SQLPARAMS_PUSH(params, "s", std::string, buyDO->getId());

	return sqlSession->executeUpdate(sql, params) > 0;
}
