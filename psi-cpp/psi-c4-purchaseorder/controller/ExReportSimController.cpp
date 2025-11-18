#include "ExReportSimController.h"
#include "oatpp/web/protocol/http/outgoing/Response.hpp"
#include "service/ExReportSimService.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"


std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
ExReportSimController::execExportSim(const ExReportSimQUERY::Wrapper& query) {
    // 定义一个Service
    SimpleReportService service;
    // 查询数据
    auto result = service.listAll(query);

    // 将数据写入到Excel中
    auto buff = ExcelComponent().writeVectorToBuff("bor",
        [result](ExcelComponent* ex) {
            // 写入表头 - 使用DTO中定义的字段描述
            ex->addHeader({
                ZH_WORDS_GETTER("bor.field.frame"),      // 框架
                ZH_WORDS_GETTER("bor.field.supplier"),  // 供应商
                ZH_WORDS_GETTER("bor.field.time"),       // 单据时间
                ZH_WORDS_GETTER("bor.field.number"),     // 单据编号
                ZH_WORDS_GETTER("bor.field.total"),      // 单据金额
                ZH_WORDS_GETTER("bor.field.actual"),     // 实际金额
                ZH_WORDS_GETTER("bor.field.arrival"),    // 到货日期
                ZH_WORDS_GETTER("bor.field.examine"),    // 审核状态
                ZH_WORDS_GETTER("bor.field.state"),      // 入库状态
                ZH_WORDS_GETTER("bor.field.people"),     // 关联人员
                ZH_WORDS_GETTER("bor.field.user"),       // 制单人
                ZH_WORDS_GETTER("bor.field.data")        // 备注信息
                });

            // 写入数据
            int row = 2;
            for (auto item : *(result->rows.get())) {
                int col = 1;
                ex->setCellValue(row, col++, item->frame);
                ex->setCellValue(row, col++, item->supplier);
                ex->setCellValue(row, col++, item->time);
                ex->setCellValue(row, col++, item->number);
                ex->setCellValue(row, col++, std::to_string(item->total));
                ex->setCellValue(row, col++, std::to_string(item->actual));
                // ex->setCellValue(row, col++, item->arrival);
                ex->setCellValue(row, col++, std::to_string(item->examine));
                // ex->setCellValue(row, col++, std::to_string(item->state));
                ex->setCellValue(row, col++, item->people);
                ex->setCellValue(row, col++, item->user);
                ex->setCellValue(row, col, item->data);
                ex->setRowProperties(row++);
            }
        });

    // 组装下发数据
    const char* charData = reinterpret_cast<const char*>(buff.data());
    auto fstring = String(charData, buff.size());

    // 创建响应头
    auto response = createResponse(Status::CODE_200, fstring);

    // 设置响应头信息
    std::string filename = "rp-sample-" + SimpleDateTimeFormat::format() + ".xlsx";
    response->putHeader("Content-Disposition", "attachment; filename=" + filename);
    response->putHeader(Header::CONTENT_TYPE, " application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

    // 影响成功结果
    return response;


	
	// return {}; // 返回一个空的 Response
}

