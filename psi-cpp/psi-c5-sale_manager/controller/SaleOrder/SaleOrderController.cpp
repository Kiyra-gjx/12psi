#include "stdafx.h"
#include "SaleOrderController.h"
#include "service/SorInfoService/SorInfoService.h"

#include "service/SorService/SorService.h"
#include "ExcelComponent.h"      // 项目Excel报表生成工具
#include "SimpleDateTimeFormat.h"
// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
SaleOrderListPageJsonVO::Wrapper SaleOrderController::executeQueryAllSaleOrder(const SaleOrderListQuery::Wrapper& query) {
    SorService sors;
    auto vo = SaleOrderListPageJsonVO::createShared();
    //这里不用查询是因为查询不到也是正常情况，返回空列表即可
    vo->success(sors.listAll(query));
	return vo;
}

//获取销售订单详情
SaleOrderDetailJsonVO::Wrapper SaleOrderController::executeQuerySaleOrderDetail(const String& id) {
    SorInfoService soris;
    auto vo = SaleOrderDetailJsonVO::createShared();
    auto data = soris.getSaleOrderDetail(id);
    if (data) {
        vo->success(data);
    }
    else {
        vo->fail({});
    }
	return vo;
}

SO_by_saleJsonVO::Wrapper SaleOrderController::executeAddSO(const SellGenerateDTO::Wrapper& dto)
{
    /*
        因为销售订单需要审核后才能生成销售单，所以DTO在销售订单层面一定是合法的
        所以销售单安全检查只需要处理与销售订单不一致的部分
        
        但是生成的销售单并不是真的销售单，只是响应给前端的一个“语法糖”，所以不能调用DO
        
    */
    SorService sr;
 
    auto data = sr.getSellGenerateData(dto);
    
    return data;
}

PO_by_saleJsonVO::Wrapper SaleOrderController::executeAddPO(const PurchaseGenerateDTO::Wrapper& dto)
{
    SorService sr;

    auto data = sr.getPurchaseGenerateData(dto);

    return data;
}

StringJsonVO::Wrapper SaleOrderController::executeAddSaleOrder(const SaleOrderAddDTO::Wrapper& dto) {
    SorService sors;
    auto vo = StringJsonVO::createShared();
    auto id = sors.saveData(dto);
    if (id == "") {
        cout << "false" << endl;
        vo->fail({});
    }
    else {
        vo->success(id);
    }
	return vo;
}

/*SorDeleteResultVO::Wrapper SaleOrderController::mockBatchDelete(const SorDeleteDTO::Wrapper& dto) {
    auto result = SorDeleteResultVO::createShared();
    result->successCount = 0;
    result->failureCount = 0;

    if (!dto || !dto->orderIds) {
        return result; // 空 DTO 或空列表，返回全 0
    }

    SorService service;

    for (const auto& id : *dto->orderIds) {
        
        if (!id) {
            result->failureCount = result->failureCount + 1;
            continue;
        }

        if (id->empty()) {
            result->failureCount= result->failureCount+1;
            continue;
        }

        try {
            // 调用 Service 删除单个 ID
            if (service.deleteById(id)) {  // ← 这里传的是 oatpp::String
                result->successCount= result->successCount+1;
            }
            else {
                result->failureCount= result->failureCount+1;
            }
        }
        catch (...) {
            result->failureCount= result->failureCount+1;
        }
    }

    return result;
}

SorAuditResultVO::Wrapper SaleOrderController::mockBatchApprove(const SorAuditDTO::Wrapper& dto) {
    SorService service;
    return service.batchApprove(dto);
}

SorAuditResultVO::Wrapper SaleOrderController::mockBatchUnapprove(const SorAuditDTO::Wrapper& dto) {
    SorService service;
    return service.batchUnapprove(dto);
}
*/
SorDeleteJsonVO::Wrapper SaleOrderController::executeBatchDelete(const SorDeleteDTO::Wrapper& dto)
{
    auto jvo = SorDeleteJsonVO::createShared();

    SorService service;
    auto result = service.batchDelete(dto);

    jvo->success(result);
    return jvo;
}

SorAuditJsonVO::Wrapper SaleOrderController::executeBatchApprove(const SorAuditDTO::Wrapper& dto)
{
    auto jvo = SorAuditJsonVO::createShared();

    SorService service;
    auto result = service.batchApprove(dto);

    jvo->success(result);
    return jvo;
}

SorAuditJsonVO::Wrapper SaleOrderController::executeBatchUnapprove(const SorAuditDTO::Wrapper& dto)
{
    auto jvo = SorAuditJsonVO::createShared();

    SorService service;
    auto result = service.batchUnapprove(dto);

    jvo->success(result);
    return jvo;
}
StringJsonVO::Wrapper SaleOrderController::executeUpdateSor(const SorUpdateDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	try {
		SorService service;
		bool issuccess = service.updateSaleOrder(dto);
		auto jvo = StringJsonVO::createShared();
		jvo->code = 200;
		jvo->data = issuccess ? "success" : "failed";
	}
	catch (const std::exception& e) {
		OATPP_LOGE("SaleOrderController", "Exception in executeUpdateSor: %s", e.what());
		jvo->code = 500;
		jvo->data = "error";
		return jvo;
	}
	return jvo;
}

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> SaleOrderController::executeExportSimple(const SorExportSimpleQuery::Wrapper& query)
{
	SorService service;
	auto dtoList = service.querySimpleReport(query);

	auto buff = ExcelComponent().writeVectorToBuff("SorSimpleExcel", [dtoList](ExcelComponent* ex) {
		ex->addHeader({
			ZH_WORDS_GETTER("saleOrder.field.frame"),
			ZH_WORDS_GETTER("saleOrder.field.customer"),
			ZH_WORDS_GETTER("saleOrder.field.time"),
			ZH_WORDS_GETTER("saleOrder.field.total"),
			ZH_WORDS_GETTER("saleOrder.field.actual"),
			ZH_WORDS_GETTER("saleOrder.field.arrival"),
			ZH_WORDS_GETTER("saleOrder.field.people"),
			ZH_WORDS_GETTER("saleOrder.field.examine"),
			ZH_WORDS_GETTER("saleOrder.field.state"),
			ZH_WORDS_GETTER("saleOrder.field.user"),
			ZH_WORDS_GETTER("saleOrder.field.data")
			});
		int row = 2;
		int col = 1;
		for (const auto& dto : dtoList) {
			col = 1;
			ex->setCellValue(row, col++, dto->frame);
			ex->setCellValue(row, col++, dto->customer);
			ex->setCellValue(row, col++, dto->time);
			ex->setCellValue(row, col++, std::to_string(dto->total));
			ex->setCellValue(row, col++, std::to_string(dto->actual));
			ex->setCellValue(row, col++, dto->arrival);
			ex->setCellValue(row, col++, dto->people);
			ex->setCellValue(row, col++, std::to_string(dto->examine));
			ex->setCellValue(row, col++, std::to_string(dto->state));
			ex->setCellValue(row, col++, dto->user);
			ex->setRowProperties(row++);
		}
		});

	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	std::string filePath = dfs.uploadFile(charData, buff.size(), "xlsx");
	std::string downloadUrl = urlPrefix + filePath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	auto response = createResponse(Status::CODE_200, fstring);

	std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename= " + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	return response;
}

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> SaleOrderController::executeExportDetail(const SorExportDetailQuery::Wrapper& query)
{
	SorService service;
	auto dtoList = service.queryDetailReport(query);

	auto buff = ExcelComponent().writeVectorToBuff("SorDetailExcel", [dtoList](ExcelComponent* ex) {
		int row = 1;
		int col = 1;
		if (dtoList.empty()) {
			ex->setCellValue(row, col++, "客户:无数据");
			ex->setCellValue(row, col++, "单据日期:无数据");
			ex->setCellValue(row, col++, "单据编号:无数据");
		}
		else {
			ex->setCellValue(row, col++, "客户:" + dtoList[0]->customer);
			ex->setCellValue(row, col++, "单据日期:" + dtoList[0]->time);
			ex->setCellValue(row, col++, "单据编号:" + dtoList[0]->number);
		}
		for (int i = 0; i < 11; i++) {
			ex->setCellValue(row, col++, "");
		}
		col = 1;
		ex->addHeader({
			ZH_WORDS_GETTER("goods.field.id"),
			ZH_WORDS_GETTER("goods.field.spec"),
			ZH_WORDS_GETTER("goods.field.attr"),
			ZH_WORDS_GETTER("goods.field.unit"),
			ZH_WORDS_GETTER("goods.field.warehouse"),
			ZH_WORDS_GETTER("goods.field.nums"),
			ZH_WORDS_GETTER("goods.field.handle"),
			ZH_WORDS_GETTER("goods.field.discount"),
			ZH_WORDS_GETTER("goods.field.dsc"),
			ZH_WORDS_GETTER("goods.field.total"),
			ZH_WORDS_GETTER("saleOrder.field.data")
		});
		ex->setRowProperties(row++);

		for (const auto& dto : dtoList) {
			for (const auto& item : *dto->items) {
				col = 1;
				ex->setCellValue(row, col++, item->goodsName);
				ex->setCellValue(row, col++, item->spec);
				ex->setCellValue(row, col++, item->attr);
				ex->setCellValue(row, col++, item->unit);
				ex->setCellValue(row, col++, item->warehouse);
				ex->setCellValue(row, col++, std::to_string(item->price));
				ex->setCellValue(row, col++, std::to_string(item->nums));
				ex->setCellValue(row, col++, std::to_string(item->handle));
				ex->setCellValue(row, col++, std::to_string(item->discount));
				ex->setCellValue(row, col++, std::to_string(item->dsc));
				ex->setCellValue(row, col++, std::to_string(item->total));
				ex->setCellValue(row, col++, item->data);
			}
			col = 1;
			ex->setCellValue(row, col++, "单据金额:" + std::to_string(dto->total));
			ex->setCellValue(row, col++, "实际金额:" + std::to_string(dto->actual));
			ex->setCellValue(row, col++, "关联人员:" + dto->people);
			ex->setCellValue(row, col++, "到货日期:" + dto->arrival);
			ex->setCellValue(row, col++, "物流信息:" + dto->logistics);
			ex->setCellValue(row, col++, "备注信息:" + dto->data);
		}
	});

	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	std::string filePath = dfs.uploadFile(charData, buff.size(), "xlsx");
	std::string downloadUrl = urlPrefix + filePath;
	OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

	// 4. 构造文件下载响应
	auto response = createResponse(Status::CODE_200, fstring);

	std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	return response;
}

Boolean SaleOrderController::execSorImport(const PayloadDTO& payload,const SorImportDTO::Wrapper& dto)
{
    SorService service;
    return Boolean(service.importData(payload,dto));
}
