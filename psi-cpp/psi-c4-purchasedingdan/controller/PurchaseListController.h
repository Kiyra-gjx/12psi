#ifndef _PUECHASELIST_CONTROLLER_
#define _PUECHASELIST_CONTROLLER_

#include"ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PurchaseListQuery.h"
#include "domain/dto/PurchaseListDTO.h"
#include "domain/vo/PurchaseListVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchase.tag")

/**
 * 采购单数据控制器，演示基础接口的使用
 */
class PurchaseListController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(PurchaseListController);
public: // 定义接口
    // 获取采购订单列表（条件+分页）接口描述
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("purchase.list.tag"), queryAllPurchaseList, PurchaseListQuery, PurchseListJsonVO::Wrapper, API_TAG);
    // 获取采购订单列表（条件+分页）接口端点
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/purchasedingdan/list", queryAllPurchaseList, PurchaseListQuery, executeQueryAll(query));

private: // 定义接口执行函数
    // 获取采购订单列表（条件+分页）
    PurchseListJsonVO::Wrapper executeQueryAll(const PurchaseListQuery::Wrapper& query);
};

#undef API_TAG

// 0 取消API控制器使用宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _PUECHASELIST_CONTROLLER_