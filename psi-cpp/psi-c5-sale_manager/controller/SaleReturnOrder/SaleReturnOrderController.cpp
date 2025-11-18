#include "stdafx.h"
#include "SaleReturnOrderController.h"
#include "../../service/SreService/SreService.h"
//松 额外引入的头文件
#include "./service/SreService/SreService.h"
#include "ExcelComponent.h"      // 项目Excel报表生成工具
#include "SimpleDateTimeFormat.h"
// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"

//判断info关键字段非空  (数据库内的非空字段+仓库+批次)
static bool is_sreinfo_notnull(const SingleInfoDTO::Wrapper& dto) {
    return dto->unit && dto->price && dto->nums && dto->discount && dto->dsc && dto->total && dto->goods && dto->warehouse && dto->batch;
}

//判断sre关键字段非空
static bool is_sre_notnull(const SreAddDTO::Wrapper& dto) {
    bool notnull = 
        dto->frame && dto->customer && dto->time && dto->number && dto->user
     && dto->totalMoney && dto->actual && dto->money && dto->cost && dto->infos
     && dto->examine && dto->nucleus && dto->cse && dto->invoice && dto->check;
    if (notnull) {
        for (auto& one : *dto->infos) {
            if (!is_sreinfo_notnull(one)) return false;
        }
        return true;
    }
    return false;
}

//判断sreinfo所有字段的有效性(不支持价格，数量<0)
static bool is_sreinfo_valid(const SingleInfoDTO::Wrapper& dto) {
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


//判断sre所有字段的有效性
static bool is_sre_valid(const SreAddDTO::Wrapper& dto) {
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
    for (const auto& one : *dto->infos) {
        if (!is_sreinfo_valid(one)) {
            return false;
        }
    }
    return true;
}

//退货单分页查询数据
SreListJsonVO::Wrapper SaleReturnOrderController::execSreQueryList(const SreListQuery::Wrapper& query) {
     SreService service;
     auto result = service.listAll(query);
     auto jvo = SreListJsonVO::createShared();
     jvo->success(result);
     return jvo;
}

//退货单详情查询数据
SreDetailJsonVO::Wrapper SaleReturnOrderController::execSreQueryDetail(const SreDetailQuery::Wrapper& query) {
    SreService service;
    auto result = service.getDetail(query);
    auto jvo = SreDetailJsonVO::createShared();
    jvo->success(result);
    return jvo;
}

//退货单
SreAddJsonVO::Wrapper SaleReturnOrderController::execSreAddList(const SreAddDTO::Wrapper& dto) {
	auto jvo = SreAddJsonVO::createShared();
    SreService service;

    if (!is_sre_notnull(dto)) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    if (!is_sre_valid(dto)) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    string id = service.addList(dto);
    jvo->success(id);
	return jvo;
}
// 执行函数：修改销售退货单
StringJsonVO::Wrapper SaleReturnOrderController::executeUpdateSre(const SreUpdateDTO::Wrapper& sreUpdateDto) {
    SreService service;
    return service.update(sreUpdateDto);
}
// 辅助函数：状态转换为中文描述
namespace {
    // 辅助方法：将状态码转换为中文描述
    std::string getNucleusStatus(oatpp::Int8 status) {
        switch (status) {
        case 0: return "未核销";
        case 1: return "部分核销";
        case 2: return "已核销";
        default: return "未知";
        }
    }

    std::string getCseStatus(oatpp::Int8 status) {
        switch (status) {
        case 0: return "未结算";
        case 1: return "部分结算";
        case 2: return "已结算";
        case 3: return "无需结算";
        default: return "未知";
        }
    }

    std::string getInvoiceStatus(oatpp::Int8 status) {
        switch (status) {
        case 0: return "未开票";
        case 1: return "部分开票";
        case 2: return "已开票";
        case 3: return "无需开票";
        default: return "未知";
        }
    }
}
//  执行函数：导出简单报表 空实现
std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> SaleReturnOrderController::executeExportSreSimple(const SreExportSimpleQuery::Wrapper& query) {
    // 1. 调用Service查询DTO列表
    SreService service;
    auto dtoList = service.querySimpleList(query);

    // 2. 生成Excel报表（复用示例中ExcelComponent的writeVectorToBuff方法）
    auto buff = ExcelComponent().writeVectorToBuff("SresimpleExcel",
        [dtoList](ExcelComponent* ex) {
            // 写入表头
            ex->addHeader({
                ZH_WORDS_GETTER("saleReturnOrder.field.frame"),    // 所属组织
                ZH_WORDS_GETTER("saleReturnOrder.field.customer"), // 客户
                ZH_WORDS_GETTER("saleReturnOrder.field.time"),     // 单据时间
                ZH_WORDS_GETTER("saleReturnOrder.field.number"),   // 单据编号
                ZH_WORDS_GETTER("saleReturnOrder.field.total"),    // 单据金额
                ZH_WORDS_GETTER("saleReturnOrder.field.actual"),   // 实际金额
                ZH_WORDS_GETTER("saleReturnOrder.field.money"),    // 实付金额
                ZH_WORDS_GETTER("saleReturnOrder.field.cost"),     // 单据费用
                ZH_WORDS_GETTER("saleReturnOrder.field.people"),   // 关联人员
                ZH_WORDS_GETTER("saleReturnOrder.field.examine"),  // 审核状态
                ZH_WORDS_GETTER("saleReturnOrder.field.nucleus"),  // 核销状态
                ZH_WORDS_GETTER("saleReturnOrder.field.cse"),      // 费用状态
                ZH_WORDS_GETTER("saleReturnOrder.field.invoice"),  // 发票状态
                ZH_WORDS_GETTER("saleReturnOrder.field.check"),    // 核对状态
                ZH_WORDS_GETTER("saleReturnOrder.field.user"),     // 制单人
                ZH_WORDS_GETTER("saleReturnOrder.field.data")      // 备注信息
                });
            // 写入数据
            int row = 2;
            int col = 1;
            for (const auto& dto : dtoList) {
                col = 1;
                ex->setCellValue(row, col++, dto->frame);
                ex->setCellValue(row, col++, dto->customer);
                ex->setCellValue(row, col++, dto->time);
                ex->setCellValue(row, col++, dto->number);
                ex->setCellValue(row, col++, std::to_string(dto->total));
                ex->setCellValue(row, col++, std::to_string(dto->actual));
                ex->setCellValue(row, col++, std::to_string(dto->money));
                ex->setCellValue(row, col++, std::to_string(dto->cost));
                ex->setCellValue(row, col++, dto->people);
                ex->setCellValue(row, col++, dto->examine == 0 ? "未审核" : "已审核");
                ex->setCellValue(row, col++, getNucleusStatus(dto->nucleus));
                ex->setCellValue(row, col++, getCseStatus(dto->cse));
                ex->setCellValue(row, col++, getInvoiceStatus(dto->invoice));
                ex->setCellValue(row, col++, dto->check == 0 ? "未核对" : "已核对");
                ex->setCellValue(row, col++, dto->user);
                ex->setCellValue(row, col, dto->data);
                ex->setRowProperties(row++);
            }
        }
    );

    // 3. 组装下发数据并上传到FastDFS
    const char* charData = reinterpret_cast<const char*>(buff.data());
    auto fstring = String(charData, buff.size());

    // 初始化FastDFS客户端
    ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
    std::string filePath = dfs.uploadFile(charData, buff.size(), "xlsx");
    std::string downloadUrl = urlPrefix + filePath;
    OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());

    // 4. 构造文件下载响应
    auto response = createResponse(Status::CODE_200, fstring);

    std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
    response->putHeader("Content-Disposition", "attachment; filename= " + filename);
    response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

    return response;
}
namespace {
    // 辅助函数：状态转换为中文描述
    std::string getExamineStatus(oatpp::Int32 status) {
        return status == 0 ? "未审核" : "已审核";
    }

    std::string getInvoiceStatus(oatpp::Int32 status) {
        switch (status) {
        case 0: return "未开票";
        case 1: return "部分开票";
        case 2: return "已开票";
        case 3: return "无需开票";
        default: return "未知";
        }
    }

    std::string getNucleusStatus(oatpp::Float64 status) {
        switch (static_cast<int>(status)) {
        case 0: return "未核销";
        case 1: return "部分核销";
        case 2: return "已核销";
        default: return "未知";
        }
    }
}
//= 执行函数：导出详细报表 空实现
std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> SaleReturnOrderController::executeExportSreDetail(const SreExportDetailQuery::Wrapper& query) {
    // 1. 调用Service查询DTO列表（主表+明细表）
    SreService service;
    auto dtoList = service.queryDetailList(query);

    // 2. 生成Excel详细报表
    auto buff = ExcelComponent().writeVectorToBuff("SreDetailExcel",
        [dtoList](ExcelComponent* ex) {
            // ========== 无论数据是否为空，先写入表头 ==========
            int row = 1;
            int col = 1;
            // 步骤1：写入“主表信息行”（若dtoList为空，显示默认提示）
            if (dtoList.empty()) {
                ex->setCellValue(row, col++, "客户:无数据");
                ex->setCellValue(row, col++, "单据日期:无数据");
                ex->setCellValue(row, col++, "单据编号:无数据");
            }
            else {
                ex->setCellValue(row, col++, "客户:" + dtoList[0]->customer);
                ex->setCellValue(row, col++, "单据日期:" + dtoList[0]->billDate);
                ex->setCellValue(row, col++, "单据编号:" + dtoList[0]->billNo);
            }
            // 空值占位
            for (int i = 0; i < 11; i++) {
                ex->setCellValue(row, col++, "");
            }
            ex->setRowProperties(row++);
            // ========== 步骤2：写入“商品表头行”（第2行） ==========
            col = 1;
            ex->addHeader({
                ZH_WORDS_GETTER("goods.field.name"),    // 商品名称
                ZH_WORDS_GETTER("goods.field.type"),    // 规格型号
                ZH_WORDS_GETTER("goods.field.attr"),    // 辅助属性
                ZH_WORDS_GETTER("goods.field.unit"),    // 单位
                ZH_WORDS_GETTER("goods.field.warehouse"),// 仓库
                ZH_WORDS_GETTER("goods.field.sell"),    // 单价
                ZH_WORDS_GETTER("goods.field.nums"),    // 数量
                ZH_WORDS_GETTER("goods.field.discount"),// 折扣率
                ZH_WORDS_GETTER("goods.field.dsc"),     // 折扣额
                ZH_WORDS_GETTER("saleReturnOrder.field.total"), // 金额
                ZH_WORDS_GETTER("saleReturnOrder.field.tax"),   // 税率
                ZH_WORDS_GETTER("saleReturnOrder.field.tat"),   // 税额
                ZH_WORDS_GETTER("saleReturnOrder.field.tpt"),   // 价税合计
                ZH_WORDS_GETTER("saleReturnOrder.field.data")   // 备注信息
                });
            ex->setRowProperties(row++);
            // ========== 步骤3：写入“商品数据行”（每条商品占一行，保留原有类型转换） ==========
            if (dtoList.empty()) {
                // 数据为空时，在商品行显示提示
                col = 1;
                ex->setCellValue(row, col++, "无匹配的商品数据");
                ex->setRowProperties(row++);
                return;
            }
            for (const auto& dto : dtoList) {
                for (const auto& item : *dto->items) {
                    col = 1;

                    // 商品明细字段：数值转字符串、状态转中文（保留原有转换逻辑）
                    ex->setCellValue(row, col++, item->goodsName);
                    ex->setCellValue(row, col++, item->spec);
                    ex->setCellValue(row, col++, item->attr);
                    ex->setCellValue(row, col++, item->unit);
                    ex->setCellValue(row, col++, item->warehouse);
                    ex->setCellValue(row, col++, std::to_string(item->price));   // 单价转字符串
                    ex->setCellValue(row, col++, std::to_string(item->nums));   // 数量转字符串
                    ex->setCellValue(row, col++, std::to_string(item->discountRate)); // 折扣率转字符串
                    ex->setCellValue(row, col++, std::to_string(item->discountAmount)); // 折扣额转字符串
                    ex->setCellValue(row, col++, std::to_string(item->amount)); // 金额转字符串
                    ex->setCellValue(row, col++, std::to_string(item->taxRate)); // 税率转字符串
                    ex->setCellValue(row, col++, std::to_string(item->taxAmount)); // 税额转字符串
                    ex->setCellValue(row, col++, std::to_string(item->taxIncludedAmount)); // 价税合计转字符串
                    ex->setCellValue(row, col, item->remark);
                    ex->setRowProperties(row++);
                }
            }
            // ========== 步骤4：写入“主表统计行”（最后一行） ==========
            col = 1;
            ex->setCellValue(row, col++, "单据金额:" + std::to_string(dtoList[0]->billAmount));
            ex->setCellValue(row, col++, "单据费用:" + std::to_string(dtoList[0]->billCost));
            ex->setCellValue(row, col++, "实际金额:" + std::to_string(dtoList[0]->actualAmount));
            ex->setCellValue(row, col++, getNucleusStatus(dtoList[0]->writeOffAmount));
            ex->setCellValue(row, col++, "结算账户:" + dtoList[0]->settlementAccount);
            ex->setCellValue(row, col++, getInvoiceStatus(dtoList[0]->invoiceInfo));
            ex->setCellValue(row, col++, "关联人员:" + dtoList[0]->relatedPerson);
            ex->setCellValue(row, col++, "物流信息:" + dtoList[0]->logisticsInfo);
            ex->setCellValue(row, col, "备注信息:" + dtoList[0]->remark);
            ex->setRowProperties(row++);


        }
    );

    // 3. 组装数据并上传到FastDFS
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

//批量导入数据
ImportResultDTO::Wrapper SaleReturnOrderController::executeImport(const SaleReturnBatchImportDTO::Wrapper& dto) {
    SreService service;
    return service.importData(dto);
}

//批量审核销售退货单
BatchOperationVO::Wrapper SaleReturnOrderController::executeBatchApprove(const SaleReturnAuditDTO::Wrapper& dto) {
    SreService service;
    return service.batchApprove(dto);
}

//批量反审核销售退货单
BatchOperationVO::Wrapper SaleReturnOrderController::executeBatchUnapprove(const SaleReturnAuditDTO::Wrapper& dto) {
    SreService service;
    return service.batchUnapprove(dto);
}


//销售退货单的核对/反核对
BatchOperationVO::Wrapper SaleReturnOrderController::executeCheck(const SreCheckDTO::Wrapper& dto) {
	auto result = BatchOperationVO::createShared();
	
	// 校验输入参数
	if (!dto || !dto->ids || dto->ids->size() == 0) {
		result->code = 400;
		result->message = ZH_WORDS_GETTER("saleReturnOrder.checkOrder.false");
		result->successCount = 0;
		result->failureCount = 0;
		return result;
	}
	
	// 创建 Service 实例
	SreService service;
	
	// 初始化计数器
	int successCount = 0;
	int failureCount = 0;
	auto failedIds = oatpp::Vector<oatpp::String>::createShared();
	
	// 遍历需要核对的退货单ID
	for (const auto& id : *dto->ids) {
		if (!id || id->empty()) {
			failureCount++;
			failedIds->push_back("EMPTY_ID");
			continue;
		}
		
		try {
			// 调用 Service 层的核对方法
			bool checked = service.checkById(id->c_str(), dto->checkStatus);
			if (checked) {
				successCount++;
			} else {
				failureCount++;
				failedIds->push_back(id);
			}
		}
		catch (const std::exception& e) {
			// 捕获异常，记录失败
			failureCount++;
			failedIds->push_back(id);
			OATPP_LOGE("SaleReturnOrderController", "Check return order failed: id=%s, error=%s", 
				id->c_str(), e.what());
		}
	}
	
	// 设置返回结果
	result->code = 200;
	result->message = dto->checkStatus ? ZH_WORDS_GETTER("saleReturnOrder.checkOrder.check") : ZH_WORDS_GETTER("saleReturnOrder.checkOrder.uncheck");
	result->successCount = successCount;
	result->failureCount = failureCount;
	result->failureIds = failedIds;
	
	return result;
}

//销售退货单的删除
DelSaleReturnResultVO::Wrapper SaleReturnOrderController::DelSaleReturn(const DelSaleReturnDTO::Wrapper& dto) {
	auto result = DelSaleReturnResultVO::createShared();
	
	// 校验输入参数
	if (!dto || !dto->returnIds || dto->returnIds->size() == 0) {
		result->successCount = 0;
		result->failureCount = 1;
		result->failedReturnIds = { "EMPTY_INPUT" };
		return result;
	}
	
	// 创建 Service 实例
	SreService service;
	
	// 初始化计数器
	int successCount = 0;
	int failureCount = 0;
	auto failedIds = oatpp::List<oatpp::String>::createShared();
	
	// 遍历所有要删除的退货单ID
	for (const auto& returnId : *dto->returnIds) {
		if (!returnId || returnId->empty()) {
			failureCount++;
			failedIds->push_back("EMPTY_ID");
			continue;
		}
		
		try {
			// 调用 Service 层的删除方法
			bool deleted = service.removeById(returnId->c_str());
			if (deleted) {
				successCount++;
			} else {
				failureCount++;
				failedIds->push_back(returnId);
			}
		}
		catch (const std::exception& e) {
			// 捕获异常，记录失败
			failureCount++;
			failedIds->push_back(returnId);
			OATPP_LOGE("SaleReturnOrderController", "Delete return order failed: id=%s, error=%s", 
				returnId->c_str(), e.what());
		}
	}
	
	// 设置返回结果
	result->successCount = successCount;
	result->failureCount = failureCount;
	result->failedReturnIds = failedIds;
	
	return result;
}