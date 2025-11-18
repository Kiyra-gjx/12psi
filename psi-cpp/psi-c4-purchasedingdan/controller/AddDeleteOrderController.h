#ifndef _AddDeleteOrderController_H_
#define _AddDeleteOrderController_H_

#include "domain/dto/AddDeleteOrderDTO.h"
#include "ApiHelper.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section
#define API_TAG ZH_WORDS_GETTER("purchase.tag")

class AddDeleteOrderController : public oatpp::web::server::api::ApiController {
public:
    AddDeleteOrderController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) /* Inject object mapper */)
        : oatpp::web::server::api::ApiController(objectMapper) {
        setDefaultAuthorizationHandler(std::make_shared<CustomerAuthorizeHandler>());
    }

    static std::shared_ptr<AddDeleteOrderController> createShared(std::shared_ptr<ObjectMapper>& objectMapper = (*((std::shared_ptr<ObjectMapper>*) oatpp::base::Environment::getComponent(typeid(std::shared_ptr<ObjectMapper>).name())))) {
        return std::make_shared<AddDeleteOrderController>(objectMapper);
    };

    ENDPOINT_INFO(addOrder) {
        info->summary = ZH_WORDS_GETTER("purchasedingdan.add.summary");
        info->tags.push_back(API_TAG);
        info->addConsumes<Object<AddOrderDTO>>("application/json");
        info->addResponse<Object<StringJsonVO>>(Status::CODE_200, "application/json");
        info->addSecurityRequirement("bearer_auth");
    }
    ENDPOINT("POST", "/purchasedingdan/add", addOrder,
        BODY_DTO(AddOrderDTO::Wrapper, dto),
        API_HANDLER_AUTH_PARAME) {
        return createResponse(Status::CODE_200, "Hello World!");
    }

    ENDPOINT_INFO(deleteOrder) {
        info->summary = ZH_WORDS_GETTER("purchasedingdan.delete.summary");
        info->tags.push_back(API_TAG);
        info->addConsumes<List<String>>("application/json");
        info->addResponse<Object<ListJsonVO<String>>>(Status::CODE_200, "application/json");
        info->addSecurityRequirement("bearer_auth");
    }
    ENDPOINT("DELETE", "/purchasedingdan/delete", deleteOrder,
        BODY_DTO(List<String>, ids),
        API_HANDLER_AUTH_PARAME) {
        return createResponse(Status::CODE_200, "Hello World!");
    }
private:
    StringJsonVO::Wrapper execAddOrder(const AddOrderDTO::Wrapper& dto);
    ListJsonVO<String>::Wrapper execDeleteOrder(const List<String>& ids);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
#endif // _AddDeleteOrderController_H_