#pragma once

#ifndef _FUNDSER_H_
#define _FUNDSER_H_

#include"domain/vo/FundsVO/FundsVO.h"
#include"domain/dto/FundsDTO/FundsDTO.h"


class FundsService
{
public:
//查询账户
	AccountDetailDTO::Wrapper getAccountById(std::string id);
//新增账户
	std::string saveNewAccount(AddAccountDTO::Wrapper dto);
//修改账户
	bool updateAccount(AccountDetailDTO::Wrapper dto);
// 删除
	bool deleteFunds(const oatpp::List<oatpp::String>& ids);
};


#endif // !_FUNDSER_H_
