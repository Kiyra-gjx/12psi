#pragma once

#ifndef _IMDATACONTROLLER_H_
#define _IMDATACONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/ImportDataVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchase.tag")

class ImDataController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ImDataController);

public:
	// 定义一个单文件上传接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("file.InData"), uploadFile, ImportDataAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/purchasedingdan/dataupload", uploadFile, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportData(request));
private:
	// 执行单文件上传操作
	StringJsonVO::Wrapper execImportData(std::shared_ptr<oatpp::web::server::api::ApiController::IncomingRequest> request);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_IMDATACONTROLLER_H_
