#pragma once
#ifndef BARCODE_CONTROLLER_H
#define BARCODE_CONTROLLER_H
#include "ApiHelper.h"
#include "../../Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/barcode/BarcodeVO.h"
#include "domain/query/barcode/BarcodeQuery.h"
#include "service/barcode/BarcodeService.h"


#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("barcode.apiTag")
class BarcodeController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(BarcodeController);
public:
	/*
	author：c3:zzz
	time:2025-10-23
	接口描述：获取条码列表（条件+分页）
	接口功能：根据条码类别分页查询条码信息，类型为：所有，二维码，条码,条码名，条码内容，条码备注
	请求方式：GET /barcode/query/?type=ALL&tag=name&TagContent=zzz&pageIndex=1&pageSize=10 （这是一个例子）
	返回数据：条码列表
	*/
	ENDPOINT_INFO(queryBarcodeClassPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("barcode.interface.pagequery"));//添加接口描述
		API_DEF_ADD_QUERY_PARAMS(Int32, "type", ZH_WORDS_GETTER("barcode.field.type"), 0, false);//添加参数
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("barcode.field.name"), "zzz", false);//添加参数
		API_DEF_ADD_QUERY_PARAMS(String, "content", ZH_WORDS_GETTER("barcode.field.content"), "zzz", false);//添加参数
		API_DEF_ADD_QUERY_PARAMS(String, "notes", ZH_WORDS_GETTER("barcode.field.notes"), "zzz", false);//添加参数
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(BarcodePageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/barcode/query-page", queryBarcodeClassPage, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, BarcodeClassPageQuery, queryParams);//获取参数
		API_HANDLER_RESP_VO(executeQueryBarcodeClassPage(query));//执行查询
	}
	/*
	author：c3:zzz
	time:2025-10-23
	接口描述：获取指定条码详情
	接口功能：根据id查询条码信息
	请求方式：GET /barcode/{id} （这是一个例子）
	返回数据：符合要求的那一个条码
	*/
	ENDPOINT_INFO(queryBarcodeById) {
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("barcode.interface.idquery"));
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("barcode.field.id"), "123", true);
		API_DEF_ADD_RSP_JSON_WRAPPER(BarcodeJsonVO);
	}
	ENDPOINT(API_M_GET, "/barcode/query-by-id/{id}", queryBarcodeById, PATH(String, id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeQueryBarcodeById(id));
	}
	/*
	author：c3:413-dik
	time:2025-10-25
	接口描述：添加条形码
	接口功能：添加条形码
	请求方式：POST /barcode （这是一个例子）
	返回数据：添加成功
	*/
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("barcode.interface.add"), addBrcode, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/barcode/add", addBrcode, BODY_DTO(BarcodeAddDTO::Wrapper, dto), executeAddBarcode(dto));

	/*
	author：c3:413-dik
	time:2025-10-25
	接口描述：下载条形码图片
	接口功能：下载条形码图片
	请求方式：GET /barcode/pic?content=test&type=BARCODE （这是一个例子）
	返回数据：test.png？
	*/
	API_DEF_ENDPOINT_INFO(
		ZH_WORDS_GETTER("barcode.interface.query-pic"), downloadBarcodePic, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "content", ZH_WORDS_GETTER("barcode.field.content"), "test", true);
	API_DEF_ADD_QUERY_PARAMS(Int32, "type", ZH_WORDS_GETTER("barcode.field.type"), 0, true);
	);
	ENDPOINT(API_M_GET, "/barcode/pic", downloadBarcodePic,
		QUERY(String, content),
		QUERY(Int32, type)) {
		return execDownloadBarcodePic(content, type);
	}

	/*
	author：c3:海棠花未眠
	time:2025-10-25
	接口描述：修改条形码接口
	接口功能：修改条形码接口
	请求方式：POST /barcode/modify （这是一个例子）
	返回数据：- code: 状态码
			  - message: "修改成功"或错误信息
			  - data: 修改后的条形码信息
	*/

	// 定义修改接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("barcode.interface.modify"),  // 接口中文描述
		modifySample,                          // 接口处理函数名
		StringJsonVO::Wrapper,                 // 返回值包装类型
		API_TAG                                // 接口标签
	);

	// 定义修改接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,                            // HTTP方法为PUT
		"/barcode/modify",                            // 接口路径
		modifySample,                         // 接口处理函数名
		BODY_DTO(BarcodeDTO::Wrapper, dto),   // 请求体DTO包装
		ModifyBarcode(dto, authObject->getPayload())  // 执行修改操作
	);

	/*
	author：c3:海棠花未眠
	time:2025-10-25
	接口描述：批量删除条形码接口
	接口功能：批量删除条形码接口
	请求方式：DELETE /barcode/delete （这是一个例子）
	返回数据：- code: 状态码
			  - message: "删除成功"或错误信息
			  - data: 被删除的条形码ID列表
	*/

	// 定义删除接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("barcode.interface.delete"),  // 接口中文描述
		removeSample,                             // 接口处理函数名
		ListJsonVO<String>::Wrapper,              // 返回值包装类型(列表)
		API_TAG                                   // 接口标签
	);

	// 定义删除接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_DEL,                               // HTTP方法为DELETE
		"/barcode/delete",                       // 接口路径
		removeSample,                            // 接口处理函数名
		BODY_DTO(List<String>, ids),             // 请求体DTO包装(条形码ID列表)
		RemoveBarcode(ids)                    // 执行删除操作
	);








private:
	BarcodePageJsonVO::Wrapper executeQueryBarcodeClassPage(const BarcodeClassPageQuery::Wrapper& query);
	BarcodeJsonVO::Wrapper executeQueryBarcodeById(const String& id);
	//添加条形码
	StringJsonVO::Wrapper executeAddBarcode(const BarcodeAddDTO::Wrapper& dto);
	// 执行传输图片处理
	std::shared_ptr<OutgoingResponse> execDownloadBarcodePic(const String& content, const Int32& type);
	// 3.3 修改数据
	StringJsonVO::Wrapper ModifyBarcode(const BarcodeDTO::Wrapper& dto, const PayloadDTO& payload);
	// 3.3 删除数据
	ListJsonVO<String>::Wrapper RemoveBarcode(const List<String>& ids);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 
#endif