#pragma once 

#ifndef _GOODS_CONTROLLER_H_
#define _GOODS_CONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/GoodsQuery/GoodsQuery.h"
#include "domain/vo/GoodsVO/GoodsVO.h"
#include "domain/dto/GoodsDTO/GoodsDTO.h"
//添加服务层头文件
#include "../../service/GoodsService//GoodsService.h"
//使用fastdfs头文件
#include "Macros.h"
#include "NacosClient.h"
#include "gtest/gtest.h"
#include "FastDfsClient.h"
//添加excel文件头文件
#include "ExcelComponent.h"


//开始标志
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("goods.tag")

class GoodsController : public oatpp::web::server::api::ApiController
{ 
	API_ACCESS_DECLARE(GoodsController);
public:
	// 添加商品接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goods.add.summary"), addCus, StringJsonVO::Wrapper, API_TAG);
	// 添加商品接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/goods/add", addCus, BODY_DTO(GoodsAddDTO::Wrapper, dto), executeAdd(dto));


	//删除商品接口描述（支持批量）
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("good.delete.summary"), removeGood, ListJsonVO<String>::Wrapper, API_TAG);
	//删除商品接口端点（支持批量）
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/goods/delete", removeGood, BODY_DTO(List<String>, ids), execRemoveGood(ids));


	// 导出商品数据接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("goods.export.summary"), exportGoods, GoodsQuery, Void, API_TAG);
	// 导出商品数据接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/goods/export", exportGoods, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(userQuery, GoodsQuery, queryParams); return execExportGoods(userQuery););


	// 定义查询所有商品信息接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("goods.query-all.summary"), queryAllGoods, GoodsQuery, GoodsListPageJsonVO::Wrapper, API_TAG);
	// 定义查询所有商品信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/goods/all", queryAllGoods, GoodsQuery, executeQueryAll(query));


	// 定义获取商品详细信息接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goods.query-one.summary"), queryOneGood, GoodsDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("goods.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
	);
	// 定义获取商品详细信息接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/goods/getdetail", queryOneGood, QUERY(String, id), executeQueryOne(id));


	// 定义新增商品信息接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goods.add.summary"), addGood, StringJsonVO::Wrapper, API_TAG);
	// 定义新增商品信息接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/goods/adddetail ", addGood, BODY_DTO(GoodsAddDTO::Wrapper, dto), executeAdd(dto));


	// 定义获取商品选择列表描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goods.specs.summary"), queryGoodSpecs, GoodsSpecJsonVO::Wrapper, API_TAG);
	// 定义获取商品选择列表端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/goods/specs", queryGoodSpecs, GoodsQuery, executeGetSpecs(query));

	// 修改商品接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("goods.modify.summary"), modifyCus, StringJsonVO::Wrapper, API_TAG)
	// 修改商品接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/goods/update", modifyCus, BODY_DTO(GoodsDetailDTO::Wrapper, dto), executeModify(dto))

	//excel报表导入商品,定义一个单文件上传接口,定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("goodsfile.upload.summary"), uploadFile, FileAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/goods/upload", uploadFile, REQUEST(std::shared_ptr<IncomingRequest>, request), execUploadOne(request));


private:
	//修改数据
	StringJsonVO::Wrapper executeModify(const GoodsDetailDTO::Wrapper& dto);
	//执行删除商品操作，传入的参数为商品id列表
	ListJsonVO<String>::Wrapper execRemoveGood(const List<String>& ids);
	//导出商品数据
	std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> execExportGoods(const GoodsQuery::Wrapper& query);
	//查询所有商品
	GoodsListPageJsonVO::Wrapper executeQueryAll(const GoodsQuery::Wrapper& query);
	//获取商品详细信息
	GoodsDetailJsonVO::Wrapper executeQueryOne(const oatpp::String& id);
	//添加商品
	StringJsonVO::Wrapper executeAdd(const GoodsAddDTO::Wrapper& dto);
	// 获取商品规格/型号列表
	GoodsSpecJsonVO::Wrapper executeGetSpecs(const GoodsQuery::Wrapper& query);
	//导入数据
	StringJsonVO::Wrapper execUploadOne(const std::shared_ptr<IncomingRequest>& request);
};


#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _GOODS_CONTROLLER_H_
