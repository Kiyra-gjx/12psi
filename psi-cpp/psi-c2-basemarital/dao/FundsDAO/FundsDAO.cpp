#include"stdafx.h"
#include"FundsDAO.h"
#include"FundsMapper.h"
/*
账户id
MYSQL_SYNTHESIZE(string, id, Id);
账户名称
MYSQL_SYNTHESIZE(string, accountname, Accountname);
账户编号
MYSQL_SYNTHESIZE(string, accountnumber, Accountnumber);
所属组织
MYSQL_SYNTHESIZE(string, frame, Frame);
余额日期
MYSQL_SYNTHESIZE(string, time, Time);
期初余额
MYSQL_SYNTHESIZE(double, initial, Initial);
账户余额
MYSQL_SYNTHESIZE(double, balance, Balance);
备注信息
MYSQL_SYNTHESIZE(string, data, Data);
*/
PtrAccountDO AccountDAO::selectById(std::string id)
{
	string sql = "SELECT id,accountname,accountnumber,frame,time,initial,balance,data FROM account WHERE `id`=?";
	return sqlSession->executeQueryOne<PtrAccountDO>(sql, PtrAccountMapper(), "%s", id);
}
//更新account表里的数据
int AccountDAO::updateAccount(const AccountDO& newAccount)
{
	std::string sql = "UPDATE account SET `accountname`=?,`accountnumber`=?,`frame`=?,`time`=?,`initial`=?,`balance`=?,`data`=? WHERE `id`=?";
	return sqlSession->executeUpdate(sql, "%s%s%s%s%f%f%s%s", newAccount.getAccountname(), newAccount.getAccountnumber(), newAccount.getFrame(), \
		newAccount.getTime(), newAccount.getInitial(), newAccount.getBalance(), newAccount.getData(), newAccount.getId());
}
//在account表里插入新的数据
int AccountDAO::insertAccount(const AccountDO& newAccount)
{
	std::string sql = "INSERT INFO account (`id`,`accountname`,`accountnumber`,`frame`,`time`,`initial`,`balance`,`data`) VALUES (?,?,?,?,?,?,?,?)";
	return sqlSession->executeUpdate(sql, "%s%s%s%s%s%f%f%s", newAccount.getId(), newAccount.getAccountname(), \
		newAccount.getAccountnumber(), newAccount.getFrame(), newAccount.getTime(), newAccount.getInitial(), newAccount.getBalance(), newAccount.getData());
}
//在account表里删除数据
