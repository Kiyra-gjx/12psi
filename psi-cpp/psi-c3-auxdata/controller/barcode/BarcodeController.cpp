#include "stdafx.h"
#include"BarcodeController.h"
#include <iostream>
/*
author:zzz
接口描述: 获取条码列表（条件+分页）
@query params: const BarcodeCategoryQuery::Wrapper
@return: BarcodePageJsonVO::Wrapper
*/
BarcodePageJsonVO::Wrapper BarcodeController::executeQueryBarcodeClassPage(const BarcodeClassPageQuery::Wrapper& query)
{
	auto result = BarcodePageJsonVO::createShared();
	BarcodeService service;
	auto pageData = service.listAll(query);
	result->success(pageData);
	return result;
}
/*
author:zzz
接口描述：获取指定条码详情
@query params: const String &id
@return: BarcodeJsonVO::Wrapper
*/
BarcodeJsonVO::Wrapper BarcodeController::executeQueryBarcodeById(const String& id)
{

	auto result = BarcodeJsonVO::createShared();
	if (!id)
	{
		result->init(nullptr, RS_PARAMS_INVALID);
		return result;
	}
	BarcodeService service;
	auto barcode = service.getById(id);
	result->success(barcode);
	return result;
}
/*
author:413dik
接口描述：添加条码
@query params: const BarcodeAddDTO::Wrapper
@return: StringJsonVO::Wrapper
*/
StringJsonVO::Wrapper BarcodeController::executeAddBarcode(const BarcodeAddDTO::Wrapper& dto)
{
	return {};
}
/*
author:413dik
接口描述：下载条码图片
@query params: const String &info
@query params: const Int32 &type
@return: OutgoingResponse
*/
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> BarcodeController::execDownloadBarcodePic(const String& content, const Int32& type)
{
	return {};
}

StringJsonVO::Wrapper BarcodeController::ModifyBarcode(const BarcodeDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 响应结果
	return{};
}

ListJsonVO<String>::Wrapper BarcodeController::RemoveBarcode(const List<String>& ids)
{
	return{};
}