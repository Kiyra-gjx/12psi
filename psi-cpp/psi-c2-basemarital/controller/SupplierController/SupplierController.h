#ifndef _SUPPLIER_CONTROLLER_H
#define _SUPPLIER_CONTROLLER_H
#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "../../domain/dto/SupplierDTO/SupplierDTO.h"
#include "../../domain/vo/SupplierVO/SupplierVO.h"
#include "../../domain/query/SupplierQuery/SupplierQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("sup.tag")

class SupplierController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(SupplierController);
public:
	// 导入数据
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("sup.import.summary"), imSup, SupFileAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 导入数据
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sup/import", imSup, REQUEST(std::shared_ptr<IncomingRequest>, request), executeImport(request));


	// 导出数据
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("sup.export.summary"), exSup, SupplierQuery, Void, API_TAG);	
	// 导出数据
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/sup/export", exSup, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(supQuery, SupplierQuery, queryParams);return executeExport(supQuery););


	// 删除供应商
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("sup.delete.summary"), removeSup, ListJsonVO<String>::Wrapper, API_TAG);
	// 删除供应商
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/sup/delete", removeSup, BODY_DTO(List<String>, ids), execRemove(ids));


	// 新增供应商描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("sup.addSupplier"), addSupplier, StringJsonVO::Wrapper, API_TAG);
	// 新增供应商端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/sup/add", addSupplier, BODY_DTO(SupplierAddDTO::Wrapper, dto), executeAddSupplier(dto));


	// 修改供应商信息描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("sup.updateSupplier"), updateSupplier, StringJsonVO::Wrapper, API_TAG);
	// 修改供应商信息端点
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/sup/update", updateSupplier, BODY_DTO(SupplierUpdateDTO::Wrapper, dto), executeupdateSupplier(dto));
	

	//定义获取供应商的接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("sup.query_all.summary"), queryAllSupplier, SupplierQuery, SupplierListPageJsonVO::Wrapper, API_TAG);
	//定义获取供应商的接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/sup/queryall", queryAllSupplier, SupplierQuery, executeQueryAll(query));


	// 获取供应商详细信息
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("sup.detail.list"), querySupplierDetail,SupplierQuery, SupplierDetailJsonVO::Wrapper, API_TAG);
	// 获取供应商详细信息
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/sup/detail", querySupplierDetail, QUERY(String, name), executeQueryDetail(name));

private:
	//获取供应商列表
	SupplierListPageJsonVO::Wrapper executeQueryAll(const SupplierQuery::Wrapper& query);
	//获取供应商详细信息
	SupplierDetailJsonVO::Wrapper executeQueryDetail(const oatpp::String& name);
	//导入数据
	StringJsonVO::Wrapper executeImport(std::shared_ptr<IncomingRequest> request);
	//导出数据
	std::shared_ptr<OutgoingResponse> executeExport(const SupplierQuery::Wrapper& query);
	//删除供应商
	ListJsonVO<String>::Wrapper execRemove(const List<String> ids);
	//新增供应商的实现接口
	StringJsonVO::Wrapper executeAddSupplier(const SupplierAddDTO::Wrapper& dto);
	//修改供应商信息描述
	StringJsonVO::Wrapper executeupdateSupplier(const SupplierUpdateDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG

#endif // !_SUPPLIER_CONTROLLER_H