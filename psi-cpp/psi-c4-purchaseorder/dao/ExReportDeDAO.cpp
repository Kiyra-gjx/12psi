
#include "stdafx.h"
#include "ExReportDeDAO.h"
#include "ExReportDeMapper.h"

// std::string ExReportDeDAO::selectById(std::string id)
// {
//     string sql = R"(
//             SELECT
//                 bi.goods,
//                 g.goods_no,
//                 g.spec_model,
//                 bi.attr,
//                 bi.unit,
//                 bi.warehouse,
//                 bi.price,
//                 bi.nums,
//                 bi.total,
//                 bi.tax,
//                 bi.tat,
//                 bi.tpt,
//                 bi.data
//             FROM buy b
//             LEFT JOIN buy_info bi ON b.id = bi.pid
//             LEFT JOIN goods g ON bi.goods = g.goods_code
//             WHERE b.id = ?
//         )";
// 	return sqlSession->executeQueryOne<PotableInfoDO>(sql, PtrBuyInfoDoMapper(), "%s", id);
// }

std::list<BuyInfoDO> ExReportDeDAO::selectWithPage(const ExReportDeQUERY::Wrapper &query) {
    return {};
}
