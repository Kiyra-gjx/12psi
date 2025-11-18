#include "stdafx.h"
#include "SellController.h"
#include"service/SellService/SellService.h"
#include "../../service/SellService/SellService.h"
#include "../ApiDeclarativeServicesHelper.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"


// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"

//判断info关键字段非空  (数据库内的非空字段+仓库+批次)
static bool is_sellinfo_notnull(const SellSingleInfoDTO::Wrapper& dto) {
	return dto->unit && dto->price && dto->nums && dto->discount && dto->dsc && dto->total && dto->goods && dto->warehouse && dto->batch;
}

//判断sell关键字段非空
static bool is_sell_notnull(const SellCreateDTO::Wrapper& dto) {
	bool notnull =
		dto->frame && dto->customer && dto->time && dto->number && dto->user
		&& dto->totalMoney && dto->actual && dto->money && dto->cost && dto->sellinfos
		&& dto->examine && dto->nucleus && dto->cse && dto->invoice && dto->check;
	if (notnull) {
		for (auto& one : *dto->sellinfos) {
			if (!is_sellinfo_notnull(one)) return false;
		}
		return true;
	}
	return false;
}

//判断sellinfo所有字段的有效性(不支持价格，数量<0)
static bool is_sellinfo_valid(const SellSingleInfoDTO::Wrapper& dto) {
	if (dto->source && dto->source->size() > 32) return false;
	if (dto->goods->empty() || dto->goods->size() > 32) return false;
	if (dto->attr && dto->attr->size() > 64) return false;
	if (dto->unit->empty() || dto->unit->size() > 32) return false;
	if (dto->warehouse->empty() || dto->warehouse->size() > 32) return false;
	if (dto->batch->empty() || dto->batch->size() > 32) return false;
	if (dto->mfd && dto->mfd->size() > 30) return false;                //暂时不解析时间
	if (dto->price.getPtr() == nullptr || dto->price < 0 || dto->price > 1e13) return false;
	if (dto->nums.getPtr() == nullptr || dto->nums < 0 || dto->nums > 1e13) return false;
	if (dto->discount.getPtr() == nullptr || dto->discount < 0 || dto->discount > 1e6) return false;
	if (dto->dsc.getPtr() == nullptr || dto->dsc < 0 || dto->dsc > 1e13) return false;
	if (dto->total.getPtr() == nullptr || dto->total < 0 || dto->total > 1e13) return false;
	if (dto->data && dto->data->size() > 256) return false;
	return true;
}


//判断sell所有字段的有效性
static bool is_sell_valid(const SellCreateDTO::Wrapper& dto) {
	if (dto->source && dto->source->size() > 32) return false;
	if (dto->frame->empty() || dto->frame->size() > 32) return false;
	if (dto->customer->empty() || dto->customer->size() > 32) return false;
	if (dto->time->empty() || dto->time->size() > 30) return false;         //暂时不解析时间
	if (dto->number->empty() || dto->number->size() > 32) return false;
	if (dto->actual.getPtr() == nullptr || dto->actual < 0 || dto->actual > 1e17) return false;
	if (dto->money.getPtr() == nullptr || dto->money < 0 || dto->money > 1e17) return false;
	if (dto->cost.getPtr() == nullptr || dto->cost < 0 || dto->cost > 1e17) return false;
	if (dto->account && dto->account->size() > 32) return false;
	if (dto->people && dto->people->size() > 32) return false;
	if (dto->logistics && dto->logistics->size() > 65535) return false;
	if (dto->file && dto->file->size() > 65535) return false;
	if (dto->data && dto->data->size() > 256) return false;
	if (dto->more && dto->more->size() > 65535) return false;
	if (dto->examine.getPtr() == nullptr || dto->examine < 0 || dto->examine > 1) return false;
	if (dto->nucleus.getPtr() == nullptr || dto->nucleus < 0 || dto->nucleus > 2) return false;
	if (dto->cse.getPtr() == nullptr || dto->cse < 0 || dto->cse > 3) return false;
	if (dto->invoice.getPtr() == nullptr || dto->invoice < 0 || dto->invoice > 3) return false;
	if (dto->check.getPtr() == nullptr || dto->check < 0 || dto->check > 1) return false;
	if (dto->user->empty() || dto->user->size() > 32) return false;
	for (const auto& one : *dto->sellinfos) {
		if (!is_sellinfo_valid(one)) {
			return false;
		}
	}
	return true;
}

Boolean SellController::execSellImport(const PayloadDTO& payload, const SellImportDTO::Wrapper& dto) {
	SellService service;
	return Boolean(service.importData(payload, dto));
}

// 查询销售单列表
SellListJsonVO::Wrapper SellController::execSellQueryList(const SellListQuery::Wrapper& query)
{
	static SellService service;
	auto dto = service.queryWithPage(query);
	auto jvo = SellListJsonVO::createShared();
	jvo->success(dto);
	return jvo;
}

// 查询销售单详情
SellDetailJsonVO::Wrapper SellController::execSellQueryDetail(const SellDetailQuery::Wrapper& query)
{
	static SellService service;
	auto dto = service.queryById(query->id);
	auto jvo = SellDetailJsonVO::createShared();
	jvo->success(dto);
	return jvo;
}

// 新增销售单
SellAddJsonVO::Wrapper SellController::execSellAddList(const SellCreateDTO::Wrapper& dto)
{
	auto jvo = SellAddJsonVO::createShared();
	SellService service;

	if (!is_sell_notnull(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!is_sell_valid(dto)) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	string id = service.create(dto);
	jvo->success(id);
	return jvo;
}


//模块--慵懒的汪负责
StringJsonVO::Wrapper SellController::executeModify(const SellUpdateDTO::Wrapper& dto, const PayloadDTO& payload) {
	auto jvo = StringJsonVO::createShared();
	if (!dto->id) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	//定义一个service
	SellService service;
	//执行数据修改
	dto->setPayload(&payload);
	//问题应该在update部分****
	if (service.updateData(dto)) {
		jvo->success(dto->id);
	}
	else {
		jvo->fail(dto->id);
	}
	//问题应该在update部分****
	return jvo;
}
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> SellController::executequerysimple(const  SellListQuery::Wrapper& query) {
	// 定义一个Service
	SellService service;
	// 查询数据
	auto result = service.listAll(query);

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("sell.simple",
		[result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("sell.fileld.id") ,
				ZH_WORDS_GETTER("sell.fileld.time") ,
				ZH_WORDS_GETTER("sell.fileld.number") ,
				ZH_WORDS_GETTER("sell.fileld.total")
				});
			// 写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->id);
				ex->setCellValue(row, col++, item->time);
				ex->setCellValue(row, col++, item->number);
				ex->setCellValue(row, col, std::to_string(item->total));
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 测试将报表上传到fastdfs
	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	string filepath = dfs.uploadFile(charData, buff.size(), "xlsx");
	// 打印文件上传成功后的下载地址
	string downloadUrl = urlPrefix + filepath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 影响成功结果
	return response;
}
std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> SellController::executequerymore(const  SellListQuery::Wrapper& query) {
	// 定义一个Service
	SellService service;
	// 查询数据
	auto result = service.listAll(query);

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("sell.detail",
		[result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
					ZH_WORDS_GETTER("sell.fileld.id"),
					ZH_WORDS_GETTER("sell.fileld.time"),
					ZH_WORDS_GETTER("sell.fileld.number"),
					ZH_WORDS_GETTER("sell.fileld.total"),
					ZH_WORDS_GETTER("sell.fileld.frame"),
					ZH_WORDS_GETTER("sell.fileld.customer"),
					ZH_WORDS_GETTER("sell.fileld.user"),
					ZH_WORDS_GETTER("sell.fileld.actual"),
					ZH_WORDS_GETTER("sell.fileld.money"),
					ZH_WORDS_GETTER("sell.fileld.cost"),
					ZH_WORDS_GETTER("sell.fileld.examine"),
					ZH_WORDS_GETTER("sell.fileld.nucleus"),
					ZH_WORDS_GETTER("sell.fileld.cse"),
					ZH_WORDS_GETTER("sell.fileld.invoice"),
					ZH_WORDS_GETTER("sell.fileld.check"),
				});
			// 写入数据
			int row = 2;
			int col = 1;
			for (auto item : *(result->rows.get())) {
				col = 1;
				ex->setCellValue(row, col++, item->id);
				ex->setCellValue(row, col++, item->time);
				ex->setCellValue(row, col++, item->number);
				ex->setCellValue(row, col++, std::to_string(item->total));
				ex->setCellValue(row, col++, item->frame);
				ex->setCellValue(row, col++, item->customer);
				ex->setCellValue(row, col++, item->user);
				ex->setCellValue(row, col++, std::to_string(item->actual));
				ex->setCellValue(row, col++, std::to_string(item->money));
				ex->setCellValue(row, col++, std::to_string(item->cost));
				ex->setCellValue(row, col++, std::to_string(item->examine));
				ex->setCellValue(row, col++, std::to_string(item->nucleus));
				ex->setCellValue(row, col++, std::to_string(item->cse));
				ex->setCellValue(row, col++, std::to_string(item->invoice));
				ex->setCellValue(row, col, std::to_string(item->check));
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 测试将报表上传到fastdfs
	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	string filepath = dfs.uploadFile(charData, buff.size(), "xlsx");
	// 打印文件上传成功后的下载地址
	string downloadUrl = urlPrefix + filepath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 影响成功结果
	return response;
}

SellGenerateReturnDTO::Wrapper SellController::execSellGenerateReturn(const oatpp::String& number)
{
	SellService service;
	return service.getSellGenerateReturn(number);

}

SellAuditJsonVO::Wrapper SellController::executeBatchApprove(const SellAuditDTO::Wrapper& dto) {
	auto jvo = SellAuditJsonVO::createShared();
	SellService service;
	auto result = service.batchApprove(dto);
	jvo->success(result);
	return jvo;
}

SellAuditJsonVO::Wrapper SellController::executeBatchUnapprove(const SellAuditDTO::Wrapper& dto) {
	auto jvo = SellAuditJsonVO::createShared();
	SellService service;
	auto result = service.batchUnapprove(dto);
	jvo->success(result);
	return jvo;
}

SalenoteDeleteJsonVO::Wrapper
SellController::executeBatchDelete(const SalenoteDeleteDTO::Wrapper& dto) {
	return {};
}