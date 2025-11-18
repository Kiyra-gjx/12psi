#pragma once

#ifndef _FUNDSDAO_H_
#define _FUNDSDAO_H_
#include"BaseDAO.h"
#include"../../domain/do/AccountDO.h"
class AccountDAO : public BaseDAO
{
public:
//id查询account表里的数据
	PtrAccountDO selectById(std::string id);
//更新account表里的数据
	int updateAccount(const AccountDO& newAccount);
//在account表里插入新的数据
	int insertAccount(const AccountDO& newAccount);
};


#endif // !_FUNDSDAO_H_
