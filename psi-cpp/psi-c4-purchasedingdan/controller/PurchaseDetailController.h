#ifndef _PURCHASEDETAIL_CONTROLLER_
#define _PURCHASEDETAIL_CONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PurchaseDetailQuery.h"
#include "domain/dto/PurchaseDetailDTO.h"
#include "domain/vo/PurchaseDetailVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchase.tag")

/**
 * 采购订单详情控制器
 */
class PurchaseDetailController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(PurchaseDetailController);
public: // 定义接口
    // 获取指定采购订单详情接口描述
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("purchase.detail.tag"), queryAllPurchaseDetail, PurchaseDetailQuery, PurchaseDetailJsonVO::Wrapper, API_TAG);
    // 获取指定采购订单详情接口端点
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/purchasedingdan/detail", queryAllPurchaseDetail, PurchaseDetailQuery, executeQueryAll(query));

private: // 定义接口执行函数
    // 获取指定采购订单详情
    PurchaseDetailJsonVO::Wrapper executeQueryAll(const PurchaseDetailQuery::Wrapper& query);
};

#undef API_TAG

// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _PURCHASEDETAIL_CONTROLLER_