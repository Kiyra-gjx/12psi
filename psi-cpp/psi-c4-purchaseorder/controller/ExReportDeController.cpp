#include "../service/ExReportDeService.h"
#include "ExReportDeController.h"
#include "oatpp/web/protocol/http/outgoing/Response.hpp"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
ExReportDeController::execExportDe(const ExReportDeQUERY::Wrapper& query) {
    ExReportDeService service;
    // auto result = service.selectOne(query);
    auto result =  service.selectAll(query);
    if (!result) {
        return createResponse(Status::CODE_404, "Data not found");
    }

    auto buff = ExcelComponent().writeVectorToBuff("buy_info",
        [result](ExcelComponent* ex) {
            ex->addHeader({
                ZH_WORDS_GETTER("bor_info.goods"),      // 商品名称

                ZH_WORDS_GETTER("bor_info.attr"),       // 辅助属性
                ZH_WORDS_GETTER("bor_info.unit"),       // 单位
                ZH_WORDS_GETTER("bor_info.warehouse"),  // 仓库
                ZH_WORDS_GETTER("bor_info.price"),      // 单价
                ZH_WORDS_GETTER("bor_info.nums"),       // 数量

                ZH_WORDS_GETTER("bor_info.total"),      // 金额
                ZH_WORDS_GETTER("bor_info.tax"),        // 税率
                ZH_WORDS_GETTER("bor_info.tat"),        // 税额
                ZH_WORDS_GETTER("bor_info.tpt"),        // 价税合计
                ZH_WORDS_GETTER("bor_info.data")        // 备注信息
                });

            int row = 2;
            // TODO:  以下代码有逻辑bug，以后再修，先大概排查完再说，还得研究下报表组件才能确定怎么处理
            ex->setCellValue(row, 1, result->goods);

            ex->setCellValue(row, 3, result->attr);
            ex->setCellValue(row, 4, result->unit);
            ex->setCellValue(row, 5, result->warehouse);
            ex->setCellValue(row, 6, result->price->c_str());
            ex->setCellValue(row, 7, result->nums->c_str());


            ex->setCellValue(row, 10, result->total->c_str());
            ex->setCellValue(row, 11, result->tax->c_str());
            ex->setCellValue(row, 12, result->tat->c_str());
            ex->setCellValue(row, 13, result->tpt->c_str());
            ex->setCellValue(row, 14, result->data);

            ex->setRowProperties(row);
        });

    const char* charData = reinterpret_cast<const char*>(buff.data());
    auto fstring = String(charData, buff.size());

    auto response = createResponse(Status::CODE_200, fstring);
    std::string filename = "rp-bor_info-" + SimpleDateTimeFormat::format() + ".xlsx";
    response->putHeader("Content-Disposition", "attachment; filename=" + filename);
    response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

    return response;

    // return {};
}