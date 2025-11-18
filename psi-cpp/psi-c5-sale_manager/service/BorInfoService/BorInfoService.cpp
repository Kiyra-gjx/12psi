#include "stdafx.h"
#include "BorInfoService.h"
#include "dao/BorInfoDAO/BorInfoDAO.h"

PtrBorInfoDO BorInfoService::queryByPid(const string& pid)
{
	BorInfoDAO dao;
	auto res = dao.selectBorInfoByPid(pid);

	if (!res)
		return nullptr;

	return res;
}
