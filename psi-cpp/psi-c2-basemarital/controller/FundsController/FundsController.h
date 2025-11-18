#pragma
#ifndef FUNDSCONTROLLER_H_
#define FUNDSCONTROLLER_H_
#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/GlobalInclude.h"
#include "domain/query/FundsQuery/FundsQuery.h"
#include "domain/vo/FundsVO/FundsVO.h"
#include "domain/dto/FundsDTO/FundsDTO.h"
#include "service/FundsService/FundsService.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("funds.tag")

class FundsController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(FundsController);
public:
	
	ENDPOINT_INFO(queryFunds) {		
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("funds.get.summary"));		
		API_DEF_ADD_AUTH();		
		API_DEF_ADD_RSP_JSON_WRAPPER(FundsPageJsonVO);		
		API_DEF_ADD_TAG(API_TAG);		
		API_DEF_ADD_PAGE_PARAMS();		
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("funds.field.name"), " ", false);
		API_DEF_ADD_QUERY_PARAMS(String, "number", ZH_WORDS_GETTER("funds.field.number"), " ", false);
		API_DEF_ADD_QUERY_PARAMS(String, "data", ZH_WORDS_GETTER("funds.field.data"), " ", false);
	}
	
	ENDPOINT(API_M_GET, "/funds/get", queryFunds, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {		
		API_HANDLER_QUERY_PARAM(userQuery, FundsQuery, queryParams);		
		API_HANDLER_RESP_VO(execQueryFunds(userQuery));
	}


	//获取账户指定详情
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("funds.field.getDetail"), QueryAccountDetail, AccountDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "AccountID", ZH_WORDS_GETTER("funds.field.AccountID"), "sa8fdshfr903", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/funds/query-fund-detail", QueryAccountDetail, QUERY(String, AccountID), excuteQueryDetail(AccountID));


	//新增账户
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("funds.field.addAccount"), AddAccount, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/funds/add-account", AddAccount, BODY_DTO(AddAccountDTO::Wrapper, dto), excuteAdd(dto, authObject->getPayload()));


	//修改指定账户
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("funds.field.modify"), ModifyAccount, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/funds/modify-account", ModifyAccount, BODY_DTO(AccountDetailDTO::Wrapper, dto), excuteModify(dto, authObject->getPayload()));


	//定义删除资金账户接口描述@快乐五香蛋
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("fund.delete.summary"), removeFund, ListJsonVO<String>::Wrapper, API_TAG);
	//定义删除资金账户接口处理@快乐五香蛋
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/funds/delete", removeFund, BODY_DTO(List<String>, ids), execRemoveFund(ids));
private:
	//定义删除资金账户接口函数@快乐五香蛋
	ListJsonVO<String>::Wrapper execRemoveFund(const List<String>& ids);
	AccountDetailJsonVO::Wrapper excuteQueryDetail(const String& id);
	StringJsonVO::Wrapper excuteAdd(const AddAccountDTO::Wrapper& dto, const PayloadDTO& payload);
	StringJsonVO::Wrapper excuteModify(const AccountDetailDTO::Wrapper& dto, const PayloadDTO& payload);
	FundsPageJsonVO::Wrapper execQueryFunds(const FundsQuery::Wrapper& query);
};
	

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif