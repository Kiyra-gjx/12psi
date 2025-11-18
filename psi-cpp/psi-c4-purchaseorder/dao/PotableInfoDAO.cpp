#include "stdafx.h"
#include"PotableInfoDAO.h"
#include"PotableInfoMapper.h"

std::list<PotableInfoDO> PotableInfoDAO::selectPotableInfoPID(const PotableInfoQuery::Wrapper& query)
{
	stringstream sqlCondition;
	SqlParams params;
	sqlCondition << "WHERE buy_info.pid = ? ";
	SQLPARAMS_PUSH(params, "i", int, query->pid.getValue(0));
	string sql = "SELECT * FROM buy_info JOIN goods ON buy_info.goods=goods.id ";
	sql += sqlCondition.str();
	return sqlSession->executeQuery<PotableInfoDO>(sql, PotableInfoMapper(), params);
}