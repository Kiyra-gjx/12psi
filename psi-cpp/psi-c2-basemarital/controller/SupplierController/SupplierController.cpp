#include "stdafx.h"
#include "SupplierController.h"
#include "../../service/SupplierService/SupplierService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "ServerInfo.h"
#include "NacosClient.h"
#include "id/UuidFacade.h"
#include "FastDfsClient.h"


ListJsonVO<oatpp::web::server::api::ApiController::String>::Wrapper SupplierController::execRemove(const List<String> ids)
{
	//定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	//参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	//定义一个Service
	SupplierService service;
	//执行数据删除
	if (service.removeData(ids)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}
	return jvo;
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> SupplierController::executeExport(const SupplierQuery::Wrapper& query)
{
	//定义一个service
	SupplierService service;
	//查询数据
	auto result = service.listAll(query);
	//将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("supplier",
		[result](ExcelComponent* ex) {
			//写入表头
			ex->addHeader({
				 ZH_WORDS_GETTER("supplier.field.id"),
				 ZH_WORDS_GETTER("supplier.field.name"),
				 ZH_WORDS_GETTER("supplier.field.py"),
				 ZH_WORDS_GETTER("supplier.field.number"),
				 ZH_WORDS_GETTER("supplier.field.frame"),
				 ZH_WORDS_GETTER("supplier.field.user"),
				 ZH_WORDS_GETTER("supplier.field.category"),
				 ZH_WORDS_GETTER("supplier.field.rate"),
				 ZH_WORDS_GETTER("supplier.field.bank"),
				 ZH_WORDS_GETTER("supplier.field.account"),
				 ZH_WORDS_GETTER("supplier.field.tax"),
				 ZH_WORDS_GETTER("supplier.field.data"),
				 ZH_WORDS_GETTER("supplier.field.contacts"),
				 ZH_WORDS_GETTER("supplier.field.balance"),
				 ZH_WORDS_GETTER("supplier.field.more")
				});
			//写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->id);
				ex->setCellValue(row, col++, item->name);
				ex->setCellValue(row, col++, item->py);
				ex->setCellValue(row, col++, item->number);
				ex->setCellValue(row, col++, item->frame);
				ex->setCellValue(row, col++, item->user);
				ex->setCellValue(row, col++, item->category);
				ex->setCellValue(row, col++, std::to_string(item->rate));
				ex->setCellValue(row, col++, item->bank);
				ex->setCellValue(row, col++, item->account);
				ex->setCellValue(row, col++, item->tax);
				ex->setCellValue(row, col++, item->data);
				ex->setCellValue(row, col++, item->contacts);
				ex->setCellValue(row, col++, std::to_string(item->balance));
				ex->setCellValue(row, col++, item->more);

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

	std::string filename = "rp-supplier-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spredsheetml.sheet");

	return response;
}

StringJsonVO::Wrapper SupplierController::executeImport(std::shared_ptr<IncomingRequest> request)
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
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "filename", filename);
	string filepath = "";

	if (!file)
	{
		auto jvo = StringJsonVO::createShared();
		jvo->fail("null");
		return jvo;
	}

	auto excel = ExcelComponent().readIntoVector(file->data(), file->size(), "supplier");
	auto jvo = StringJsonVO::createShared();
	SupplierService service;
	list<SupplierDTO> dto;

	if (excel.size() < 2)
	{
		jvo->fail("empty");
		return jvo;
	}

	int rowNumber = 1;  // 从1开始计数(包含表头)
	bool isFirstRow = true;

	for (const auto& data : excel)
	{
		// 跳过表头
		if (isFirstRow) {
			isFirstRow = false;
			rowNumber++;
			continue;
		}

		SupplierDTO sdto;
		int i = 0;
		UuidFacade uf;
		auto ids = uf.genUuid();
		sdto.id = ids;

		// 1. 名字
		if (i < data.size() && !data[i].empty())
		{
			sdto.name = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 2. 拼音
		if (i < data.size() && !data[i].empty())
		{
			sdto.py = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 3. 编号
		if (i < data.size() && !data[i].empty())
		{
			sdto.number = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 4. 框架
		if (i < data.size() && !data[i].empty())
		{
			sdto.frame = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 5. 用户
		if (i < data.size() && !data[i].empty())
		{
			sdto.user = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 6. 类别
		if (i < data.size() && !data[i].empty())
		{
			sdto.category = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 7. 税率
		if (i < data.size() && !data[i].empty())
		{
			try {
				sdto.rate = std::stoi(data[i]);
				i++;
			}
			catch (const std::exception& e) {
				std::string str = "[" + filename + "] " +
					"模板文件第" + std::to_string(rowNumber) + "行 " +
					"税率格式错误: " + data[i];
				jvo->fail(str);
				return jvo;
			}
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 8. 银行
		if (i < data.size() && !data[i].empty())
		{
			sdto.bank = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 9. 账号
		if (i < data.size() && !data[i].empty())
		{
			sdto.account = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 10. 税号
		if (i < data.size() && !data[i].empty())
		{
			sdto.tax = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 11. 数据
		if (i < data.size() && !data[i].empty())
		{
			sdto.data = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 12. 联系人
		if (i < data.size() && !data[i].empty())
		{
			sdto.contacts = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		// 13. 余额
		if (i < data.size() && !data[i].empty())
		{
			try {
				sdto.balance = std::stoi(data[i]);
				i++;
			}
			catch (const std::exception& e) {
				std::string str = "[" + std::string(filename->c_str()) + "] " +
					"模板文件第" + std::to_string(rowNumber) + "行 " +
					"余额格式错误: " + data[i];
				jvo->fail(str);
				return jvo;
			}
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}
		// 14. 备注
		if (i < data.size() && !data[i].empty())
		{
			sdto.more = data[i];
			i++;
		}
		else {
			std::string str = "[" + std::string(filename->c_str()) + "] " +
				"模板文件第" + std::to_string(rowNumber) + "行 " +
				"所属" + "" + (i >= data.size() ? "[" + data[i] + "]" + "未匹配" : "");
			jvo->fail(str);
			return jvo;
		}

		dto.push_back(sdto);
		rowNumber++;
	}

	auto res = service.Import(dto);

	if (res)
	{
		jvo->success("导入成功,共导入" + std::to_string(dto.size()) + "条数据");
	}
	else {
		jvo->fail("fail");
	}

	return jvo;
}

StringJsonVO::Wrapper SupplierController::executeAddSupplier(const SupplierAddDTO::Wrapper& dto)
{
	SupplierService sse;
	auto jvo = StringJsonVO::createShared();
	// 保存数据
	auto id = sse.saveSupplier(dto);
	// 保存成功
	if (id != "")
		jvo->success(id);
	else
		jvo->fail({});
	return jvo;
}


StringJsonVO::Wrapper SupplierController::executeupdateSupplier(const SupplierUpdateDTO::Wrapper& dto)
{
	SupplierService sse;
	auto jvo = StringJsonVO::createShared();

	auto bl = sse.updateSupplier(dto);

	if (bl)
		jvo->success("");
	else
		jvo->fail({});
	return jvo;
}

SupplierListPageJsonVO::Wrapper SupplierController::executeQueryAll(const SupplierQuery::Wrapper& query)
{
	// 创建服务对象
	SupplierService service;
	// 调用服务层获取分页数据
	auto pageData = service.listSuppliers(query);

	auto PageJson = SupplierListPageJsonVO::createShared();
	// 判断结果
	if (pageData && pageData->total > 0)
		PageJson->success(pageData);
	else
		PageJson->fail(SupplierListPageDTO::createShared());
	return PageJson;
}

SupplierDetailJsonVO::Wrapper SupplierController::executeQueryDetail(const oatpp::String& name)
{	
	auto json = SupplierDetailJsonVO::createShared();
	if (!name)
	{
		json->init(nullptr, RS_PARAMS_INVALID);
		return json;
	}
	SupplierService service;
	auto detail = service.getSupplierDetail(name.getValue({}));
	json->success(detail);
	return json;
}