#ifndef _ADDRETURNORDERCONTROLLER_H_
#define _ADDRETURNORDERCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/dto/AddReturnOrderDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("purchasereturnorder.tag")

/**
 * 采购退货单 - 控制器
 * 处理采购退货单的新增操作
 */
class AddReturnOrderController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(AddReturnOrderController);

public:

    // 添加采购退货单接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("purchase.return.order.add.summary"),
        addReturnOrder,
        StringJsonVO::Wrapper,
        API_TAG
    );

    // 添加采购退货单接口端点
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/purchasereturnorder/add",
        addReturnOrder,
        BODY_DTO(AddReturnOrderDTO::Wrapper, dto),
        executeAddReturnOrder(dto)
    );

private:
    // 执行新增采购退货单
    StringJsonVO::Wrapper executeAddReturnOrder(const AddReturnOrderDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // _ADDRETURNORDERCONTROLLER_H_