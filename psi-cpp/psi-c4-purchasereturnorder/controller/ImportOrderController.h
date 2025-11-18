#pragma once

#ifndef _IMPORTRETURNORDER_CONTROLLER_
#define _IMPORTRETURNORDER_CONTROLLER_


#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include"domain/dto/ImportDTO.h"


#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("purchasereturnorder.tag")

class ImportOrderController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(ImportOrderController);
public: // 定义接口
	// 导入数据
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("import_order.tag"), orderImportOne, FileAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/purchasereturnorder/import", orderImportOne, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportOne(request));

private: // 定义接口执行函数


	// 执行单文件上传处理
	ListJsonVO<String>::Wrapper execImportOne(std::shared_ptr<IncomingRequest> request);


};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_IMPORTEXCELCONTROLLER_H_




