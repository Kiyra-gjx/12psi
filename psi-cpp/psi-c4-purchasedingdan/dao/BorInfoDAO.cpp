#include "stdafx.h"
#include "BorInfoDAO.h"
#include "BorInfoMapper.h"

PtrBorInfoDO BorInfoDAO::selectByPid(const std::string& pid)
{
	string sql = "SELECT id,pid,goods,attr,unit,warehouse,price,nums,discount,dsc,total,tax,tat,tpt,data,handle FROM bor_info WHERE pid=?";
	return sqlSession->executeQueryOne<PtrBorInfoDO>(sql, BorInfoMapper(), "%s", pid);
}

bool BorInfoDAO::updateBorInfo(const PtrBorInfoDO& borInfoDO)
{
	if (!borInfoDO) {
		return false;
	}

	string sql = "UPDATE bor_info SET "
		"attr=?, unit=?, warehouse=?, price=?, nums=?, "
		"discount=?, dsc=?, total=?, tax=?, tat=?, tpt=?, data=?, handle=? "
		"WHERE pid=? AND goods=?";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getAttr());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getUnit());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getWarehouse());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getPrice());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getNums());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getDiscount());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getDsc());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTotal());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTax());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTat());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTpt());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getData());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getHandle());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getPid());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getGoods());

	return sqlSession->executeUpdate(sql, params) > 0;
}

PtrBorInfoDO BorInfoDAO::selectByPidAndGoods(const std::string& pid, const std::string& goods)
{
	string sql = "SELECT id,pid,goods,attr,unit,warehouse,price,nums,discount,dsc,total,tax,tat,tpt,data,handle FROM bor_info WHERE pid=? AND goods=?";
	return sqlSession->executeQueryOne<PtrBorInfoDO>(sql, BorInfoMapper(), "%s%s", pid, goods);
}