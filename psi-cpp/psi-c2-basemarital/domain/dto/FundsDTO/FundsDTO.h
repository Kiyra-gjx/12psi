#pragma once
#ifndef _FUNDSDTO_H_
#define _FUNDSDTO_H_
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class AddAccountDTO : public oatpp::DTO
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


/**
 * 示例新增数据传输对象
 */
class FundsAddDTO : public oatpp::DTO
{
	DTO_INIT(FundsAddDTO, DTO);
	// 账户名称
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("funds.field.name");
	}
	// 账户编号
	DTO_FIELD(String, number);
	DTO_FIELD_INFO(number) {
		info->description = ZH_WORDS_GETTER("funds.field.number");
	}
	// 所属组织
	DTO_FIELD(Int32, frame);
	DTO_FIELD_INFO(frame) {
		info->description = ZH_WORDS_GETTER("funds.field.frame");
	}

	// 余额日期
	DTO_FIELD(Int32, time);
	DTO_FIELD_INFO(time) {
		info->description = ZH_WORDS_GETTER("funds.field.time");
	}
	// 账户余额
	DTO_FIELD(Float32, balance);
	DTO_FIELD_INFO(balance) {
		info->description = ZH_WORDS_GETTER("funds.field.balance");
	}
	// 备注信息
	DTO_FIELD(String, data);
	DTO_FIELD_INFO(data) {
		info->description = ZH_WORDS_GETTER("funds.field.data");
	}
	

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

/**
 * 示例传输对象
 */
class FundsDTO : public FundsAddDTO
{
	DTO_INIT(FundsDTO, FundsAddDTO);
};

/**
 * 示例分页传输对象
 */
class FundsPageDTO : public PageDTO<FundsDTO::Wrapper>
{
	DTO_INIT(FundsPageDTO, PageDTO<FundsDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_

