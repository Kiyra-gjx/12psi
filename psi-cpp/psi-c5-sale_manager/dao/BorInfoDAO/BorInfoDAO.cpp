#include "stdafx.h"
#include "BorInfoDAO.h"
#include "BorInfoMapper.h"

PtrBorInfoDO BorInfoDAO::selectBorInfoByPid(const std::string& pid)
{
	string sql = "SELECT id,pid,goods,attr,unit,warehouse,price,nums,discount,dsc,total,tax,tat,tpt,data,handle FROM bor_info WHERE pid=?";
	return sqlSession->executeQueryOne<PtrBorInfoDO>(sql, BorInfoMapper(), "%s", pid);
}

