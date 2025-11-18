#include "stdafx.h"
#include "GoodsDAO.h"

PtrGoodsDO GoodsDAO::selectById(const std::string& id)
{
	string sql = "SELECT id,name,py,number,spec,category,brand,unit,buy,sell,code,location,stock,type,data,imgs,details,units,strategy,serial,batch,validity,protect,threshold,more FROM goods WHERE id=?";
	return sqlSession->executeQueryOne<PtrGoodsDO>(sql, GoodsMapper(), "%s", id);
}

bool GoodsDAO::updateGoods(const PtrGoodsDO& goodsDO)
{
	if (!goodsDO) {
		return false;
	}

	string sql = "UPDATE goods SET ";
	SqlParams params;
	bool hasUpdateFields = false;

	// 动态构建更新字段
	if (!goodsDO->getName().empty()) {
		sql += "name=?";
		SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getName());
		hasUpdateFields = true;
	}

	if (!goodsDO->getNumber().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "number=?";
		SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getNumber());
		hasUpdateFields = true;
	}

	if (!goodsDO->getSpec().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "spec=?";
		SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getSpec());
		hasUpdateFields = true;
	}

	if (!goodsDO->getUnit().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "unit=?";
		SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getUnit());
		hasUpdateFields = true;
	}

	if (!goodsDO->getCategory().empty()) {
		if (hasUpdateFields) sql += ", ";
		sql += "category=?";
		SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getCategory());
		hasUpdateFields = true;
	}

	if (goodsDO->getBuy() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "buy=?";
		SQLPARAMS_PUSH(params, "d", double, goodsDO->getBuy());
		hasUpdateFields = true;
	}

	if (goodsDO->getSell() > 0) {
		if (hasUpdateFields) sql += ", ";
		sql += "sell=?";
		SQLPARAMS_PUSH(params, "d", double, goodsDO->getSell());
		hasUpdateFields = true;
	}

	if (!hasUpdateFields) {
		return false; // 没有需要更新的字段
	}

	sql += " WHERE id=?";
	SQLPARAMS_PUSH(params, "s", std::string, goodsDO->getId());

	return sqlSession->executeUpdate(sql, params) > 0;
}