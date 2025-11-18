
#include"ReviewOrderDAO.h"
#include "stdafx.h"
#include "ReviewOrderMapper.h"




PtrBreDO ReviewOrderDAO::selectById(std::string id)
{
	string sql = "SELECT id,source,money,account,examine,user,number FROM bre WHERE `id` =?";


	return sqlSession->executeQueryOne<PtrBreDO>(sql, PtrReviewBreMapper(), "%s", id);
}



std::list<BreInfoDO> ReviewOrderDAO::selectByPid(std::string pid)
{
	// 构建查询语句
	string sql = "SELECT id,pid,goods,warehouse,nums,price FROM  bre_info WHERE pid=?";

	// 执行查询
	return sqlSession->executeQuery<BreInfoDO>(sql, ReviewBreInfoMapper(), "%s", pid);
}

PtrRoomDO ReviewOrderDAO::selectGoods(std::string goods, std::string warehouse)
{
	// 构建查询语句
	string sql = "SELECT id,goods,warehouse,nums FROM room WHERE goods=? AND warehouse=?";

	// 执行查询
	return sqlSession->executeQueryOne<PtrRoomDO>(sql, PtrReviewRoomMapper(), "%s%s", goods, warehouse);
}

PtrAccountInfoDO ReviewOrderDAO::selectByPC(string pid, string cid)
{
	string sql = "select id from account_info where pid = ?  AND class = ?  AND type = 'bre' ";

	return sqlSession->executeQueryOne<PtrAccountInfoDO>(sql, PtrReviewAccountInfoMapper(), "%s%s", pid, cid);
}

PtrRoomInfoDO ReviewOrderDAO::selectByPCI(std::string pid, std::string cid, std::string info)
{
	string sql = "select id from room_info where pid = ?  AND class = ?  AND type = 'bre' AND info = ? ";

	return sqlSession->executeQueryOne<PtrRoomInfoDO>(sql, PtrReviewRoomInfoMapper(), "%s%s%s", pid, cid, info);
}

