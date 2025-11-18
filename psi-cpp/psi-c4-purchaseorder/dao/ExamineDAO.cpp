#include "stdafx.h"
#include "ExamineDAO.h"
#include "ExamineMapper.h"

PtrBuyDO ExamineDAO::selectById(std::string id)
{
	string sql = "SELECT id,source,examine FROM buy WHERE `id` =?";


	return sqlSession->executeQueryOne<PtrBuyDO>(sql, PtrExamineMapper(), "%s", id);
}