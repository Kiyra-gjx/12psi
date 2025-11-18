#include "stdafx.h"
#include "BuyInfoDAO.h"
#include "BuyInfoMapper.h"

PtrBuyInfoDO BuyInfoDAO::selectByPid(const std::string& pid)
{
	string sql = "SELECT id,pid,source,goods,attr,unit,warehouse,batch,mfd,price,nums,serial,discount,dsc,total,tax,tat,tpt,data,retreat FROM buy_info WHERE pid=?";
	return sqlSession->executeQueryOne<PtrBuyInfoDO>(sql, BuyInfoMapper(), "%s", pid);
}

bool BuyInfoDAO::updateBuyInfo(const PtrBuyInfoDO& borInfoDO)
{
	if (!borInfoDO) {
		return false;
	}

	string sql = "UPDATE buy_info SET "
		"source=?, attr=?, unit=?, warehouse=?, batch=?, price=?, nums=?, serial=?, "
		"discount=?, dsc=?, total=?, tax=?, tat=?, tpt=?, data=?, retreat=? "
		"WHERE pid=? AND goods=?";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getSource());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getAttr());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getUnit());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getWarehouse());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getBatch());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getPrice());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getNums());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getSerial());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getDiscount());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getDsc());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTotal());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTax());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTat());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getTpt());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getData());
	SQLPARAMS_PUSH(params, "d", double, borInfoDO->getRetreat());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getPid());
	SQLPARAMS_PUSH(params, "s", std::string, borInfoDO->getGoods());

	return sqlSession->executeUpdate(sql, params) > 0;
}

PtrBuyInfoDO BuyInfoDAO::selectByPidAndGoods(const std::string& pid, const std::string& goods)
{
	string sql = "SELECT id,pid,source,goods,attr,unit,warehouse,batch,mfd,price,nums,serial,discount,dsc,total,tax,tat,tpt,data,retreat FROM buy_info WHERE pid=? AND goods=?";
	return sqlSession->executeQueryOne<PtrBuyInfoDO>(sql, BuyInfoMapper(), "%s%s", pid, goods);
}