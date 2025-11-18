#ifndef _DELETERETURNORDERSCONTROLLER_H_
#define _DELETERETURNORDERSCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/dto/DeleteReturnOrdersDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG2 ZH_WORDS_GETTER("purchasereturnorder.tag")

/**
 * 采购退货单 - 控制器
 * 处理采购退货单的新增操作
 */
class DeleteReturnOrdersController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(DeleteReturnOrdersController);

public:

    // 添加采购退货单接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("purchase.return.order.delete.summary"),
        deleteReturnOrders,
        StringJsonVO::Wrapper,
        API_TAG2
    );

    // 添加采购退货单接口端点
    API_HANDLER_ENDPOINT_AUTH(
        API_M_DEL,
        "/purchasereturnorder/delete",
        deleteReturnOrders,
        BODY_DTO(DeleteReturnOrdersDTO::Wrapper, dto),
        executeDeleteReturnOrders(dto)
    );

private:
    // 执行新增采购退货单
    StringJsonVO::Wrapper executeDeleteReturnOrders(const DeleteReturnOrdersDTO::Wrapper& dto);
};

#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController)

#endif // _DELETERETURNORDERSCONTROLLER_H_