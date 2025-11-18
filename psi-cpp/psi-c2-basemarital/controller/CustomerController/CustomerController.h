#ifndef _CustomerController_H_
#define _CustomerController_H_

#include <ApiHelper.h>
#include <Macros.h>

#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/CustomerQuery/CustomerQuery.h"
#include "domain/vo/CustomerVO/CustomerVO.h"
#include "domain/dto/CustomerDTO/CustomerDTO.h"
#include "service/CustomerService/CustomerService.h"


#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("cus.tag")
/**
 * 客户管理控制器
 */

class CustomerController : public oatpp::web::server::api::ApiController
{

	//定义控制器访问接口
	API_ACCESS_DECLARE(CustomerController);
public:
	// 新增客户接口
	ENDPOINT_INFO(addCustomer)
	{
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("Customer.get.add"));
		API_DEF_ADD_RSP_JSON_WRAPPER(CustomerAddResponseVO);
		API_DEF_ADD_TAG(ZH_WORDS_GETTER("Customer.get.title"));
		API_DEF_ADD_AUTH();

		info->addResponse<oatpp::Object<CustomerAddResponseVO>>(Status::CODE_200, "application/json");
		info->addResponse<oatpp::Object<CustomerAddResponseVO>>(Status::CODE_400, "application/json");
	}
	ENDPOINT("POST", "cus/add", addCustomer, BODY_DTO(CustomerDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME);


	//获取客户详情
	ENDPOINT_INFO(getCustomerInfo)
	{
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("Customer.get.get"));
		API_DEF_ADD_RSP_JSON_WRAPPER(CustomerGetResponseVO);
		API_DEF_ADD_TAG(ZH_WORDS_GETTER("Customer.get.title"));
		info->addResponse<oatpp::Object<CustomerGetResponseVO>>(Status::CODE_200, "application/json");
		API_DEF_ADD_AUTH();
	}
	ENDPOINT("GET", "cus/get/{customerid}", getCustomerInfo, PATH(oatpp::String, customerId), API_HANDLER_AUTH_PARAME);


	//修改客户接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("cus.modify.summary"), modifyCustomer, StringJsonVO::Wrapper, API_TAG);
	//修改客户接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/cus/modify", modifyCustomer, BODY_DTO(CustomerModifyDTO::Wrapper, dto), executeModifyCustomer(dto));


	//  定义导入客户列表文件接口描述，用于批量增加客户@快乐五香蛋
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("cus.ImportCusfile.summary"), uploadFile, CusFileAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	//  定义导入文件接口描述@快乐五香蛋
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/cus/cusmanager/upload", uploadFile, REQUEST(std::shared_ptr<IncomingRequest>, request), importcus(request));



	//删除客户接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("cus.delete.summary"), deleteCustomer, StringJsonVO::Wrapper, API_TAG);
	//删除客户接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/cus/delete", deleteCustomer, BODY_DTO(List<String>, ids), executeDeleteCustomer(ids));


	// 查询所有客户接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("cus.query-all.summary"), queryAllCus, CustomerQuery, CustomerListPageJsonVO::Wrapper, API_TAG);
	// 查询所有客户接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/cus/queryall", queryAllCus, CustomerQuery, executeQueryAll(query));


	// 定义导出文件接口描述@快乐五香蛋
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("cus.DownloadCusFile.summary"), exportFile, CustomerQuery, Void, API_TAG);
	// 定义导出文件接口,导出客户@快乐五香蛋
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/cus/cusmanager/downloadcusfile", exportFile, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, CustomerQuery, queryParams); return execExportCus(userQuery););


private: //定义导入数据函数@快乐五香蛋
	StringJsonVO::Wrapper importcus(std::shared_ptr<IncomingRequest> request);
	//演示导出数据@快乐五香蛋
	std::shared_ptr<OutgoingResponse> execExportCus(const CustomerQuery::Wrapper& query);
	// 查询所有客户接口端点
	CustomerListPageJsonVO::Wrapper executeQueryAll(const CustomerQuery::Wrapper& query);
	//修改
	StringJsonVO::Wrapper executeModifyCustomer(const CustomerModifyDTO::Wrapper& dto);
	//删除
	StringJsonVO::Wrapper executeDeleteCustomer(const List<String>& ids);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif