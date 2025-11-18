#include"stdafx.h"
#include"FundsService.h"
#include"../../dao/FundsDAO/FundsDAO.h"
#include"id/SnowFlake.h"
/*
* class AddAccountDTO : public oatpp::DTO
{
	DTO_INIT(AddAccountDTO, DTO);
	
	API_DTO_FIELD_DEFAULT(String, accountname, ZH_WORDS_GETTER("funds.field.name"));
	API_DTO_FIELD_DEFAULT(String, accountnumber, ZH_WORDS_GETTER("funds.field.number"));
	API_DTO_FIELD_DEFAULT(String, frame, ZH_WORDS_GETTER("funds.field.frame"));
	API_DTO_FIELD_DEFAULT(String, time, ZH_WORDS_GETTER("funds.field.time"));
	API_DTO_FIELD_DEFAULT(Float64, initial, ZH_WORDS_GETTER("funds.field.initial"));
	API_DTO_FIELD_DEFAULT(Float64, balance, ZH_WORDS_GETTER("funds.field.balance"));
	API_DTO_FIELD_DEFAULT(String, data, ZH_WORDS_GETTER("funds.field.data"));

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

};

class AccountDetailDTO :public AddAccountDTO
{
	DTO_INIT(AccountDetailDTO, AddAccountDTO);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("funds.field.id"));
};
*/
/*
* 	//账户id
	MYSQL_SYNTHESIZE(string, id, Id);
	//账户名称
	MYSQL_SYNTHESIZE(string, accountname, Accountname);
	//账户编号
	MYSQL_SYNTHESIZE(string, accountnumber, Accountnumber);
	//所属组织
	MYSQL_SYNTHESIZE(string, frame, Frame);
	//余额日期
	MYSQL_SYNTHESIZE(string, time, Time);
	//期初余额
	MYSQL_SYNTHESIZE(double, initial, Initial);
	//账户余额
	MYSQL_SYNTHESIZE(double, balance, Balance);
	//备注信息
	MYSQL_SYNTHESIZE(string, data, Data);
*/
//查询账户
AccountDetailDTO::Wrapper FundsService::getAccountById(std::string id)
{
	AccountDAO dao;
	auto res = dao.selectById(id);
	if (!res) return nullptr;

	auto dto = AccountDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, accountname, Accountname, accountnumber, Accountnumber, frame, Frame, time, Time, initial, Initial, balance, Balance, data, Data);
	return dto;
}
//新增账户
std::string FundsService::saveNewAccount(AddAccountDTO::Wrapper dto)
{
	AccountDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		Accountname, accountname,
		Accountnumber, accountnumber,
		Frame, frame,
		Time, time,
		Initial, initial,
		Balance, balance,
		Data, data
	);
	SnowFlake sf(1, 1);
	data.setId(std::to_string(sf.nextId()));
	AccountDAO dao;
	return dao.insert(data) == 1 ? data.getId() : "";

}
//修改账户
bool FundsService::updateAccount(AccountDetailDTO::Wrapper dto)
{
	AccountDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		Id, id,
		Accountname, accountname,
		Accountnumber, accountnumber,
		Frame, frame,
		Time, time,
		Initial, initial,
		Balance, balance,
		Data, data
	);

	AccountDAO dao;
	return dao.update(data) == 1;
}
//删除
bool FundsService::deleteFunds(const oatpp::List<oatpp::String>& ids)
{
	AccountDAO dao;
	std::list<std::string> datas;
	for (auto one : *ids.get())
	{
		datas.emplace_back(one.getValue({}));
	}
	int rows = dao.deleteByIds<AccountDO>(datas);
	if (rows == ids->size())
	{
		return true;
	}
	return false;
}