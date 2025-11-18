#include "stdafx.h"
#include "CustomerController.h"
#include "service/CustomerService/CustomerService.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
// FastDFS需要导入的头
#include "ServerInfo.h" 
#include "NacosClient.h"
#include "FastDfsClient.h"

StringJsonVO::Wrapper CustomerController::executeModifyCustomer(const CustomerModifyDTO::Wrapper& dto) {
	CustomerService cs;
	auto res = StringJsonVO::createShared();
	auto res_id = cs.modifyCustomer(dto);
	if (res_id == dto->id.getValue("") && res_id != ""s)
	{
		res->success(res_id);
	}
	else
	{
		res->fail("");
	}
	return res;
}

StringJsonVO::Wrapper CustomerController::executeDeleteCustomer(const List<String>& ids) {
	CustomerService cs;
	auto res = StringJsonVO::createShared();
	auto res_num = cs.deleteCustomer(ids);
	if (res_num != 0)
	{
		res->success(to_string(res_num));
	}
	else
	{
		res->fail("");
	}
	return res;
}

//定义导入数据函数@快乐五香蛋
StringJsonVO::Wrapper CustomerController::importcus(std::shared_ptr<IncomingRequest> request)
{
		//初始化
		API_MULTIPART_INIT(container, reader);

		//配置读取器
		API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

		//读取数据
		request->transferBody(&reader);

		//打印上传总部分分数
		OATPP_LOGD("Multipart", "parts_count=%d", container->count());

		API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);

		if (!file)
		{
			auto jvo = StringJsonVO::createShared();
			jvo->fail("文件为空");
			return jvo;
		}
		auto excel = ExcelComponent().readIntoVector(file->data(), file->size(), "NodCloud");
	
		CustomerService service;
		bool status = service.Import(excel);

		auto jvo = StringJsonVO::createShared();
		if (status)
		{
			jvo->success("success");
		}
		else
		{
			jvo->fail("");
		}
		return jvo;
	
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>  CustomerController::execExportCus(const CustomerQuery::Wrapper& query)
{
	//定义一个service
	CustomerService service;
	//查询数据
	auto result = service.execExport(query);
	//将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("NodCloud",
		[result](ExcelComponent* ex) {
			//写入表头
			ex->addHeader({
				 ZH_WORDS_GETTER("cus.field.name"),
				 ZH_WORDS_GETTER("cus.field.number"),
				 ZH_WORDS_GETTER("cus.field.category"),
				 ZH_WORDS_GETTER("cus.field.grade"),
				 ZH_WORDS_GETTER("cus.field.bank"),
				 ZH_WORDS_GETTER("cus.field.account"),
				 ZH_WORDS_GETTER("cus.field.tax"),
				 ZH_WORDS_GETTER("cus.field.balance"),
				 ZH_WORDS_GETTER("cus.field.frame"),
				 ZH_WORDS_GETTER("cus.field.user"),
				 ZH_WORDS_GETTER("cus.field.data"),
				 ZH_WORDS_GETTER("cus.field.contacts")

				});
			//写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->name);
				ex->setCellValue(row, col++, item->number);
				ex->setCellValue(row, col++, item->category);
				ex->setCellValue(row, col++, item->grade);
				ex->setCellValue(row, col++, item->bank);
				ex->setCellValue(row, col++, item->account);
				ex->setCellValue(row, col++, item->tax);
				ex->setCellValue(row, col++, std::to_string(item->balance));
				ex->setCellValue(row, col++, item->frame);
				ex->setCellValue(row, col++, item->user);
				ex->setCellValue(row, col++, item->data);
				ex->setCellValue(row++, col++, item->contacts);

			}
		});
	//组装
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	//将报表上传到fastdfs
	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	string filepath = dfs.uploadFile(charData, buff.size(), "xlsx");
	//打印文件上传成功后的下载地址
	string downloadUrl = urlPrefix + filepath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	auto response = createResponse(Status::CODE_200, fstring);

	std::string filename = "rp-customer-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spredsheetml.sheet");

	return response;
}

// 新增客户接口
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> CustomerController::addCustomer(const CustomerDTO::Wrapper& dto, const std::shared_ptr<CustomerAuthorizeObject>& authObject)
{
	CustomerService customerService;

	auto vo = CustomerAddResponseVO::createShared();

	if (!dto->user || !dto->name || !dto->frame || !dto->grade || !dto->number || !dto->category ) {
		vo->init(nullptr, RS_PARAMS_INVALID);
		return createDtoResponse(Status::CODE_400, vo);
	}

	vo = customerService.addCustomer(dto);
	return createDtoResponse(Status::CODE_200, vo);


}

// 修改客户接口

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> CustomerController::getCustomerInfo(const oatpp::String& customerId, const std::shared_ptr<CustomerAuthorizeObject>& authObject)
{
	CustomerService customerService;

	auto vo = CustomerGetResponseVO::createShared();

	if (customerId == nullptr || customerId->size() == 0) {
		vo->init(nullptr, RS_PARAMS_INVALID);
		return createDtoResponse(Status::CODE_200, vo);
	}

	auto dto = CustomerGetDTO::createShared();

	dto->id = customerId;

	vo = customerService.getCustomerInfo(dto);
	return createDtoResponse(Status::CODE_200, vo);
}

// 查询所有客户
CustomerListPageJsonVO::Wrapper CustomerController::executeQueryAll(const CustomerQuery::Wrapper& query)
{
	// 定义一个Service
	CustomerService service;
	// 查询数据
	auto result = service.listAll(query);
	// 响应结果
	auto jvo = CustomerListPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}