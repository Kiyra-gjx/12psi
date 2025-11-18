#include "stdafx.h"
#include "SellInfoService.h"
#include "dao/SellInfoDAO/SellInfoDAO.h"

PtrSellInfoDO SellInfoService::queryByPid(const std::string& pid)
{
	SellInfoDAO dao;
	auto res = dao.selectSellInfoByPid(pid);

	if (!res)
		return nullptr;

	return res;

}
